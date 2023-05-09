#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include "entry.h"
#include "../../list/include/list.h"

#include <stddef.h>

enum query 
{
    KEY,
    VALUE
};

struct dictionary
{
    struct list entries;
    void (*key_print)(void *key);
    void (*value_print)(void *value);
};

struct dictionary dictionary_init(void (*key_print)(void *key), void (*value_print)(void *value));

void dictionary_destroy(struct dictionary *dictionary);

void dictionary_add(struct dictionary *dictionary, void *key, size_t key_bytes, void *value, size_t value_bytes);

void dictionary_print(struct dictionary *dictionary);

void dictionary_quicksort(struct dictionary *dictionary, enum query query);

void *dictionary_query(struct dictionary *dictionary, void *key, size_t bytes);

void dictionary_alter(struct dictionary *dictionary, void *key, size_t key_bytes, void *value, size_t value_bytes);

#endif /* _DICTIONARY_H */

