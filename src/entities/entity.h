#pragma once

#include <stdint.h>

namespace BHAS {

  // <<abstract>>
  class Entity {

    public:
      Entity(uint8_t id);

    public:
      uint8_t id() const;

    private:
      uint8_t _id = 0;

  };

};