#pragma once

#include "i_message_handler.h"

namespace BHAS::Logging {

  class MessageLogger : public Communication::IMessageHandler {

    public:
      void handle_received_message(Communication::Message& message) const;
      void handle_send_message(Communication::Message& message) const;

  };

};