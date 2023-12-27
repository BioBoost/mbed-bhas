#pragma once

#include "message.h"
#include "channels/channel.h"

namespace BHAS::Communication {

  // Forward declaration
  class Channel;

  // <<interface>>
  class IHandleSentMessage {

    public:
      virtual void handle_sent_message(Message& message, Channel* channel) = 0;

  };

};