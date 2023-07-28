#include "message_logger.h"
#include "message_printer.h"

namespace BHAS::Logging {

  void MessageLogger::handle_received_message(Communication::Message& message) const {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    printf("RECEIVED: %s\r\n", buffer);
  }

  void MessageLogger::handle_send_message(Communication::Message& message) const {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    printf("SENT: %s\r\n", buffer);
  }

};