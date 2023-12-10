#include "node_manager.h"
#include <sstream>

namespace BHAS {

  NodeManager::NodeManager() {}

  void NodeManager::add_or_update_node(Nodes::BaseNode node) {
    if (Nodes::BaseNode* existingNode = find_by_id(node.id())) {
      existingNode->indicate_active();
    } else {
      _nodes.push_back(node);
    }
  }

  Nodes::BaseNode* NodeManager::find_by_id(uint8_t id) {
    for(Nodes::BaseNode& node : _nodes) {
      if (node.id() == id) return &node;
    }
    return nullptr;
  }

  std::string NodeManager::to_string() {
    std::stringstream output;

    for(Nodes::BaseNode& node : _nodes) {
      output << node.to_string() << std::endl;
    }

    return output.str();
  }

};