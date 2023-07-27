#pragma once

#include "message.h"

namespace BHAS::Communication {

  // <<interface>>
  class IMessageHandler {

    public:
      virtual void handle_message(Message& message) const = 0;

  };

};