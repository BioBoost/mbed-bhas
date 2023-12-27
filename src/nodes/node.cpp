#include "node.h"
#include "mbed.h"
#include "../logging/trace_logging.h"
#include "message_convertor.h"
#include "../entities/system.h"
#include "../entities/alive_timer.h"

#define TRACE_GROUP "BHAS Node"

namespace BHAS::Nodes {

  Node::Node(uint8_t id, uint8_t gatewayId)
    : _id(id), _gatewayId(gatewayId) {

    _router = new Communication::Router(this);
    setup_system_entity();
    setup_alive_timer_entity();
  }

  /**
   * Add an entity to the node.
  */
  void Node::add_entity(Entity* entity) {
    tr_info("Registering: %s", entity->to_string().c_str());
    _entities.add(entity);
  }

  /**
   * Hand over processing to the event queue.
  */
  void Node::dispatch_forever() {
    _eventQueue.dispatch_forever();
  }

  void Node::setup_system_entity() {
    Entities::System * system = new Entities::System(entities().get_free_id(), queue());
    system->on_event(callback(this, &Node::handle_event));
    add_entity(system);
  }

  void Node::setup_alive_timer_entity() {
    Entities::AliveTimer * alive = new Entities::AliveTimer(entities().get_free_id(), queue());
    alive->on_event(callback(this, &Node::handle_event));
    add_entity(alive);
  }

  /**
   * Internal event (temperature, system events, channel stats, button press, ...) handler.
  */
  void Node::handle_event(Event& event) {
    tr_info("Event has occurred: %s", event.to_string().c_str());
    Communication::Message message = Convertors::MessageConvertor::event_to_message(id(), gateway_id(), event);
    router()->send_message(message);
  }

  /**
   * If the router has received a message that is intended for this node,
   * than it is delivered here.
  */
  void Node::handle_received_message(Communication::Message& message, Communication::Channel* channel) {
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

  std::string Node::to_string() const {
    // TODO
    return "Node tostring() ...";
  }

};