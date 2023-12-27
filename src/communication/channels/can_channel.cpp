#include "can_channel.h"
#include "../../logging/trace_logging.h"
#include "../encoders/can_encoder.h"

#define TRACE_GROUP "BHAS CANChannel"

#if defined(PLATFORM_MBED)
#include "mbed.h"
#include "InterfaceCAN.h"
#endif
#if defined(PLATFORM_ESP) 
#include "driver/twai.h"
#endif

// TODO: Provide a reset we can call from the router if needed. Seems if no receiver is attached the bus eventually gets stuck.

namespace BHAS::Communication::Channels {

#if defined(PLATFORM_MBED)
  CANChannel::CANChannel(CAN& canBus)
    :_canBus(canBus) {

    tr_info("Creating CANChannel");
    _canBus.frequency(100*1000);
  }

  bool CANChannel::init() {
    return true;
  }

  bool CANChannel::send(Message& message) {
    int result = _canBus.write(
      Encoders::CANEncoder::message_to_can_message(message)
    );

    // TODO: Check result + what if fails ? Do we create internal buffer for messages that need to be send ?
  
    if (result) call_send_handlers(message);

    return result;
  }

  void CANChannel::process() {
    CANMessage rawMessage;
    if (_canBus.read(rawMessage)) {
      if (rawMessage.len < 3) return;   // Ignore message if minimal fields are missing

      Message message = Encoders::CANEncoder::can_message_to_message(rawMessage);
      call_receive_handlers(message);
    }
  }
#endif

#if defined(PLATFORM_ESP) 
  CANChannel::CANChannel(gpio_num_t txPin, gpio_num_t rxPin)
    : _txPin(txPin), _rxPin(rxPin) {
  }

  bool CANChannel::init() {
    //Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(_txPin, _rxPin, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
      // TODO: Error message ?
      _initialized = false;
      return false;
    }

    if (twai_start() != ESP_OK) {
      // TODO: Error message ?
      _initialized = false;
      return false;
    }

    _initialized = true;
    return true;
  }

  bool CANChannel::send(Message& message) {
    twai_message_t canMessage = Encoders::CANEncoder::message_to_can_message(message);
    esp_err_t result = twai_transmit(&canMessage, pdMS_TO_TICKS(100));

    // TODO: Check result + what if fails ? Do we create internal buffer for messages that need to be send ?
  
    if (result == ESP_OK) call_send_handlers(message);

    return result == ESP_OK;
  }

  void CANChannel::process() {
    twai_message_t canMessage;
    if (twai_receive(&canMessage, pdMS_TO_TICKS(10)) == ESP_OK) {
      Message message = Encoders::CANEncoder::can_message_to_message(canMessage);
      call_receive_handlers(message);
    }
  }
#endif

};