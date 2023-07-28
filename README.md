# BHAS - Bio Home Automation System

Mbed library for my Bio Home Automation System (BHAS - pronounced BeeHas). It consists of CAN nodes that are connected to an MQTT enabled master device.

## Nodes

Nodes are basically a representation of the actual hardware platforms. They include the device dependant code.

So we can for example have a node with switches attached, a node that controls a number of relays, ...

In a later stage we will also provide a master node which serves as a gateway to Home Assistant via MQTT.

## Messages

Messages are basically an abstraction of a CAN message.

The general structure is as shown next:

| DESTINATION_ID | SOURCE_ID | ENTITY_ID | MESSAGE_TYPE | PAYLOAD |
| 8 bits         | 8 bits    | 8 bits    | 8 bits       | 0-5 bytes |

Where a basic CAN message looks like

![CAN Format](./img/can-format.svg)

*Source: https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial*

Notice that a basic CAN message can only hold 8 bytes of data while we seem to have 9. This difference comes from the fact that the CAN ID is set to the message destination ID. The 3 remaining bits are currently ignored.

* Nodes will typically ignore messages not intended for them, but this is not a must. This allows for logging and sniffing :).
* A destination ID of `255` is considered a broadcast message
* Message types currently include:
  * NONE: `0x00`
  * HELLO: `0x01`
  * EVENT: `0x02`
  * ALERT: `0x03`
  * CONFIG: `0x04`
  * PERIODIC: `0x05`
  * WARNING: `0x06`
  * ERROR: `0x07`
  * ALIVE: `0x08`

For the moment only `EVENT` and `PERIODIC` messages are used.

## Entities

Entities are the building blocks of a node. They represent an abstraction of a sensor, relay, led, ... They have a unique id within the scope of the node which can be the source or target of a message.

## Drivers

Drivers contain the hardware dependant code for sensors/actuators/...
