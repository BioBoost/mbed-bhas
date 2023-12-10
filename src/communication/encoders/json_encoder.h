#pragma once
#include "../../bhas_platform.h"

#include "../message.h"
#include <string>
#include "../../logging/message_printer.h"
#include "../../helpers/string_convertor.h"

#if defined(PLATFORM_ESP)
#include "nlohmann_json.hpp"
#endif

namespace BHAS::Communication::Encoders {

  class JSONEncoder {

    public:
      static std::string message_to_json_string(const Message& message) {

#if defined(PLATFORM_ESP)
        using json = nlohmann::json;
        using Logging::MessagePrinter;

        json jsonObj;
        jsonObj["gateway_id"] = message.destination_id();
        jsonObj["source_id"] = message.source_id();
        jsonObj["entity_id"] = message.entity_id();
        jsonObj["extended_id"] = message.extended_id();
        jsonObj["basetype"] = StringConvertor::message_base_type_as_string(message.base_type());
        jsonObj["subtype"] = StringConvertor::message_sub_type_as_string(message);

        const uint8_t * payload = message.payload();
        for (size_t i = 0; i < message.payload_size(); i++) {
          jsonObj["payload"].push_back(payload[i]);
        }

        return jsonObj.dump();
#else
        return "JSON not supported on this platform";     // TODO: We could do this without nlohmann
#endif

      }

  };

};