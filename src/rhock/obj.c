#include "print.h"
#include "obj.h"
#include "crc16.h"

struct rhock_obj *rhock_get_obj(rhock_memory_addr addr)
{
    return (struct rhock_obj *)rhock_get(addr, 0);
}

struct crc_comp
{
    uint8_t present;
    uint8_t byte;
    uint16_t crc;
};

static void crc_push_byte(struct crc_comp *crc, uint8_t byte)
{
    if (crc->present) {
        crc->crc = crc16_update(crc->crc, (crc->byte<<16)|byte);
        crc->present = 0;
    } else {
        crc->byte = byte;
        crc->present = 1;
    }
}

uint16_t rhock_obj_crc(struct rhock_obj *obj)
{
    uint16_t k, data_size;
    struct crc_comp crc;
    crc.crc = 0;
    crc.present = 0;

    crc_push_byte(&crc, (obj->id>>24)&0xff);
    crc_push_byte(&crc, (obj->id>>16)&0xff);
    crc_push_byte(&crc, (obj->id>>8)&0xff);
    crc_push_byte(&crc, (obj->id)&0xff);

    crc_push_byte(&crc, (obj->size>>8)&0xff);
    crc_push_byte(&crc, obj->size&0xff);

    for (k=0; k<RHOCK_OBJ_NAME_SIZE; k++) {
        crc_push_byte(&crc, obj->name[k]);
    }

    crc_push_byte(&crc, obj->variables);
    crc_push_byte(&crc, obj->entries);

    for (k=0; k<obj->entries*3; k++) {
        crc_push_byte(&crc, obj->entry[k]);
    }

    for (k=0; k<obj->variables*4; k++) {
        crc_push_byte(&crc, obj->defaults[k]);
    }

    data_size = rhock_data_size(obj);
    for (k=0; k<data_size; k++) {
        crc_push_byte(&crc, obj->data[k]);
    }

    if (crc.present) {
        crc_push_byte(&crc, 0);
    }

    return crc.crc;
}

uint16_t rhock_data_size(struct rhock_obj *obj)
{
    return obj->size - obj->entries*3 - obj->variables*4 - RHOCK_HEADER;
}

uint8_t rhock_obj_load(struct rhock_obj *obj, const uint8_t *data, uint32_t size)
{
    uint16_t k = 0;
    obj->start = data;

    if (size < RHOCK_HEADER) {
        return 0;
    }

    obj->id = data[k++]<<24;
    obj->id |= data[k++]<<16;
    obj->id |= data[k++]<<8;
    obj->id |= data[k++]<<0;

    obj->crc16 = data[k++]<<8;
    obj->crc16 |= data[k++]<<0;

    obj->size = data[k++]<<8;
    obj->size |= data[k++]<<0;

    if (obj->size != size) {
        return 0;
    }

    obj->name = (const char*)&data[k];
    k += RHOCK_OBJ_NAME_SIZE;

    obj->variables = data[k++];
    obj->defaults = data+k;
    k += obj->variables*4;

    obj->entries = data[k++];

    obj->entry = data+k;
    k += obj->entries * 3;

    obj->data = data+k;

    return rhock_obj_crc(obj)==obj->crc16;
}

uint16_t rhock_obj_guess_size(const uint8_t *data)
{
    return 
         (data[6]<<8)
        |(data[7])
        ;
}

uint8_t rhock_entry_initial(struct rhock_obj *obj, rhock_entry n)
{
    return obj->entry[3*n];
}

rhock_addr rhock_entry_addr(struct rhock_obj *obj, rhock_entry n)
{
    return (obj->entry[3*n+1]<<8)|obj->entry[3*n+2];
}

rhock_value rhock_default_value(struct rhock_obj *obj, rhock_var num)
{
    int i;

    i = (obj->defaults[4*num+0])<<24;
    i |= (obj->defaults[4*num+1])<<16;
    i |= (obj->defaults[4*num+2])<<8;
    i |= (obj->defaults[4*num+3])<<0;

    return i;
}
