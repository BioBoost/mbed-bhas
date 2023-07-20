#include "can_communication_channel.h"
#include "InterfaceCAN.h"
#include "mbed.h"

namespace BHAS {

  CANCommunicationChannel::CANCommunicationChannel(CAN & canBus)
    :_canBus(canBus) {
  }

  bool CANCommunicationChannel::send(const Message & message) {
    char buffer[MAX_CAN_PACKET_SIZE] = { 0 };
    buffer[0] = message.destination_id();
    buffer[1] = message.entity_id();
    buffer[2] = static_cast<char>(message.type());
    memcpy(buffer+3, message.payload(), message.payload_size());

    int result = _canBus.write(CANMessage(message.source_id(), buffer, 3+message.payload_size()));
  
    call_handlers(_sendHandlers, message);

    return result;
  }

  void CANCommunicationChannel::receive() {
    CANMessage rawMessage;
    if (_canBus.read(rawMessage)) {
      // Ignore message if minimal fields are missing
      if (rawMessage.len < 3) return;

      Message message;
      message.source_id(rawMessage.id);
      message.destination_id(rawMessage.data[0]);
      message.entity_id(rawMessage.data[1]);
      message.type(static_cast<Message::Type>(rawMessage.data[2]));

      call_handlers(_receiveHandlers, message);
    }
  }

  void CANCommunicationChannel::register_receive_handler(IMessageHandler & handler) {
    _receiveHandlers.push_back(handler);
  }

  void CANCommunicationChannel::register_send_handler(IMessageHandler & handler) {
    _sendHandlers.push_back(handler);
  }

  void CANCommunicationChannel::call_handlers(std::vector<std::reference_wrapper<IMessageHandler>> & handlers, const Message & message) const {
    for (auto handler : handlers) {
      handler.get().handle_message(message);
    }
  }

};