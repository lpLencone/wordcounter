#ifndef _LIST_H
#define _LIST_H

#include "node.h"

struct list
{
    struct node *head;
    struct node *tail;
    int tamanho;
    void (*free)(void *data);
    int (*compare)(void *data, void *data2, size_t bytes);
    void (*print)(void *data);
};

struct list list_init(
    void (*free)(void *data), 
    int (*compare)(void *data, void *data2, size_t bytes), 
    void (*print)(void *data)
);

void list_destroy(struct list *list);

void list_add(struct list *list, void *data, size_t bytes);

void *list_query(
    struct list *list, 
    void *data, 
    size_t bytes,
    int (*compare)(void *data, void *data2, size_t bytes)
);

void *list_index(struct list *list, int index);

void list_print(struct list *list);

void list_quicksort(
    struct list *list, 
    size_t bytes, 
    int (*compare)(void *data, void *data2, size_t bytes)
);

#endif /* _LIST_H */

