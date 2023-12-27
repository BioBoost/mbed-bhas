#include "router.h"
#include "../logging/trace_logging.h"
#include <sstream>

#define TRACE_GROUP "BHAS Router"

namespace BHAS::Communication {

  Router::Router(Nodes::Node* localNode)
    : _localNode(localNode) {
    
    tr_info("Creating router for node %s", _localNode->to_string().c_str());
  }

  void Router::register_channel(Channel* channel, bool defaultGateway) {
    tr_info("Registering new channel with router: %s", channel->to_string().c_str());
    channel->register_receive_handler(this);

    // Register the loggers on the channel
    channel->register_receive_handler(&_messageLogger);
    channel->register_sent_handler(&_messageLogger);

    if (defaultGateway) {
      _defaultGateway = channel;
    }
  }

  void Router::add_or_update_node(NetworkNode node) {
    if (NetworkNode* existingNode = find_node_by_id(node.id())) {
      existingNode->indicate_active();
    } else {
      _nodes.push_back(node);
    }
  }

  void Router::handle_received_message(Message& message, Channel* channel) {
    tr_debug("Received message on channel %s", channel->to_string().c_str());
    add_or_update_node(NetworkNode(message.source_id(), channel));

    tr_debug("Currently registered nodes in router:");
    tr_debug("|=> %s", to_string().c_str());

    // Check if message is destined for this node
    if (message.destination_id() == _localNode->id() || message.destination_id() == Router::BROADCAST_ID) {
      _localNode->handle_received_message(message, channel);
      if (message.destination_id() == _localNode->id()) return;       // Done here
    }

    // Else route the message further if the resulting interface is not the incoming interface
    Channel* egressChannel = determine_egress_channel(message.destination_id());
    if (egressChannel && egressChannel != channel) {
      tr_debug("Routing message towards it's final destination");
      egressChannel->send(message);
    }
  }

  void Router::send_message(Message& message) {
    // If broadcast then send to all channels
    if (message.destination_id() == Router::BROADCAST_ID) {
      broadcast_message(message);
      return;
    }

    unicast_message(message);
  }

  void Router::unicast_message(Message& message) {
    tr_debug("Sending unicast message");
    Channel* egressChannel = determine_egress_channel(message.destination_id());
    if (!egressChannel) {
      tr_warning("Cannot send message as no Egress channel is found.");
      return;
    }
    egressChannel->send(message);
  }

  void Router::broadcast_message(Message& message) {
    tr_debug("Sending broadcast message");
    for (auto channel : _channels) {
      channel->send(message);
    }
  }

  Channel* Router::determine_egress_channel(uint8_t destinationId) {
    NetworkNode* node = find_node_by_id(destinationId);
    if (!node) return _defaultGateway;
    return node->channel();
  }

  NetworkNode* Router::find_node_by_id(uint8_t id) {
    for (size_t i = 0; i < _nodes.size(); i++) {
      if (_nodes[i].id() == id) return &(_nodes[i]);
    }
    return nullptr;
  }

  std::string Router::to_string() {
    std::stringstream output;
    for(NetworkNode& node : _nodes) {
      output << node.to_string() << std::endl;
    }
    return output.str();
  }

};
