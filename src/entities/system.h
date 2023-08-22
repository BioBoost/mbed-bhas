#pragma once

#include "mbed.h"
#include <stdint.h>
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
