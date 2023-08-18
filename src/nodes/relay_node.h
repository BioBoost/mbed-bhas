#pragma once

#include "node.h"
#include "channel.h"
#include "internal_temperature.h"
#include "relay.h"
#include "entity.h"
#include "message.h"
#include <stdint.h>
#include "mbed.h"
#include "event_context.h"

namespace BHAS::Nodes {

  class RelayNode : public Node {

    public:
      RelayNode(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    public:
      virtual void dispatch_forever();

    protected:
      void handle_received_message(Communication::Message& message) const override;
      void handle_send_message(Communication::Message& message) const override;

    private:
      void temperature_ready(Events::EventContext* context, int8_t temperature);

    private:
      void setup_temperature();
      void setup_relays();

    private:
      void send_can_boot_message();

  };

};