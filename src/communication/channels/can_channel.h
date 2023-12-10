#pragma once

#include "../../bhas_platform.h"
#include "channel.h"

#if defined(PLATFORM_MBED)
#include "InterfaceCAN.h"
#include "mbed.h"
#endif

#if defined(PLATFORM_ESP)
#include "driver/gpio.h"
#endif

namespace BHAS::Communication::Channels {

  class CANChannel : public Channel {

    public:
#if defined(PLATFORM_MBED)
      CANChannel(CAN& canBus);
#endif
#if defined(PLATFORM_ESP)
      CANChannel(gpio_num_t txPin, gpio_num_t rxPin);
#endif

    public:
      bool init();

    public:
      bool send(Message& message);
      void process();   // Need to call this method periodically to receive messages; handlers will be called if registered
    
    private:
#if defined(PLATFORM_MBED)
      CAN& _canBus;
#endif
#if defined(PLATFORM_ESP)
      gpio_num_t _txPin;
      gpio_num_t _rxPin;
      bool _initialized = false;
#endif

  };

};
