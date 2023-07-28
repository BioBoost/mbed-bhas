#pragma once

#include "message.h"

namespace BHAS::Communication {

  // <<interface>>
  class IMessageHandler {

    public:
      virtual void handle_received_message(Message& message) const = 0;
      virtual void handle_send_message(Message& message) const = 0;

  };

};