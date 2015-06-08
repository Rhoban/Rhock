#include <string.h>
#include "obj_write.h"

/**
 * Initializes the structure
 */
void rhock_obj_init(struct rhock_obj *obj)
{
    obj->id = 0;
    obj->crc16 = 0;
    obj->size = 0;
    obj->variables = 0;
    obj->entries = 0;
    obj->name = NULL;
    obj->entry = NULL;
    obj->data = NULL;
}

/**
 * Sets the program id
 */
void rhock_set_id(struct rhock_obj *obj, uint32_t id)
{
    obj->id = id;
}

/**
 * Sets the program name
 */
void rhock_set_name(struct rhock_obj *obj, const char *name)
{
    obj->name = name;
}

/**
 * Sets the default values
 */
void rhock_set_variables(struct rhock_obj *obj, uint8_t *defaults, uint8_t size)
{
    obj->variables = size;
    obj->defaults = defaults;
}

/**
 * Sets the entry data
 */
void rhock_set_entries(struct rhock_obj *obj, uint8_t *entry, uint8_t size)
{
    obj->entries = size;
    obj->entry = entry;
}

/**
 * Sets the data
 */
void rhock_set_data(struct rhock_obj *obj, uint8_t *data, rhock_addr size)
{
    obj->size = size + obj->entries*3 + obj->variables*4 + RHOCK_HEADER;
    obj->data = data;
}

/**
 * Writes the object
 */
void rhock_write(struct rhock_obj *obj, uint8_t *buffer)
{
    uint16_t pos = 0, k;
    obj->crc16 = rhock_obj_crc(obj);

    buffer[pos++] = (obj->id>>24)&0xff;
    buffer[pos++] = (obj->id>>16)&0xff;
    buffer[pos++] = (obj->id>>8)&0xff;
    buffer[pos++] = (obj->id>>0)&0xff;

    buffer[pos++] = (obj->crc16>>8)&0xff;
    buffer[pos++] = (obj->crc16>>0)&0xff;
    
    buffer[pos++] = (obj->size>>8)&0xff;
    buffer[pos++] = (obj->size>>0)&0xff;

    for (k=0; k<RHOCK_OBJ_NAME_SIZE; k++) {
        buffer[pos++] = obj->name[k];
    }
    
    buffer[pos++] = obj->variables;
    for (k=0; k<obj->variables*4; k++) {
        buffer[pos++] = obj->defaults[k];
    }

    buffer[pos++] = obj->entries;
    for (k=0; k<obj->entries*3; k++) {
        buffer[pos++] = obj->entry[k];
    }

    uint16_t data_size = rhock_data_size(obj);
    for (k=0; k<data_size; k++) {
        buffer[pos++] = obj->data[k];
    }
}
