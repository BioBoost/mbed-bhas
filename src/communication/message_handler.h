#pragma once

#include "message.h"

namespace BHAS {

  // <<interface>>
  class IMessageHandler {

    public:
      virtual void handle_message(const Message & message) const = 0;

  };

};