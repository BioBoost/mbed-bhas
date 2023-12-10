#pragma once

#include "node.h"
#include "channel.h"
#include <cstdint>
#include "mbed.h"

namespace BHAS::Nodes {

  class Lpc1768 : public Node {

    public:
      Lpc1768(uint8_t id, uint8_t gatewayId, Communication::Channel& channel);

    private:
      void setup_leds();

  };

};