#include "command_manager.h"
#include "node.h"
#include "version_command.h"
#include "reset_command.h"
#include "node_id_command.h"
#include "gateway_id_command.h"
#include "factory_reset_command.h"

namespace BHAS {

  CommandManager::CommandManager(ConfigurationManager& config)
    : _config(config) {

    _commander.addCommand(new Commands::ResetCommand("RESET"));
    _commander.addCommand(new Commands::NodeIdCommand("NODEID", config));
    _commander.addCommand(new Commands::GatewayId("GWID", config));
    _commander.addCommand(new Commands::VersionCommand("VERSION"));
    _commander.addCommand(new Commands::FactoryResetCommand("FACTORYRESET", config));
  }

  void CommandManager::dispatch() {
    _commander.dispatch();
  }

  void CommandManager::on_command(mbed::Callback<void()> cb) {
    _commander.on_command(cb);
  }

};