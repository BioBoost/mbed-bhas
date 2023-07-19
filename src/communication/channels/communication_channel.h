#pragma once

#include "message.h"

namespace BHAS {

  // <<interface>>
  class ICommunicationChannel {

    public:
      bool send(Message * message);

  };

};