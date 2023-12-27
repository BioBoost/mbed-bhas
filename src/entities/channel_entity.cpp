#include "channel_entity.h"

#if defined(PLATFORM_MBED)

namespace BHAS::Entities {

  ChannelEntity::ChannelEntity(uint8_t id, EventQueue& queue, Communication::Channel& channel, EventQueue::duration reportTime, std::string description)
    : Entity(id, description), _channel(channel) {

    queue.call_every(reportTime, callback(this, &ChannelEntity::notify_report_stats));
  }

  void ChannelEntity::notify_report_stats() {
    // TODO: Request send and receive counter from the entity itself
    Event event(*this, Event::Type::CHANNEL_STATS, { 0xDE, 0xAD });
    call_event_handler(event);
  }

  std::string ChannelEntity::name() const {
    // TODO: Maybe request type from channel itself or something?
    return "ChannelEntity";
  }

};

#endif
