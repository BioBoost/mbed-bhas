#pragma once

#include "channel.h"
#include <queue>
#include "i_message_handler.h"

namespace BHAS::Communication::Channels {

  class LocalEchoChannel : public Channel {

    public:
      // Sending a message on this channel will trigger an echo of the same message
      bool send(Message& message);
      void receive();
  
    private:
      std::queue<Message> _messageBuffer;
    
  };

};
