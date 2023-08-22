#pragma once

#include "node.h"
#include "channel.h"
#include "message.h"
#include <stdint.h>
#include "mbed.h"
#include "event.h"

namespace BHAS::Nodes {

  class FourSwitchNode : public Node {

    public:
      FourSwitchNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    public:
      virtual void dispatch_forever();

    protected:
      void handle_received_message(Communication::Message& message) override;
      void handle_send_message(Communication::Message& message) override;

    private:
      void event_handler(Event& event);

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();
      void setup_alive_timer();

    private:
      void send_can_boot_message();

  };

};