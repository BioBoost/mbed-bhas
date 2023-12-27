// The router takes care of sending messages, receiving messages and routing
// messages to other nodes in the network.
//
// If ever the need arises we can easily add message buffering here

#pragma once

#include <cstdint>
#include "../nodes/node.h"
#include "../communication/channels/channel.h"
#include "../communication/i_handle_received_message.h"
#include "network_node.h"
#include "../logging/message_logger.h"

// Forward declaration
namespace BHAS::Nodes {
  class Node;
};

namespace BHAS::Communication {

  class Router : public IHandleReceivedMessage {

    public:
      Router(Nodes::Node* localNode);

    public:
      void register_channel(Channel* channel, bool defaultGateway = false);

    protected:
      void handle_received_message(Message& message, Channel* channel);

    public:
      /**
       * Send a message to the network. If the destination is known
       * then the message is send to a specific channel.
       * If the destination is unknown, then the message is send through
       * the default gateway channel.
       * If the message is to be broadcasted, it is send to all channels.
      */
      void send_message(Message& message);
  
    public:
      std::string to_string();
    
    private:
      void unicast_message(Message& message);
      void broadcast_message(Message& message);
      Channel* determine_egress_channel(uint8_t destinationId);
      NetworkNode* find_node_by_id(uint8_t id);
      void add_or_update_node(NetworkNode node);

    protected:
      static const uint8_t BROADCAST_ID = 255;

    private:
      std::vector<Channel*> _channels;
      Channel* _defaultGateway = nullptr;
      Nodes::Node* _localNode = nullptr;
      std::vector<NetworkNode> _nodes;
      Logging::MessageLogger _messageLogger;
  };

};