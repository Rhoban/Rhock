# Object format

[« Back to the index](index.md)

The object is formed with an header (all data are MSB first):

* 4 bytes: `id`, an identifier that identifies the program, it
  should be different for each loaded program. It could be generated using
  UNIX timestamps for example.

* 2 bytes: `crc16`, checksum of the whole binary. Replace these two bytes
  with zero before computing the checksum. If the size is not a multiple of 2,
  padd it with zeros for computing crc16.

* 2 bytes: `size`, the size of the whole binary, header included.

* 16 bytes: `name`, the name of the scene. It should be ascii characters,
  padded with 0s.

* 1 bytes: `variables`, the number of variables to allocate.

* 1 byte: `entries` the number of entry points
* For each entry (`entries` time):
    * 1 byte, `type` the type of the entry (see below)
    * 2 bytes, `addr` the address of the corresponding entry

* Data zone

Note that:

* The address are 16 bits, relative to the begining of the entries zone (thus, the first
  entry will begin at address 0)
* The minimal header size is 27 bytes, including no entry. 
  Thus the minimal object file is 27 bytes.

## Sections types

There is 4 entry types:

* (`0x00`) `normal`, a entry executed when the program is runned, paused when it's paused
* (`0x01`) `stop`, the entry that is executed when stopped
* (`0x02`) `pause`, the entry that is executed when paused
