#include "lpc_1768.h"
#include "mbed_trace.h"
#include <stdint.h>
#include "indicator_led.h"

#define TRACE_GROUP "BHAS Lpc1768"

namespace BHAS::Nodes {

  Lpc1768::Lpc1768(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel)
  : Node(id, gatewayId, channel) {

    tr_info("Setting up a Lpc1768 node with [Nid: %d]", this->id());
    tr_info("Upstream gateway is configured with [Nid: %d]", this->gateway_id());

    setup_leds();
  }

  void Lpc1768::setup_leds() {
#if defined(TARGET_LPC1768)
    PinName ledPins[] = { LED1, LED2, LED3, LED4 };

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::IndicatorLed* led = new Entities::IndicatorLed(entities().get_free_id(), ledPins[i]);
      tr_info("Registering: %s", led->to_string().c_str());
      entities().add(led);
    }
#endif
  }

};