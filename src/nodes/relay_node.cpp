#include "relay_node.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS RelayNode"

namespace BHAS::Nodes {

  RelayNode::RelayNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
  : Node(id, gatewayId, channel) {

    tr_info("Setting up a RelayNode with [id: %d]", this->id());
    tr_info("Upstream gateway is configured with [id: %d]", this->gateway_id());

    setup_relays();
    setup_temperature();
  }

  void RelayNode::dispatch_forever() {
    send_can_boot_message();
    Node::dispatch_forever();
  }

  void RelayNode::handle_received_message(Communication::Message& message) const {
    if (message.destination_id() != id() && message.destination_id() != Node::BROADCAST_ID) {
      tr_debug("Ignoring message");
      return;
    }

    // TODO: Handle message
  }

  void RelayNode::handle_send_message(Communication::Message& message) const {
    // Ignore send messages
  }

  void RelayNode::temperature_ready(Events::EventContext* context, int8_t temperature) {
    Communication::Message message(id(), gateway_id(), context->entity().id(), Communication::Message::Type::PERIODIC);

    uint8_t payload[] = { static_cast<uint8_t>(temperature) };
    message.payload(payload, sizeof(payload));

    channel().send(message);
  }

  void RelayNode::setup_relays() {
    PinName relayPins[] = { LED1, D8, D9, D10 };

    for (size_t i = 0; i < sizeof(relayPins)/sizeof(PinName); i++) {
      Entities::Relay* relay = new Entities::Relay(10+i, relayPins[i]);            // TODO: Better id generation !
      tr_info("Registering: %s", relay->to_string().c_str());
      entities().add(relay);
    }
  }

  void RelayNode::setup_temperature() {
    Entities::InternalTemperature * temperature = new Entities::InternalTemperature(30, queue());
    temperature->on_temperature(callback(this, &RelayNode::temperature_ready));
    tr_info("Registering: %s", temperature->to_string().c_str());
    entities().add(temperature);
  }

  // TODO: Refactor - duplicate in FourSwitchNode
  void RelayNode::send_can_boot_message() {
    Communication::Message message(id(), gateway_id(), 0, Communication::Message::Type::BOOT);
    channel().send(message);
  }

};

// TODO: AliveTimer not implemented yet