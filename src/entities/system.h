#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  // System entity basically represents the device itself
  // One of its responsibilities is generating a boot event.

  class System : public Entity {

    public:
      System(uint8_t id, EventQueue& queue, std::string description = "");

    public:
      virtual std::string name() const override;

    private:
      void notify_boot();

  };

};

#endif