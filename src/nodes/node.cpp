#include "node.h"

#include "mbed.h"

namespace BHAS::Nodes {

  Node::Node(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
    : _id(id), _gatewayId(gatewayId), _channel(channel) {

    setup_channel_logging();
    setup_channel_processing();
  }

  uint8_t Node::id() const {
    return _id;
  }

  uint8_t Node::gateway_id() const {
    return _gatewayId;
  }

  void Node::take_over() {
    _eventQueue.dispatch_forever();
  }

  Communication::Channels::Channel& Node::channel() {
    return _channel;
  }

  events::EventQueue& Node::queue() {
    return _eventQueue;
  }

  EntityManager& Node::entities() {
    return _entities;
  }

  void Node::setup_channel_logging() {
    _channel.register_receive_handler(&_messageLogger);
    _channel.register_receive_handler(this);

    _channel.register_send_handler(&_messageLogger);
    _channel.register_send_handler(this);
  }

  void Node::setup_channel_processing() {
    _eventQueue.call_every(1ms, callback(&_channel, &Communication::Channels::Channel::receive));
  }

};