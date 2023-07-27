#include "channel.h"

namespace BHAS::Communication::Channels {

  void Channel::register_receive_handler(IMessageHandler* handler) {
    _receiveHandlers.push_back(handler);
  }

  void Channel::register_send_handler(IMessageHandler* handler) {
    _sendHandlers.push_back(handler);
  }

  void Channel::call_receive_handlers(Message& message) {
    call_handlers(_receiveHandlers, message);
  }

  void Channel::call_send_handlers(Message& message) {
    call_handlers(_sendHandlers, message);
  }

  void Channel::call_handlers(std::vector<IMessageHandler*>& handlers, Message& message) {
    for (auto handler : handlers) {
      handler->handle_message(message);
    }
  }

};
