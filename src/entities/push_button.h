#pragma once

#include "entity.h"
#include "mbed.h"
#include "mbed_events.h"
#include "entity_event_handler.h"

namespace BHAS {

  class PushButton : public Entity {

    public:
      PushButton(uint8_t id, PinName pin, EntityEventHandler * eventHandler);

    private:
      void handle_fall_event();
      void handle_rise_event();

    private:
      InterruptIn button;
      Timer timer;
      EntityEventHandler * _eventHandler = nullptr;
  };

};