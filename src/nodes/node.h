#pragma once

#include "mbed_events.h"
#include <stdint.h>
#include "i_message_handler.h"
#include "message.h"
#include "message_logger.h"
#include "entity_manager.h"
#include "channel.h"
#include "event.h"

namespace BHAS {

  class Node : public Communication::IMessageHandler {

    public:
      Node(uint8_t id, uint8_t gatewayId, Communication::Channels::Channel& channel);

    public:
      uint8_t id() const;
      uint8_t gateway_id() const;

    public:
      void dispatch_forever();

    protected:
      Communication::Channels::Channel& channel();
      events::EventQueue& queue();
      EntityManager& entities();

    protected:
      void handle_received_message(Communication::Message& message);
      void handle_send_message(Communication::Message& message);

    private:
      void setup_channel_logging();
      void setup_channel_processing();
      void setup_system();

    protected:
      void event_handler(Event& event);

    protected:
      static const uint8_t BROADCAST_ID = 255;

    private:
      uint8_t _id = 0;
      uint8_t _gatewayId = 0;
      Communication::Channels::Channel& _channel;
      Logging::MessageLogger _messageLogger;
      EntityManager _entities;
      events::EventQueue _eventQueue;
  };

};