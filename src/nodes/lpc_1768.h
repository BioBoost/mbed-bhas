#pragma once

#include "node.h"
#include "channel.h"
#include <stdint.h>
#include "mbed.h"

namespace BHAS::Nodes {

  class Lpc1768 : public Node {

    public:
      Lpc1768(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    private:
      void setup_leds();

  };

};