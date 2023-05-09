#include "../include/node.h"

#include <stdlib.h>
#include <string.h>

struct node * 
node_init(void *data, size_t bytes, void (*free)(void *data))
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->prev = NULL;
    node->next = NULL;
    node->data = malloc(bytes);
    memcpy(node->data, data, bytes);
    node->free = free;
    return node;
}

void 
node_destroy(struct node *node)
{
    // Se houver, liberar memória alocada para ponteiros armazenados dentro de `data` com função personalizada
    if (node->free != NULL) {
        // Tal função não deverá liberar a memória do próprio membro
        node->free(node->data);
    }
    free(node->data);
    free(node);
}

