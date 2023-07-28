#pragma once

#include "message.h"
#include "i_message_handler.h"
#include <vector>

namespace BHAS::Communication::Channels {

  // <<abstract>>
  class Channel {

    public:
      // Send message via the communication channel
      virtual bool send(Message& message) = 0;

      // Receive message via the communication channel
      virtual void receive() = 0;

    public:
      void register_receive_handler(IMessageHandler* handler);
      void register_send_handler(IMessageHandler* handler);

    protected:
      void call_receive_handlers(Message& message);
      void call_send_handlers(Message& message);

    private:
      std::vector<IMessageHandler*> _receiveHandlers;
      std::vector<IMessageHandler*> _sendHandlers;

  };

};