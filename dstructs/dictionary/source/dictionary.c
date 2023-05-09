
#include "../include/dictionary.h"

#include <stdio.h>
#include <string.h>

void __destroy_entry(void *entry);
int __compare_entry_key(void *entry, void *key, size_t bytes);
int __compare_entry_value(void *data1, void *data2, size_t bytes);
void __print_entry(void *data);
struct entry *__get_entry(struct dictionary *dictionary, void *key, size_t bytes);

typedef int (*fn_compare)(void *data, void *data2, size_t bytes);
fn_compare __set_compare(enum query query);

struct dictionary
dictionary_init(void (*key_print)(void *key), void (*value_print)(void *value))
{
    struct dictionary dictionary;
    dictionary.entries = list_init(__destroy_entry, __compare_entry_key, __print_entry);
    dictionary.key_print = key_print;
    dictionary.value_print = value_print;
    return dictionary;
}

void
dictionary_destroy(struct dictionary *dictionary)
{
    list_destroy(&dictionary->entries);
}

void
dictionary_add(struct dictionary *dictionary, void *key, size_t key_bytes, void *value, size_t value_bytes)
{
    struct entry *query = __get_entry(dictionary, key, key_bytes);
    if (query != NULL) {
        printf("Registro já existe.\n");
        return;
    }
    struct entry entry = entry_init(key, key_bytes, dictionary->key_print, value, value_bytes, dictionary->value_print);
    list_add(&dictionary->entries, &entry, sizeof(struct entry));
}

void *
dictionary_query(struct dictionary *dictionary, void *key, size_t bytes)
{
    struct entry *entry = __get_entry(dictionary, key, bytes);
    if (entry != NULL) {
        return entry->value;
    }
    return NULL;
}

void
dictionary_alter(struct dictionary *dictionary, void *key, size_t key_bytes, void *value, size_t value_bytes)
{
    struct entry *entry = __get_entry(dictionary, key, key_bytes);
    if (entry == NULL) {
        printf("Registro não existe.\n");
        return;
    }
    memcpy(entry->value, value, value_bytes);
}

void
dictionary_print(struct dictionary *dictionary)
{
    list_print(&dictionary->entries);
}

void
dictionary_quicksort(struct dictionary *dictionary, enum query query)
{
    int (*compare)(void *data, void *data2, size_t bytes);
    compare = __set_compare(query);
    list_quicksort(&dictionary->entries, 0, compare);
}

void
__destroy_entry(void *entry)
{
    entry_destroy((struct entry *)entry);
}

int
__compare_entry_key(void *data1, void *data2, size_t bytes)
{
    struct entry *entry1 = (struct entry *)data1;
    struct entry *entry2 = (struct entry *)data2;
    void *key1 = entry1->key;
    void *key2 = entry2->key;
    bytes = (entry1->key_bytes > entry2->key_bytes) ? 
             entry1->key_bytes : entry2->key_bytes;
    return memcmp(key1, key2, bytes);
}

int
__compare_entry_value(void *data1, void *data2, size_t bytes)
{
    struct entry *entry1 = (struct entry *)data1;
    struct entry *entry2 = (struct entry *)data2;
    void *value1 = entry1->value;
    void *value2 = entry2->value;
    bytes = (entry1->value_bytes > entry2->value_bytes) ? 
             entry1->value_bytes : entry2->value_bytes;
    return memcmp(value1, value2, bytes);
}

void 
__print_entry(void *data)
{
    struct entry *entry = (struct entry *)data;
    void *key = entry->key;
    void *value = entry->value;
    entry->key_print(key);
    entry->value_print(value);
}

fn_compare 
__set_compare(enum query query)
{
    int (*compare)(void *data, void *data2, size_t bytes);
    if (query == KEY) {
        compare = __compare_entry_key;
    }
    else if (query == VALUE) {
        compare = __compare_entry_value;
    }
    else {
        return NULL;
    }
    return compare;
}

struct entry *
__get_entry(struct dictionary *dictionary, void *key, size_t bytes)
{
    int query_value = 0;
    struct entry query = entry_init(key, bytes, NULL, &query_value, sizeof(int), NULL);
    struct entry *entry = (struct entry *)list_query(&dictionary->entries, &query, bytes, NULL);
    entry_destroy(&query);
    return entry;
}

