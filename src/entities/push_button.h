#pragma once

#include "mbed.h"
#include <stdint.h>
#include "event_context.h"
#include "entity.h"

namespace BHAS::Entities {

  class PushButton : public Entity {

    public:
      enum class PressType { SHORT, LONG };

    public:
      PushButton(uint8_t id, EventQueue& queue, PinName pin);

    public:
      // Why still pass type? Allow upper code to register single handler or two separate
      void on_short_press(Callback<void(BHAS::Events::EventContext*, PressType)> eventCallback);
      void on_long_press(Callback<void(BHAS::Events::EventContext*, PressType)> eventCallback);

    private:
      void falling_edge();
      void rising_edge();


    private:
      void notify_press(PressType type);

    private:
      InterruptIn _button;
      Timer _timer;
      EventQueue& _queue;

      Callback<void(BHAS::Events::EventContext*, PressType)> _onShortPress;
      Callback<void(BHAS::Events::EventContext*, PressType)> _onLongPress;

  };

};
