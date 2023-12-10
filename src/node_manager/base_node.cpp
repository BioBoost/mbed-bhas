#include "base_node.h"
#include <time.h>

namespace BHAS::Nodes {

  BaseNode::BaseNode(uint8_t id)
    : _id(id) {

  }

  void BaseNode::indicate_active() {
    _lastActiveTime = time(NULL);
  }

  uint8_t BaseNode::id() const {
    return _id;
  }

  std::string BaseNode::to_string() {
    uint64_t secondsAlive = static_cast<uint64_t>(difftime(time(NULL), _lastActiveTime));
    return "Node [nid: " + std::to_string(_id) + "] last seen " + std::to_string(secondsAlive) + " seconds ago.";
  }

};