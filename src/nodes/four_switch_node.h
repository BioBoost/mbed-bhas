#pragma once

#include "node.h"
#include "channel.h"
#include "internal_temperature.h"
#include "push_button.h"
#include "led.h"
#include "entity.h"
#include "message.h"
#include <stdint.h>
#include "mbed.h"
#include "temperature_event.h"
#include "alive_time_event.h"

namespace BHAS::Nodes {

  class FourSwitchNode : public Node {

    public:
      FourSwitchNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    public:
      virtual void dispatch_forever();

    protected:
      void handle_received_message(Communication::Message& message) const override;
      void handle_send_message(Communication::Message& message) const override;

    private:
      void button_event(BHAS::Events::ButtonEvent& event);
      void temperature_ready(BHAS::Events::TemperatureEvent& event);
      void alive_ready(BHAS::Events::AliveTimeEvent& event);

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();
      void setup_alive_timer();

    private:
      void send_can_boot_message();

  };

};