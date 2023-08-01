#pragma once

#include "Commander.h"
#include "mbed.h"
#include "mbed_trace.h"
#include "configuration_manager.h"

#define TRACE_GROUP "BHAS COMMANDS"

namespace BHAS::Commands {

  class FactoryResetCommand : public Commander::Command {

    public:
      FactoryResetCommand(const char* command, ConfigurationManager& config)
        : Command(command), _config(config) {
      }
    
    public:
      std::string action() override {
        _config.factory_reset();
        ThisThread::sleep_for(500ms);
        NVIC_SystemReset();
        return Command::SUCCESS_MESSAGE;
      }

    private:
      ConfigurationManager& _config;

  };

};
