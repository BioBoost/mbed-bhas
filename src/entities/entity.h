#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)
#include "mbed.h"
#endif

#include <cstdint>
#include <string>
#include "./actions/action.h"
#include "./events/event.h"

namespace BHAS {

  // Forward declaration
  class Event;
  class Action;

  // <<abstract>>
  class Entity {

    public:
      Entity(uint8_t id, std::string description = "");

    public:
      uint8_t id() const;
      std::string description() const;

    public:
      virtual std::string name() const;
      virtual std::string to_string() const;

    public:
      // TODO - Actually implement these
      virtual void enable() {};
      virtual void disable() {};
      virtual void reset() {};

    public:
      // Register event handler
#if defined(PLATFORM_MBED)
      void on_event(mbed::Callback<void(Event&)> eventCallback);
#endif

    public:
      virtual void process_action(Action& action);

    protected:
      void call_event_handler(Event& event);

    private:
      uint8_t _id = 0;
      std::string _description;
#if defined(PLATFORM_MBED)
      Callback<void(Event&)> _onEvent;
#endif
  };

};
