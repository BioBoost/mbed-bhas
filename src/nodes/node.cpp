#include "node.h"
#include "mbed.h"
#include "mbed_trace.h"
#include "system.h"

#define TRACE_GROUP "BHAS Node"

namespace BHAS {

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

  void Node::dispatch_forever() {
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

  void Node::setup_system() {
    Entities::System * system = new Entities::System(1, queue());
    system->on_event(callback(this, &Node::event_handler));
    tr_info("Registering: %s", system->to_string().c_str());
    entities().add(system);
  }

  void Node::event_handler(Event& event) {
    Communication::Message message(id(), gateway_id(), event.entity().id(), Communication::Message::BaseType::EVENT, static_cast<uint8_t>(event.type()));
    message.payload(&event.arguments()[0], event.arguments().size());
    _channel.send(message);
  }

  void Node::handle_received_message(Communication::Message& message) {
    if (message.destination_id() != id() && message.destination_id() != Node::BROADCAST_ID) {
      tr_debug("Ignoring message");
      return;
    }

    Entities::Entity* entity = entities().find_by_id(message.entity_id());
    if (!entity) {
      tr_warning("Could not find entity with id = %d", message.entity_id());
      return;   // Error ?
    }

    switch(message.base_type()) {
      case Communication::Message::BaseType::ACTION:
        // Here we should call convertor for the action
        std::vector<uint8_t> args;
        for (size_t i = 0; i < message.payload_size(); i++) { args.push_back(message.payload()[i]); }
        Action action(static_cast<Action::Type>(message.sub_type()), args);
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