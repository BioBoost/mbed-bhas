#pragma once

#include "node.h"
#include "channel.h"
#include <stdint.h>
#include "mbed.h"

namespace BHAS::Nodes {

  class NucleoL476 : public Node {

    public:
      NucleoL476(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();

  };

};