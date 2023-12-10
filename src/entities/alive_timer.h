#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
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

    private:
      Timer _timer;

  };

};

#endif