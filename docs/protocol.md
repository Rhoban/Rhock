# Binary protocol

The Rhock binary protocol can be use to communicate with embedded robots.
It supports loading, running and monitoring programs in the virtual machine,
but can also be used for other general purpose.

The format of the frames is:

* HEADER1 (0xFF)
* HEADER2 (0xAA)
* Packet type (1 byte)
* Packet size (1 byte)
* [size] bytes of data
* Checksum (sum of data bytes)

The reserved packet types are:

* 0x00: Ack
* 0x01: Monitor, setting the monitor frequency
* 0x02: Store, commands for the store
* 0x03: Program, controlling the programs
* 0x04: Print, values that are printed by user programs
* 0x06: Reset, erase all the user-defined programs

All the other types can be used by the user for any purpose
