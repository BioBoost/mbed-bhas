#pragma once

#include "../communication/i_handle_received_message.h"
#include "../communication/i_handle_sent_message.h"

namespace BHAS::Logging {

  class MessageLogger : public Communication::IHandleReceivedMessage, public Communication::IHandleSentMessage {

    public:
      void handle_received_message(Communication::Message& message, Communication::Channel* channel);
      void handle_sent_message(Communication::Message& message, Communication::Channel* channel);

  };

};