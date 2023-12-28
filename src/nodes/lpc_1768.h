#pragma once

#include "../bhas_platform.h"

#if defined(TARGET_LPC1768)

#include "node.h"
#include "channel.h"
#include <cstdint>
#include "mbed.h"
#include "../communication/channels/can_channel.h"


namespace BHAS::Nodes {

  class Lpc1768 : public Nodes::Node {

    public:
      Lpc1768(uint8_t id, uint8_t gatewayId);

    public:
      virtual std::string type() const override { return "Lpc1768"; }

    private:
      void setup_leds();
      void setup_channels();

    private:
      CAN _canBus;
      Communication::Channels::CANChannel _canChannel;
  };

};

#endif