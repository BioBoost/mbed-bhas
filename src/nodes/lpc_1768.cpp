#include "lpc_1768.h"
#include "../logging/trace_logging.h"
#include <cstdint>
#include "indicator_led.h"
#include "../entities/channel_entity.h"

#define TRACE_GROUP "BHAS Lpc1768"

#if defined(TARGET_LPC1768)

namespace BHAS::Nodes {

  Lpc1768::Lpc1768(uint8_t id, uint8_t gatewayId)
  : Node(id, gatewayId), _canBus(p30, p29), _canChannel(_canBus) {

    tr_info("Creating an Lpc1768 Node with [Nid: %d]", this->id());
    tr_info("Upstream gateway is configured with [Nid: %d]", this->gateway_id());

    setup_leds();
    setup_channels();
  }

  void Lpc1768::setup_leds() {
    PinName ledPins[] = { LED1, LED2, LED3, LED4 };

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::IndicatorLed* led = new Entities::IndicatorLed(entities().get_free_id(), ledPins[i]);
      add_entity(led);
    }
  }

  void Lpc1768::setup_channels() {
    router()->register_channel(&_canChannel, true);
    queue().call_every(1ms, callback(&_canChannel, &Communication::Channel::process));

    Entities::ChannelEntity * channelEntity = new Entities::ChannelEntity(entities().get_free_id(), queue(), _canChannel, 500s, "Lpc1768 CAN Channel");
    channelEntity->on_event(callback(this, &Lpc1768::handle_event));
    add_entity(channelEntity);
  }

};

#endif