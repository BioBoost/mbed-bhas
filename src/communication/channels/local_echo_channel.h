#pragma once

#include "channel.h"
#include <queue>

namespace BHAS::Communication::Channels {

  class LocalEchoChannel : public Channel {

    public:
      LocalEchoChannel();

    public:
      // Sending a message on this channel will trigger an echo of the same message
      bool send(Message& message);
      void process();
  
    private:
      std::queue<Message> _messageBuffer;
    
  };

};
