#pragma once

#include "../communication/message_handler.h"

namespace BHAS {

  class MessageLogger : public IMessageHandler {

    public:
      void handle_message(const Message & message) const;

  };

};