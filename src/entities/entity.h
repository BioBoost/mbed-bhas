#pragma once

#include <stdint.h>
#include <string>
#include "action.h"

namespace BHAS::Entities {

  // <<abstract>>
  class Entity {

    public:
      Entity(uint8_t id, std::string description = "");

    public:
      uint8_t id() const;
      std::string description() const;

    public:
      virtual std::string name() const;
      virtual std::string to_string() const;

    public:
      // TODO - Actually implement these
      virtual void enable() {};
      virtual void disable() {};
      virtual void reset() {};

    public:
      // virtual void on_event(Callback<void(Events::Event)> eventCallback);
      virtual void process_action(Actions::Action& action);


    private:
      uint8_t _id = 0;
      std::string _description;

  };

};