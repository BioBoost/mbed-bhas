#pragma once

#include "../bhas_platform.h"

#if defined(TARGET_NUCLEO_L476RG)

#include "node.h"
#include "channel.h"
#include <cstdint>
#include "mbed.h"
#include "../communication/channels/can_channel.h"


namespace BHAS::Nodes {

  class NucleoL476 : public Nodes::Node {

    public:
      NucleoL476(uint8_t id, uint8_t gatewayId);

    public:
      virtual std::string type() const override { return "NucleoL476"; }

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();
      void setup_channels();

    private:
      CAN _canBus;
      Communication::Channels::CANChannel _canChannel;
  };

};

#endif