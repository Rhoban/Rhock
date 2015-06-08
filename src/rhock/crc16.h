#ifndef _RHOCK_OBJ_CRC
#define _RHOCK_OBJ_CRC

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint16_t crc16_update(uint16_t crc_accum, uint16_t new_data);

#ifdef __cplusplus
}
#endif

#endif
