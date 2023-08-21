#include "four_switch_node.h"
#include "alive_timer.h"
#include "mbed_trace.h"
#include "event_convertor.h"

#define TRACE_GROUP "BHAS FourSwitchNode"

namespace BHAS::Nodes {

  FourSwitchNode::FourSwitchNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
  : Node(id, gatewayId, channel) {

    tr_info("Setting up a FourSwitchNode with [id: %d]", this->id());
    tr_info("Upstream gateway is configured with [id: %d]", this->gateway_id());

    setup_buttons();
    setup_leds();
    setup_temperature();
    setup_alive_timer();
  }

  void FourSwitchNode::dispatch_forever() {
    send_can_boot_message();
    Node::dispatch_forever();
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

  void FourSwitchNode::button_event(BHAS::Events::ButtonEvent& event) {
    Communication::Message message = Events::EventConvertor::to_message(event, id(), gateway_id());
    channel().send(message);
  }

  void FourSwitchNode::temperature_ready(BHAS::Events::TemperatureEvent& event) {
    Communication::Message message = Events::EventConvertor::to_message(event, id(), gateway_id());
    channel().send(message);
  }

  void FourSwitchNode::alive_ready(BHAS::Events::AliveTimeEvent& event) {
    Communication::Message message = Events::EventConvertor::to_message(event, id(), gateway_id());
    channel().send(message);
  }

  void FourSwitchNode::setup_buttons() {
    PinName buttonPins[] = { PC_13, D8, D9, D10 };

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(10+i, queue(), buttonPins[i]);            // TODO: Better id generation !
      button->on_event(callback(this, &FourSwitchNode::button_event));
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

  void FourSwitchNode::setup_alive_timer() {
    Entities::AliveTimer * alive = new Entities::AliveTimer(60, queue());
    alive->on_alive(callback(this, &FourSwitchNode::alive_ready));
    tr_info("Registering: %s", alive->to_string().c_str());
    entities().add(alive);
  }

  // TODO: Refactor - duplicate in RelayNode
  void FourSwitchNode::send_can_boot_message() {
    Communication::Message message(id(), gateway_id(), 0, Communication::Message::Type::BOOT);
    channel().send(message);
  }

};