#include "message_logger.h"
#include "message_printer.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS MessageLogger"

namespace BHAS::Logging {

  void MessageLogger::handle_received_message(Communication::Message& message, Communication::Channel* channel) {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    tr_debug("Received message via %s: %s", channel->to_string().c_str(), buffer);
  }

  void MessageLogger::handle_sent_message(Communication::Message& message, Communication::Channel* channel) {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    tr_debug("Send message via %s: %s", channel->to_string().c_str(), buffer);
  }

};