#include "channel.h"

namespace BHAS::Communication {

  void Channel::register_receive_handler(IHandleReceivedMessage* handler) {
    _receiveHandlers.push_back(handler);
  }

  void Channel::register_sent_handler(IHandleSentMessage* handler) {
    _sentHandlers.push_back(handler);
  }

  void Channel::call_receive_handlers(Message& message) {
    _messagesReceived++;
    for (auto handler : _receiveHandlers) {
      handler->handle_received_message(message, this);
    }
  }

  void Channel::call_send_handlers(Message& message) {
    _messagesSent++;
    for (auto handler : _sentHandlers) {
      handler->handle_sent_message(message, this);
    }
  }

};
