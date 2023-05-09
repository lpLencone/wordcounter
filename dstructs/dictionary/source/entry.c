
#include "../include/entry.h"

#include <stdlib.h>
#include <string.h>

struct entry 
entry_init(void *key, size_t key_bytes, void (*key_print)(void *key), void *value, size_t value_bytes, void (*value_print)(void *value))
{
    struct entry entry;
    entry.key = malloc(key_bytes);
    entry.value = malloc(value_bytes);
    memcpy(entry.key, key, key_bytes);
    memcpy(entry.value, value, value_bytes);
    entry.key_bytes = key_bytes;
    entry.value_bytes = value_bytes;
    entry.key_print = key_print;
    entry.value_print = value_print;
    return entry;
}

void 
entry_destroy(struct entry *entry)
{
    free(entry->key);
    free(entry->value);
}

