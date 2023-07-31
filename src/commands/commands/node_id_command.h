#pragma once

#include "Commander.h"
#include "configuration_manager.h"

namespace BHAS::Commands {

  class NodeIdCommand : public Commander::Command {

    public:
      NodeIdCommand(const char* command, ConfigurationManager& config)
        : Command(command), _config(config) {
      }
    
    public:
      std::string get() override {
        uint8_t nodeId = _config.node_id();
        std::string output = std::to_string(nodeId);
        return output;
      }

      std::string set(std::string argument) override {
        uint8_t nodeId = strtol(argument.data(), NULL, 10);
        _config.node_id((uint32_t)nodeId);
        return Command::SUCCESS_MESSAGE;
      } 

    private:
      ConfigurationManager& _config;

  };

};
