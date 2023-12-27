#pragma once

#include "../message.h"
#include <vector>
#include "../i_handle_received_message.h"
#include "../i_handle_sent_message.h"
#include <string>

namespace BHAS::Communication {

  // Forward declaration
  class IHandleSentMessage;
  class IHandleReceivedMessage;

  // <<abstract>>
  class Channel {

    public:
      // Send message via the communication channel (may be queued)
      virtual bool send(Message& message) = 0;

      // Give processing time to the channel. Can be used to receive messages, send queued messages, ...
      virtual void process() = 0;

    public:
      void register_receive_handler(IHandleReceivedMessage* handler);
      void register_sent_handler(IHandleSentMessage* handler);

    public:
      uint32_t messages_received() const { return _messagesReceived; }
      uint32_t messages_sent() const { return _messagesSent; }

    protected:
      void call_receive_handlers(Message& message);
      void call_send_handlers(Message& message);

    public:
      virtual std::string to_string() { return "Channel"; }

    private:
      std::vector<IHandleReceivedMessage*> _receiveHandlers;
      std::vector<IHandleSentMessage*> _sentHandlers;

      uint32_t _messagesReceived = 0;
      uint32_t _messagesSent = 0;

  };

};