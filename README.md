# BHAS - Bio Home Automation System

Mbed library for my Bio Home Automation System (BHAS - pronounced BeeHas). It consists of CAN nodes that are connected to an MQTT enabled master device.

## Nodes

Nodes are basically a representation of the actual hardware platforms. They include the device dependant code.

So we can for example have a node with switches attached, a node that controls a number of relays, ...

In a later stage we will also provide a master node which serves as a gateway to Home Assistant via MQTT.

## Messages

Messages are basically an abstraction of a CAN message.

The general structure is as shown next:

| DESTINATION_ID | SOURCE_ID | ENTITY_ID | MESSAGE_TYPE                           | PAYLOAD |
| 8 bits         | 8 bits    | 8 bits    | BASE TYPE (4 bits) + SUB TYPE (4 bits) | 0-5 bytes |

Where a basic CAN message looks like

![CAN Format](./img/can-format.svg)

*Source: https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial*

Notice that a basic CAN message can only hold 8 bytes of data while we seem to have 9. This difference comes from the fact that the CAN ID is set to the message destination ID. The 3 remaining bits are currently ignored.

* Nodes will typically ignore messages not intended for them, but this is not a must. This allows for logging and sniffing :).
* A destination ID of `255` is considered a broadcast message
* Message type consist of a base type and a sub type. This allows us to differentiate between messages for the base entity and for the more specific entity subclasses.
  * If ever needed, we can probable fit base type in 3 bits to allow for more subtypes

## Entities

Entities are the building blocks of a node. They represent an abstraction of a sensor, relay, led, ... They have a unique id within the scope of the node which can be the source or target of a message.

## Drivers

Drivers contain the hardware dependant code for sensors/actuators/...

## Configuration Storage

### L073RZ

Features:

* 192 KB Flash
* 20 KB SRAM
* Flash = 48 sectors, where 1 sector = 4KB (128 bytes * 32 pages)

Basically you need to allocate multiple of sector size as sector is is the minimal erase size.

See [STM32L0x3 Manual @ page 68](https://www.st.com/resource/en/reference_manual/rm0367-ultralowpower-stm32l0x3-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) for more info

* `MBED_ROM_START`: `0x08000000`
* `MBED_ROM_SIZE`: `0x30000` (192 KB)

[Ch. Tronche](https://tronche.com/blog/2020/03/mbed-flashiap-tdbstore-and-stm32f4-internal-flash/) claims that the underlying TDBStore needs twice the space (multiple of sectors) as it keeps two databases. Basically to cover power failure. Found no actual info on this in the Mbed docs. Needs to be investigated further. Taking two sectors just to be sure for the moment.

So:

* Config size: `8 * 1024 = 8192 bytes`
* Start of storage: `0x08000000 + 0x30000 - 8192`
* Max size of bin: `0x30000 - 8192 = 0x2E000` (about 188 KB which, currently using about 38 KB)

### L476RG

Features:

* 1MB Flash
* 128 KB SRAM
* 256 pages of 2 KB each (2 banks)

Minimal erase size = 2 KB. So need to allocate multiples of this.

See [STM32L47xxxx Manual @ page 97](https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) for more info

* `MBED_ROM_START`: `0x8000000`
* `MBED_ROM_SIZE`: `0x100000` (1.0 MB)

So:

* Config size: `8 * 1024 = 8192 bytes`
* Start of storage: `0x08000000 + 0x100000 - 8192`
* Max size of bin: `0x100000 - 8192 = 0xFE000`

### LPC1768

Probable not correct. **Can't seem to get it to work.**

Features:

* 512KB Flash
* 64 KB SRAM

* `MBED_ROM_START`: `0x0000000` (`LPC_FLASH_BASE`)
* `MBED_ROM_SIZE`: `0x80000` (512KB)

Datasheet states that flash starts at `0x0004 0000` or at `0x0002 0000` [Manual @ page 23](https://www.nxp.com/docs/en/data-sheet/LPC1769_68_67_66_65_64_63.pdf)

So:

* Config size: `8 * 1024 = 8192 bytes`
* Start of storage: `0x0000000 + 0x80000 - 8192`
* Max size of bin: `0x80000 - 8192 = 0x7E000`

## Errors

For some reason I can't seem to override the storage size in `mbed_lib.json`. Adding this fails:

```json
  "NUCLEO_L073RZ": {
    "flashiap-block-device.size": "(8*1024)",
    "flashiap-block-device.base-address": "(MBED_ROM_START + MBED_ROM_SIZE - (8*1024))",
    "target.restrict_size": "0x2E000"
  }
```

## Dependencies

* [commander](https://github.com/BioBoost/mbed-commander): Serial commander library (special thanks @ [sillevl](https://github.com/sillevl))
