idf_component_register(SRCS
  "communication/message.cpp"
  "communication/channels/channel.cpp"
  "communication/channels/local_echo_channel.cpp"
  "communication/channels/can_channel.cpp"
  "nodes/master_node.cpp"
  "node_manager/base_node.cpp"
  "node_manager/node_manager.cpp"
  "logging/message_logger.cpp"
  INCLUDE_DIRS "."
  REQUIRES driver nlohmann)