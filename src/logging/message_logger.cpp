#include "message_logger.h"
#include "message_printer.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS MessageLogger"

namespace BHAS::Logging {

  void MessageLogger::handle_received_message(Communication::Message& message) const {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    tr_debug("Received message: %s", buffer);
  }

  void MessageLogger::handle_send_message(Communication::Message& message) const {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    tr_debug("Send message: %s", buffer);
  }

};