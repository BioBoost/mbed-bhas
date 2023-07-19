#include "can_communication_channel.h"
#include "InterfaceCAN.h"
#include "mbed.h"

namespace BHAS {

  CANCommunicationChannel::CANCommunicationChannel(CAN & canBus)
    :_canBus(canBus) {
  }

  bool CANCommunicationChannel::send(Message * message) {
    char buffer[8] = { 0 };
    buffer[0] = message->destination_id();
    buffer[1] = message->entity_id();
    buffer[2] = static_cast<char>(message->type());
    memcpy(buffer+3, message->payload(), message->payload_size());

    return _canBus.write(CANMessage(message->source_id(), buffer, 3+message->payload_size()));
  }


};