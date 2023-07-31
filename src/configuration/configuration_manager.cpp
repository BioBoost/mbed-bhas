// Based on https://github.com/vives-dust/firmware
// More info: https://tronche.com/blog/2020/03/mbed-flashiap-tdbstore-and-stm32f4-internal-flash/

#include "configuration_manager.h"
#include "mbed_trace.h"
#include <stdint.h>

#define TRACE_GROUP "BHAS ConfigurationManager"

namespace BHAS::Config {

  ConfigurationManager::ConfigurationManager()
    : _flashBlockDevice(), _kvStore(&_flashBlockDevice) {

  }

  bool ConfigurationManager::init() {
    int result = _flashBlockDevice.init();
    if (result != MBED_SUCCESS) {
      tr_error("Failed to initialize Flash Block Device with status = %d", result);
      return false;
    }
    tr_debug("Successfully initialized Flash Block Device with size = %llu bytes", _flashBlockDevice.size());

    result = _kvStore.init();
    if (result != MBED_SUCCESS) {
      tr_error("Failed to initialize KeyValue store with status = %d", result);
      return false;
    }
    tr_debug("Successfully initialized KeyValue store");

    check_for_config();
    increment_boot_count();

    return true;
  }

  void ConfigurationManager::check_for_config() {
    if (config_id() == 0) {
      tr_warning("No configuration found.");
      factory_reset();
      tr_debug("Resetting the device");
      ThisThread::sleep_for(2s);
      NVIC_SystemReset();
    } else if (config_id() < CURRENT_CONFIG_ID) {
      tr_warning("Configuration in Flash is outdated.");
      // TODO: Upgrade procedure ?
      factory_reset();
      tr_debug("Resetting the device");
      ThisThread::sleep_for(2s);
      NVIC_SystemReset();
    }

    tr_info("Device configuration found in flash with id = %d", config_id());
  }

  void ConfigurationManager::factory_reset() {
    tr_info("Performing factory reset. Please configure the device!");

    uint32_t bootCount = boot_count();

    // Reset all values
    _kvStore.reset();

    // Restore boot count
    boot_count(bootCount);

    // Set the config id
    config_id(CURRENT_CONFIG_ID);

    // Set the defaults
    node_id(DEFAULT_NODE_ID);
    gateway_id(DEFAULT_GATEWAY_ID);
  }

  uint32_t ConfigurationManager::boot_count() {
    uint32_t bootCount = 0;
    _kvStore.get(BOOTCOUNT_KEY, &bootCount, sizeof(bootCount));
    return bootCount;
  }

  void ConfigurationManager::increment_boot_count() {
    uint32_t bootCount = boot_count();
    boot_count(bootCount+1);
  }

  void ConfigurationManager::boot_count(uint32_t count) {
    _kvStore.set(BOOTCOUNT_KEY, &count, sizeof(count), 0);
  }

  uint8_t ConfigurationManager::node_id() {
    uint8_t nodeId = DEFAULT_NODE_ID;
    _kvStore.get(NODE_ID_KEY, &nodeId, sizeof(nodeId));
    return nodeId;
  }

  void ConfigurationManager::node_id(uint8_t id) {
    _kvStore.set(NODE_ID_KEY, &id, sizeof(id), 0);
  }

  uint8_t ConfigurationManager::gateway_id() {
    uint8_t nodeId = DEFAULT_GATEWAY_ID;
    _kvStore.get(GATEWAY_ID_KEY, &nodeId, sizeof(nodeId));
    return nodeId;
  }

  void ConfigurationManager::gateway_id(uint8_t id) {
    _kvStore.set(GATEWAY_ID_KEY, &id, sizeof(id), 0);
  }

  uint8_t ConfigurationManager::config_id() {
    uint8_t configId = 0;
    _kvStore.get(CONFIG_ID_KEY, &configId, sizeof(configId));
    return configId;
  }

  void ConfigurationManager::config_id(uint8_t id) {
    _kvStore.set(CONFIG_ID_KEY, &id, sizeof(id), 0);
  }

};