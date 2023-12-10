#pragma once

#include "../message.h"
#include "../i_message_handler.h"
#include <vector>

namespace BHAS::Communication {

  // <<abstract>>
  class Channel {

    public:
      // Send message via the communication channel (may be queued)
      virtual bool send(Message& message) = 0;

      // Give processing time to the channel. Can be used to receive messages, send queued messages, ...
      virtual void process() = 0;

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