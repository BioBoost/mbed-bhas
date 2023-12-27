#include "network_node.h"
#include <time.h>

namespace BHAS::Communication {

  NetworkNode::NetworkNode(uint8_t id, Channel* channel)
    : _id(id), _channel(channel) {

  }

  void NetworkNode::indicate_active() {
    _lastActiveTime = time(NULL);
  }

  std::string NetworkNode::to_string() {
    uint64_t secondsAlive = static_cast<uint64_t>(difftime(time(NULL), _lastActiveTime));
    return "Network Node [nid: " + std::to_string(_id) + "] last seen " + std::to_string(secondsAlive) + " seconds ago.";
  }

};