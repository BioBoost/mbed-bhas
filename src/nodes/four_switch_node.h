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
#include "event_context.h"

namespace BHAS::Nodes {

  class FourSwitchNode : public Node {

    public:
      FourSwitchNode(uint8_t id, Communication::Channels::Channel& channel);

    protected:
      void handle_received_message(Communication::Message& message) const override;
      void handle_send_message(Communication::Message& message) const override;

    private:
      void button_pressed(Events::EventContext* context, Entities::PushButton::PressType type);
      void temperature_ready(Events::EventContext* context, int8_t temperature);

    private:
      void setup_buttons();
      void setup_leds();
      void setup_temperature();

  };

};