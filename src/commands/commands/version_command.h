#pragma once

#include "Commander.h"
#include "version.h"

namespace BHAS::Commands {

  class VersionCommand : public Commander::Command {

    public:
      VersionCommand(const char* command)
        : Command(command) {
      }
    
    public:
      std::string get() override {
        return  "Firmware version: " BHAS_FIRMWARE_VERSION "\n" "Compilation Date: " __TIMESTAMP__;
      }

  };

};
