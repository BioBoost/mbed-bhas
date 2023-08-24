#include "node.h"
#include "mbed.h"
#include "mbed_trace.h"
#include "system.h"
#include "alive_timer.h"
#include "message_convertor.h"

#define TRACE_GROUP "BHAS Node"

namespace BHAS {

  Node::Node(uint8_t id, uint8_t gatewayId, Communication::Channel& channel)
    : _id(id), _gatewayId(gatewayId), _channel(channel) {

    setup_channel_logging();
    setup_channel_processing();
    setup_system();
    setup_alive_timer();
  }

  uint8_t Node::id() const {
    return _id;
  }

  uint8_t Node::gateway_id() const {
    return _gatewayId;
  }

  void Node::dispatch_forever() {
    _eventQueue.dispatch_forever();
  }

  Communication::Channel& Node::channel() {
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
    _eventQueue.call_every(1ms, callback(&_channel, &Communication::Channel::receive));
  }

  void Node::setup_system() {
    // TODO: Can we add the type of the node here ?
    // That way our gateway can report of its a relayNode, a SwitchNode, ...
    Entities::System * system = new Entities::System(entities().get_free_id(), queue());
    system->on_event(callback(this, &Node::event_handler));
    tr_info("Registering: %s", system->to_string().c_str());
    entities().add(system);
  }

  void Node::setup_alive_timer() {
    Entities::AliveTimer * alive = new Entities::AliveTimer(entities().get_free_id(), queue());
    alive->on_event(callback(this, &Node::event_handler));
    tr_info("Registering: %s", alive->to_string().c_str());
    entities().add(alive);
  }

  void Node::event_handler(Event& event) {
    Communication::Message message = Convertors::MessageConvertor::event_to_message(id(), gateway_id(), event);
    _channel.send(message);
  }

  void Node::handle_received_message(Communication::Message& message) {
    if (message.destination_id() != id() && message.destination_id() != Node::BROADCAST_ID) {
      tr_debug("Ignoring message");
      return;
    }

    Entity* entity = entities().find_by_id(message.entity_id());
    if (!entity) {
      tr_warning("Could not find entity with id = %d", message.entity_id());
      return;   // Error ?
    }

    switch(message.base_type()) {
      case Communication::Message::BaseType::ACTION:
        Action action = Convertors::MessageConvertor::message_to_action(message);
        entity->process_action(action);
        break;

      // TODO: Handle other types of messages like CONFIG
      // case Communication::Message::BaseType::CONFIG: 
    }
  }

  void Node::handle_send_message(Communication::Message& message) {
    // Ignore send messages
  }

};