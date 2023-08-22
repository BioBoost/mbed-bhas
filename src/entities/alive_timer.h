#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  class AliveTimer : public Entity {

    public:
      AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 300s, std::string description = "");

    public:
      virtual std::string name() const override;

    private:
      void notify_alive();

  };

};
