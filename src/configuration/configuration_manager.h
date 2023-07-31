// Based on https://github.com/vives-dust/firmware

#pragma once

#include "mbed.h"
#include "FlashIAPBlockDevice.h"
#include "TDBStore.h"

namespace BHAS {

  class ConfigurationManager {

    public:
      ConfigurationManager();

    public:
      bool init();

    public:
      void factory_reset();

    public:     // Config params
      uint32_t boot_count();

      uint8_t node_id();
      void node_id(uint8_t id);

      uint8_t gateway_id();
      void gateway_id(uint8_t id);

      bool double_reset();
      void set_double_reset();
      void clear_double_reset();

    private:
      void increment_boot_count();
      void boot_count(uint32_t count);

      uint8_t config_id();
      void config_id(uint8_t id);

    private:
      void check_for_config();

    private:
      FlashIAPBlockDevice _flashBlockDevice;     // Block device for flash
      TDBStore _kvStore;                // KeyValue store for block device

      static constexpr const char* CONFIG_ID_KEY = "cid";
      static constexpr const char* NODE_ID_KEY = "id";
      static constexpr const char* BOOTCOUNT_KEY = "bc";
      static constexpr const char* GATEWAY_ID_KEY = "gid";
      static constexpr const char* DOUBLE_RESET_KEY = "drk";

      static const uint8_t CURRENT_CONFIG_ID = 0x03;     // Basically version of config. Update if params change!

      static const uint8_t DEFAULT_NODE_ID = 1;
      static const uint8_t DEFAULT_GATEWAY_ID = 0;
  };

};