#include "../include/queue.h"

struct queue
queue_init(void (*free)(void *data))
{
    struct queue queue;
    queue.first = NULL;
    queue.last = NULL;
    queue.free = free;
    return queue;
}

void queue_destroy(struct queue *queue)
{
    while (queue->first != NULL) {
        queue_pop(queue);
    }
}

void queue_push(struct queue *queue, void *data, size_t bytes)
{
    struct node *node = node_init(data, bytes, queue->free);
    if (queue->last == NULL) {
        queue->first = queue->last = node;
    }
    else {
        queue->last->next = node;
        queue->last = node;
    }
}

void *queue_peek(struct queue *queue)
{
    if (queue->first == NULL) {
        return NULL;
    }
    return queue->first->data;
    return queue->first->data;
}

void queue_pop(struct queue *queue)
{
    if (queue->first != NULL) {
        struct node *aux = queue->first->next;
        node_destroy(queue->first);
        queue->first = aux;
    }
}

