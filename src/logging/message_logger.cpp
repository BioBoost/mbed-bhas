#include "message_logger.h"
#include "message_printer.h"

namespace BHAS {

  void MessageLogger::handle_message(const Message & message) const {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    printf("%s\r\n", buffer);
  }

};