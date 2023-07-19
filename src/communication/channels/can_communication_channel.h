#pragma once

#include "InterfaceCAN.h"
#include "mbed.h"
#include "communication_channel.h"

namespace BHAS {

  class CANCommunicationChannel : public ICommunicationChannel {

    public:
      CANCommunicationChannel(CAN & canBus);

    public:
      bool send(Message * message);

    private:
      CAN & _canBus;

  };

};