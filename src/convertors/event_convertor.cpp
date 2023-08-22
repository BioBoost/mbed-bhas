#include "event_convertor.h"

namespace BHAS::Events {

  Communication::Message EventConvertor::to_message(AliveTimeEvent event, uint8_t sourceId, uint8_t destinationId) {
    Communication::Message message(sourceId, destinationId, event.entity().id(), Communication::Message::BaseType::PERIODIC);

    uint32_t seconds = event.seconds();
    uint8_t payload[] = {
      static_cast<uint8_t>((seconds >> 24) & 0xFF),
      static_cast<uint8_t>((seconds >> 16) & 0xFF),
      static_cast<uint8_t>((seconds >> 8) & 0xFF),
      static_cast<uint8_t>((seconds >> 0) & 0xFF),
    };
    message.payload(payload, sizeof(payload));

    return message;
  }

  Communication::Message EventConvertor::to_message(TemperatureEvent event, uint8_t sourceId, uint8_t destinationId) {
    Communication::Message message(sourceId, destinationId, event.entity().id(), Communication::Message::BaseType::PERIODIC);

    uint8_t payload[] = { static_cast<uint8_t>(event.temperature()) };
    message.payload(payload, sizeof(payload));

    return message;
  }

  Communication::Message EventConvertor::to_message(ButtonEvent event, uint8_t sourceId, uint8_t destinationId) {
    Communication::Message message(sourceId, destinationId, event.entity().id(), Communication::Message::BaseType::EVENT);

    uint8_t payload[] = { static_cast<uint8_t>(event.type()) };
    message.payload(payload, sizeof(payload));

    return message;
  }

};