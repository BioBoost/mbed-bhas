#pragma once

#include "mbed_events.h"
#include <cstdint>
#include <vector>
#include "../communication/message.h"
#include "../entity_manager/entity_manager.h"
#include "../entities/events/event.h"
#include "../communication/channels/channel.h"
#include "../logging/trace_logging.h"
#include "../router/router.h"
#include "../communication/i_handle_received_message.h"

// Forward declaration
namespace BHAS::Communication {
  class Router;
};

namespace BHAS::Nodes {

  class Node : public Communication::IHandleReceivedMessage {

    public:
      Node(uint8_t id, uint8_t gatewayId);

    public:
      uint8_t id() const { return _id; }
      uint8_t gateway_id() const { return _gatewayId; }
      virtual std::string type() const { return "Node"; }

    protected:
      void add_entity(Entity* entity);

    public:
      void dispatch_forever();

    protected:
      events::EventQueue& queue() { return _eventQueue; }
      EntityManager& entities() { return _entities; }
      Communication::Router* router() { return _router; }

    public:
      void handle_received_message(Communication::Message& message, Communication::Channel* channel);

    private:
      void setup_system_entity();
      void setup_alive_timer_entity();

    protected:
      void handle_event(Event& event);

    public:
      virtual std::string to_string() const;

    private:
      uint8_t _id = 0;
      uint8_t _gatewayId = 0;
      EntityManager _entities;
      events::EventQueue _eventQueue;
      Communication::Router* _router = nullptr;       // TODO: Can't seem to create instance here
  };

};
