#pragma once

#include "Commander.h"
#include "configuration_manager.h"

namespace BHAS::Commands {

  class GatewayId : public Commander::Command {

    public:
      GatewayId(const char* command, ConfigurationManager& config)
        : Command(command), _config(config) {
      }
    
    public:
      std::string get() override {
        uint8_t gatewayId = _config.gateway_id();
        std::string output = std::to_string(gatewayId);
        return output;
      }

      std::string set(std::string argument) override {
        uint8_t gatewayId = strtol(argument.data(), NULL, 10);
        _config.gateway_id(gatewayId);
        return Command::SUCCESS_MESSAGE;
      } 

    private:
      ConfigurationManager& _config;

  };

};
