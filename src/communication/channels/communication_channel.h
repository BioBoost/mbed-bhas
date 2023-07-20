#pragma once

#include "message.h"
#include "message_handler.h"

namespace BHAS {

  // <<interface>>
  class ICommunicationChannel {

    public:
      // Send message via the communication channel
      bool send(const Message * const message);

      // // Register handler to process received messages
      // void register_receive_handler(IMessageHandler & handler);

      // Register handler to process send messages
      void register_send_handler(IMessageHandler & handler);

  };

};