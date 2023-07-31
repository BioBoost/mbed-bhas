#pragma once

#include "configuration_manager.h"
#include "Commander.h"
#include "node.h"

namespace BHAS {

  class CommandManager {

    public:
      CommandManager(ConfigurationManager& config);

    public:
      void dispatch();

    public:
      void on_command(mbed::Callback<void()> cb);

    private:
      Commander::Commander _commander;
      ConfigurationManager& _config;
  };

};
