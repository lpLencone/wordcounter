#ifndef _NODE_H
#define _NODE_H

#include <stddef.h>

struct node
{
    struct node *prev;
    struct node *next;
    void *data;
    void (*free)(void *data);
};

struct node *node_init(void *data, size_t bytes, void (*free)(void *data));
void node_destroy(struct node *node);

#endif /* _NODE_H */

