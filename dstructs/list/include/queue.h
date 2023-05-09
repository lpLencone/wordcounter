

#ifndef _QUEUE_H
#define _QUEUE_H

#include "node.h"

struct queue {
    struct node *first;
    struct node *last;
    void (*free)(void *data);
};

struct queue queue_init(void (*free)(void *data));

void queue_destroy(struct queue *queue);

void queue_push(struct queue *queue, void *data, size_t bytes);

void *queue_peek(struct queue *queue);

void queue_pop(struct queue *queue);

#endif /* _QUEUE_H */

