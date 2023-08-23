#pragma once

#include "message.h"
#include "action.h"
#include "../entities/events/event.h"

namespace BHAS::Convertors {

  class MessageConvertor {

    public:
      static Communication::Message event_to_message(uint8_t sourceId, uint8_t destinationId, BHAS::Event& event);
      static Action message_to_action(Communication::Message& message);

  };

};