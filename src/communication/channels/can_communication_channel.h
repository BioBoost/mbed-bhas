#pragma once

#include "InterfaceCAN.h"
#include "mbed.h"
#include "communication_channel.h"
#include <vector>
#include "../message_handler.h"

namespace BHAS {

  class CANCommunicationChannel : public ICommunicationChannel {

    public:
      CANCommunicationChannel(CAN & canBus);

    public:
      bool send(const Message & message);

    public:
      void register_receive_handler(IMessageHandler & handler);
      void register_send_handler(IMessageHandler & handler);

    private:
      void call_handlers(std::vector<std::reference_wrapper<IMessageHandler>> & handlers, const Message & message) const;

    private:
      static const size_t MAX_CAN_PACKET_SIZE = 8;
      CAN & _canBus;
      std::vector<std::reference_wrapper<IMessageHandler>> _receiveHandlers;
      std::vector<std::reference_wrapper<IMessageHandler>> _sendHandlers;

  };

};