#include "four_switch_node.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS FourSwitchNode"

namespace BHAS::Nodes {

  FourSwitchNode::FourSwitchNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
  : Node(id, gatewayId, channel) {

    tr_info("Setting up a FourSwitchNode with [id: %d]", this->id());
    tr_info("Upstream gateway is configured with [id: %d]", this->gateway_id());

    setup_buttons();
    setup_leds();
    setup_temperature();
  }

  void FourSwitchNode::handle_received_message(Communication::Message& message) const {
    if (message.destination_id() != id() && message.destination_id() != Node::BROADCAST_ID) {
      tr_debug("Ignoring message");
      return;
    }

    // TODO: Handle message
  }

  void FourSwitchNode::handle_send_message(Communication::Message& message) const {
    // Ignore send messages
  }

  void FourSwitchNode::button_pressed(Events::EventContext* context, Entities::PushButton::PressType type) {
    Communication::Message message(id(), gateway_id(), context->entity().id(), Communication::Message::Type::EVENT);

    uint8_t payload[] = { static_cast<uint8_t>(type) };
    message.payload(payload, sizeof(payload));

    channel().send(message);
  }

  void FourSwitchNode::temperature_ready(Events::EventContext* context, int8_t temperature) {
    Communication::Message message(id(), gateway_id(), context->entity().id(), Communication::Message::Type::PERIODIC);

    uint8_t payload[] = { static_cast<uint8_t>(temperature) };
    message.payload(payload, sizeof(payload));

    channel().send(message);
  }

  void FourSwitchNode::setup_buttons() {
    PinName buttonPins[] = { PC_13, D8, D9, D10 };

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(10+i, queue(), buttonPins[i]);            // TODO: Better id generation !
      button->on_short_press(callback(this, &FourSwitchNode::button_pressed));
      button->on_long_press(callback(this, &FourSwitchNode::button_pressed));
      tr_info("Registering: %s", button->to_string().c_str());
      entities().add(button);
    }
  }

  void FourSwitchNode::setup_leds() {
    PinName ledPins[] = { LED1 };

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::Led* led = new Entities::Led(20+i, ledPins[i]);            // TODO: Better id generation !
      tr_info("Registering: %s", led->to_string().c_str());
      entities().add(led);
    }
  }

  void FourSwitchNode::setup_temperature() {
    Entities::InternalTemperature * temperature = new Entities::InternalTemperature(30, queue());
    temperature->on_temperature(callback(this, &FourSwitchNode::temperature_ready));
    tr_info("Registering: %s", temperature->to_string().c_str());
    entities().add(temperature);
  }

};