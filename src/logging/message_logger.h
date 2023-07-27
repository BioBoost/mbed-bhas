#pragma once

#include "i_message_handler.h"

namespace BHAS::Logging {

  class MessageLogger : public Communication::IMessageHandler {

    public:
      void handle_message(Communication::Message& message) const;

  };

};