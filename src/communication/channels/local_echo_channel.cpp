#include "local_echo_channel.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS LocalEchoChannel"

namespace BHAS::Communication::Channels {

  LocalEchoChannel::LocalEchoChannel() {
    tr_info("Creating LocalEchoChannel");
  }

  bool LocalEchoChannel::send(Message& message) {
    _messageBuffer.push(message);
    call_send_handlers(message);
    return true;
  }

  void LocalEchoChannel::receive() {
    if (_messageBuffer.size() == 0) return;
    
    Message message = _messageBuffer.front();
    _messageBuffer.pop();
    call_receive_handlers(message);
  }

};
