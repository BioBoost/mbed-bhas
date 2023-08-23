#include "message_convertor.h"

namespace BHAS::Convertors {

  Communication::Message MessageConvertor::event_to_message(uint8_t sourceId, uint8_t destinationId, BHAS::Event& event) {
    Communication::Message message(sourceId, destinationId, event.entity().id(), Communication::Message::BaseType::EVENT, static_cast<uint8_t>(event.type()));
    message.payload(&event.arguments()[0], event.arguments().size());
    return message;
  }

  Action MessageConvertor::message_to_action(Communication::Message& message) {
    std::vector<uint8_t> args;
    for (size_t i = 0; i < message.payload_size(); i++) {
      args.push_back(message.payload()[i]);
    }
    Action action(static_cast<Action::Type>(message.sub_type()), args);
    return action;
  }

};