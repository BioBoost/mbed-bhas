#include "four_switch_node.h"
#include "mbed_trace.h"
#include <stdint.h>
#include "push_button.h"
#include "led.h"
#include "internal_temperature.h"
#include "alive_timer.h"

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

  void FourSwitchNode::setup_buttons() {
    PinName buttonPins[] = { PC_13, D8, D9, D10 };

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(10+i, queue(), buttonPins[i]);            // TODO: Better id generation !
      button->on_event(callback(this, &FourSwitchNode::event_handler));
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
    temperature->on_event(callback(this, &FourSwitchNode::event_handler));
    tr_info("Registering: %s", temperature->to_string().c_str());
    entities().add(temperature);
  }

  void FourSwitchNode::setup_alive_timer() {
    Entities::AliveTimer * alive = new Entities::AliveTimer(60, queue(), 20s);
    alive->on_event(callback(this, &FourSwitchNode::event_handler));
    tr_info("Registering: %s", alive->to_string().c_str());
    entities().add(alive);
  }

};