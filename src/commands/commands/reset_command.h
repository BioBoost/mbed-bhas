#pragma once

#include "Commander.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS COMMANDS"

namespace BHAS::Commands {

  class ResetCommand : public Commander::Command {

    public:
      ResetCommand(const char* command)
        : Command(command) {
      }
    
    public:
      std::string action() override {
        tr_info("Resetting device");
        ThisThread::sleep_for(500ms);
        NVIC_SystemReset();
        return Command::SUCCESS_MESSAGE;
      }

  };

};
