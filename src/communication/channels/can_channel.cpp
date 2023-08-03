#if !DEVICE_CAN
#warning [NOT_SUPPORTED] CAN not supported for this target
#else

#include "can_channel.h"
#include "mbed.h"
#include "InterfaceCAN.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS CANChannel"

namespace BHAS::Communication::Channels {

  CANChannel::CANChannel(CAN& canBus)
    :_canBus(canBus) {

    tr_info("Creating CANChannel");
  }

  bool CANChannel::send(Message& message) {
    char buffer[MAX_CAN_PACKET_SIZE] = { 0 };
    buffer[0] = message.destination_id();
    buffer[1] = message.entity_id();
    buffer[2] = static_cast<char>(message.type());
    memcpy(buffer+3, message.payload(), message.payload_size());

    int result = _canBus.write(CANMessage(message.source_id(), buffer, 3+message.payload_size()));

    // TODO: Check result + what if fails ? Do we create internal buffer for messages that need to be send ?
  
    call_send_handlers(message);

    return result;
  }

  void CANChannel::receive() {
    CANMessage rawMessage;
    if (_canBus.read(rawMessage)) {
      // Ignore message if minimal fields are missing
      if (rawMessage.len < 3) return;

      Message message;
      message.source_id(rawMessage.id);
      message.destination_id(rawMessage.data[0]);
      message.entity_id(rawMessage.data[1]);
      message.type(static_cast<Message::Type>(rawMessage.data[2]));

      call_receive_handlers(message);
    }
  }

};

#endif