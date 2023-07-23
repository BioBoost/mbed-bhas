#pragma once

#include "mbed_events.h"
#include <stdio.h>
#include "InterfaceCAN.h"
#include "message.h"
#include "can_communication_channel.h"
#include "message_printer.h"
#include "message_logger.h"
#include "push_button.h"
#include "entity_event_handler.h"
#include "entity_event.h"

namespace BHAS {

  class Node : public BHAS::EntityEventHandler {
    public:
      Node()
      : _canBus(D15, D14), _canChannel(_canBus){

        _canChannel.register_receive_handler(_messageLogger);
        _canChannel.register_send_handler(_messageLogger);
      }

    public:
      void take_over() {
        // events are executed by the dispatch_forever method
        _queue.dispatch_forever();
      }

    public:

      void handle_event(BHAS::EntityEvent event) {
        // Warning! This runs in IRQ context. Need to schedule event handler
        _queue.call(callback(this, &Node::process_event), event);
      }

      void process_event(BHAS::EntityEvent event) {
        // TODO: Send via CAN bus
        printf("Now we got event in event loop thread context! => id = %d\r\n", event.entity()->id());
      }

    private:
      void register_entities() {
        // TODO: Based on config ?
        _entities.push_back(BHAS::PushButton(13, D7, this));
      }

    private:
      CAN _canBus;
      BHAS::CANCommunicationChannel _canChannel;
      BHAS::MessageLogger _messageLogger;
      EventQueue _queue;
      std::vector<BHAS::Entity> _entities;
  };  

};