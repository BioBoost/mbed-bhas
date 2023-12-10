#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  class PushButton : public Entity {

    public:
      enum class ButtonEvent { DOWN, UP, SHORT_PRESS, LONG_PRESS };

    public:
      PushButton(uint8_t id, EventQueue& queue, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

    private:
      void falling_edge();
      void rising_edge();

    private:
      void notify_event(ButtonEvent type);

    private:
      InterruptIn _button;
      Timer _timer;
      EventQueue& _queue;

  };

};

#endif
