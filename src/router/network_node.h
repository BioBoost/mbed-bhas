#pragma once

#include <cstdint>
#include <string>
#include "../communication/channels/channel.h"

namespace BHAS::Communication {

  class NetworkNode {

    public:
      NetworkNode(uint8_t id, Channel* channel);

    public:
      void indicate_active();

    public:
      uint8_t id() const { return _id; };
      Channel* channel() const { return _channel; }

    public:
      std::string to_string();

    private:
      uint8_t _id = 0;
      time_t _lastActiveTime = 0;
      Channel* _channel = nullptr;
  };

};