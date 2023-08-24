#if !DEVICE_CAN
#warning [NOT_SUPPORTED] CAN not supported for this target
#else

#include "can_channel.h"
#include "mbed.h"
#include "InterfaceCAN.h"
#include "mbed_trace.h"
#include "can_encoder.h"

#define TRACE_GROUP "BHAS CANChannel"

namespace BHAS::Communication::Channels {

  CANChannel::CANChannel(CAN& canBus)
    :_canBus(canBus) {

    tr_info("Creating CANChannel");
  }

  bool CANChannel::send(Message& message) {
    int result = _canBus.write(
      Encoders::CANEncoder::message_to_can_message(message)
    );

    // TODO: Check result + what if fails ? Do we create internal buffer for messages that need to be send ?
  
    if (result) call_send_handlers(message);

    return result;
  }

  void CANChannel::receive() {
    CANMessage rawMessage;
    if (_canBus.read(rawMessage)) {
      if (rawMessage.len < 3) return;   // Ignore message if minimal fields are missing

      Message message = Encoders::CANEncoder::can_message_to_message(rawMessage);
      call_receive_handlers(message);
    }
  }

};

#endif