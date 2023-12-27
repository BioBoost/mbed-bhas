#include "nucleo_l476.h"
#include "../logging/trace_logging.h"
#include <cstdint>
#include "push_button.h"
#include "indicator_led.h"
#include "internal_temperature.h"
#include "../entities/channel_entity.h"

#define TRACE_GROUP "BHAS NucleoL476"

#if defined(TARGET_NUCLEO_L476RG)

namespace BHAS::Nodes {

  NucleoL476::NucleoL476(uint8_t id, uint8_t gatewayId)
  : Node(id, gatewayId), _canBus(D15, D14), _canChannel(_canBus) {

    tr_info("Creating a NucleoL476 Node with [Nid: %d]", this->id());
    tr_info("Upstream gateway is configured with [Nid: %d]", this->gateway_id());

    setup_buttons();
    setup_leds();
    setup_temperature();
    setup_channels();
  }

  void NucleoL476::setup_buttons() {
    PinName buttonPins[] = { PC_13 };

    for (size_t i = 0; i < sizeof(buttonPins)/sizeof(PinName); i++) {
      Entities::PushButton* button = new Entities::PushButton(entities().get_free_id(), queue(), buttonPins[i]);
      button->on_event(callback(this, &NucleoL476::handle_event));
      add_entity(button);
    }
  }

  void NucleoL476::setup_leds() {
    PinName ledPins[] = { LED1 };

    for (size_t i = 0; i < sizeof(ledPins)/sizeof(PinName); i++) {
      Entities::IndicatorLed* led = new Entities::IndicatorLed(entities().get_free_id(), ledPins[i]);
      add_entity(led);
    }
  }

  void NucleoL476::setup_temperature() {
    Entities::InternalTemperature * temperature = new Entities::InternalTemperature(entities().get_free_id(), queue());
    temperature->on_event(callback(this, &NucleoL476::handle_event));
    add_entity(temperature);
  }

  void NucleoL476::setup_channels() {
    router()->register_channel(&_canChannel, true);
    queue().call_every(1ms, callback(&_canChannel, &Communication::Channel::process));

    Entities::ChannelEntity * channelEntity = new Entities::ChannelEntity(entities().get_free_id(), queue(), _canChannel, 500s, "Nucleo CAN Channel");
    channelEntity->on_event(callback(this, &NucleoL476::handle_event));
    add_entity(channelEntity);
  }

};

#endif