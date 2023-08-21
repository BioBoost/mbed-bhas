#pragma once

#include "message.h"
#include "alive_time_event.h"
#include "temperature_event.h"
#include "button_event.h"

namespace BHAS::Events {

  class EventConvertor {

    public:
      static Communication::Message to_message(AliveTimeEvent event, uint8_t sourceId, uint8_t destinationId);
      static Communication::Message to_message(TemperatureEvent event, uint8_t sourceId, uint8_t destinationId);
      static Communication::Message to_message(ButtonEvent event, uint8_t sourceId, uint8_t destinationId);

  };

};