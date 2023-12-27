#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
#include "entity.h"
#include "../communication/channels/channel.h"

namespace BHAS::Entities {

  class ChannelEntity : public Entity {

    public:
      ChannelEntity(uint8_t id, EventQueue& queue, Communication::Channel& channel, EventQueue::duration reportTime = 500s, std::string description = "");

    public:
      virtual std::string name() const override;

    private:
      void notify_report_stats();

    private:
      Communication::Channel& _channel;

  };

};

#endif
