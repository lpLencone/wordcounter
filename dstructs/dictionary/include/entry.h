
#ifndef _ENTRY_H
#define _ENTRY_H

#include <stddef.h>

struct entry
{
    void *key;
    size_t key_bytes;
    void *value;
    size_t value_bytes;
    void (*key_print)(void *key);
    void (*value_print)(void *value);
};

struct entry entry_init(void *key, size_t key_bytes, void (*key_print)(void *key), void *value, size_t value_bytes, void (*value_print)(void *value));

void entry_destroy(struct entry *entry);

#endif /* _ENTRY_H */

