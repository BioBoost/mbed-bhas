#include "nucleo_l476.h"
#include "mbed_trace.h"
#include <stdint.h>
#include "push_button.h"
#include "indicator_led.h"
#include "internal_temperature.h"

#define TRACE_GROUP "BHAS NucleoL476"

namespace BHAS::Nodes {

  NucleoL476::NucleoL476(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
  : Node(id, gatewayId, channel) {

    tr_info("Setting up a NucleoL476 with [Nid: %d]", this->id());
    tr_info("Upstream gateway is configured with [Nid: %d]", this->gateway_id());

    setup_buttons();
    setup_leds();
    setup_temperature();
  }

  void NucleoL476::setup_buttons() {
#if defined(TARGET_NUCLEO_L476RG)
    PinName buttonPins[] = { PC_13 };

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(entities().get_free_id(), queue(), buttonPins[i]);
      button->on_event(callback(this, &NucleoL476::event_handler));
      tr_info("Registering: %s", button->to_string().c_str());
      entities().add(button);
    }
#endif
  }

  void NucleoL476::setup_leds() {
#if defined(TARGET_NUCLEO_L476RG)
    PinName ledPins[] = { LED1 };

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::IndicatorLed* led = new Entities::IndicatorLed(entities().get_free_id(), ledPins[i]);
      tr_info("Registering: %s", led->to_string().c_str());
      entities().add(led);
    }
#endif
  }

  void NucleoL476::setup_temperature() {
#if defined(TARGET_NUCLEO_L476RG)
    Entities::InternalTemperature * temperature = new Entities::InternalTemperature(entities().get_free_id(), queue());
    temperature->on_event(callback(this, &NucleoL476::event_handler));
    tr_info("Registering: %s", temperature->to_string().c_str());
    entities().add(temperature);
#endif
  }

};