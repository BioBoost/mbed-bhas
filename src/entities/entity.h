#pragma once

#include <stdint.h>
#include <string>

namespace BHAS::Entities {

  // <<abstract>>
  class Entity {

    public:
      Entity(uint8_t id, std::string description = "");

    public:
      uint8_t id() const;
      std::string description() const;

    public:
      virtual std::string to_string() const;

    private:
      uint8_t _id = 0;
      std::string _description;

  };

};