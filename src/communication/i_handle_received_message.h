#pragma once

#include "message.h"
#include "channels/channel.h"

namespace BHAS::Communication {

  // Forward declaration
  class Channel;

  // <<interface>>
  class IHandleReceivedMessage {

    public:
      virtual void handle_received_message(Message& message, Channel* channel) = 0;

  };

};