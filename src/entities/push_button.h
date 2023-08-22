#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"
#include "button_event.h"
#include "action.h"

namespace BHAS::Entities {

  class PushButton : public Entity {

    public:
      PushButton(uint8_t id, EventQueue& queue, PinName pin, std::string description = "");

    public:
      void on_event(Callback<void(BHAS::Events::ButtonEvent&)> eventCallback);

    private:
      void falling_edge();
      void rising_edge();


    private:
      void notify_press(Events::ButtonEvent::Type type);

    public:
      virtual std::string name() const override;

    public:
      virtual void process_action(Actions::Action& action) override {};

    private:
      InterruptIn _button;
      Timer _timer;
      EventQueue& _queue;

      Callback<void(BHAS::Events::ButtonEvent&)> _onEvent;

  };

};
