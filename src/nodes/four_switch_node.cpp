#include "four_switch_node.h"
#include "mbed_trace.h"
#include <stdint.h>
#include "push_button.h"
#include "led.h"
#include "internal_temperature.h"

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

  void FourSwitchNode::setup_buttons() {
#if defined(TARGET_LPC1768)
    PinName buttonPins[] = { };
#else
    PinName buttonPins[] = { PC_13, D8, D9, D10 };
#endif

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(entities().get_free_id(), queue(), buttonPins[i]);
      button->on_event(callback(this, &FourSwitchNode::event_handler));
      tr_info("Registering: %s", button->to_string().c_str());
      entities().add(button);
    }
  }

  void FourSwitchNode::setup_leds() {
#if defined(TARGET_LPC1768)
    PinName ledPins[] = { LED1, LED2, LED3, LED4 };
#else
    PinName ledPins[] = { LED1 };
#endif

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::Led* led = new Entities::Led(entities().get_free_id(), ledPins[i]);
      tr_info("Registering: %s", led->to_string().c_str());
      entities().add(led);
    }
  }

  void FourSwitchNode::setup_temperature() {
    Entities::InternalTemperature * temperature = new Entities::InternalTemperature(entities().get_free_id(), queue());
    temperature->on_event(callback(this, &FourSwitchNode::event_handler));
    tr_info("Registering: %s", temperature->to_string().c_str());
    entities().add(temperature);
  }

};