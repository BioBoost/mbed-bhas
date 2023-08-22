#pragma once

#include "node.h"
#include "channel.h"
#include <stdint.h>
#include "mbed.h"

namespace BHAS::Nodes {

  class FourSwitchNode : public Node {

    public:
      FourSwitchNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();

  };

};