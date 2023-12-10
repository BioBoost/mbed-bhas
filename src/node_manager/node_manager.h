#pragma once

#include <cstdint>
#include <vector>
#include "base_node.h"
#include <string>

namespace BHAS {

  class NodeManager {

    public:
      NodeManager();

    public:
      void add_or_update_node(Nodes::BaseNode node);
    
    public:
      Nodes::BaseNode* find_by_id(uint8_t id);

    public:
      std::string to_string();

    private:
      std::vector<Nodes::BaseNode> _nodes;

  };

};