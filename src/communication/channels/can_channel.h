#pragma once

#if !DEVICE_CAN
#warning [NOT_SUPPORTED] CAN not supported for this target
#else

#include "InterfaceCAN.h"
#include "mbed.h"
#include "channel.h"

namespace BHAS::Communication::Channels {

  class CANChannel : public Channel {

    public:
      CANChannel(CAN& canBus);

    public:
      bool send(Message& message);
      void receive();   // Need to call this method periodically to receive messages; handlers will be called if registered
    
    private:
      static const size_t MAX_CAN_PACKET_SIZE = 8;
      CAN& _canBus;

  };

};

#endif