
#include "../include/list.h"
#include "../../../utils/util.h"

#include <stdio.h>

void 
__quicksort_recursive(struct node *head, struct node *tail, size_t bytes, int (*compare)(void *data, void *data2, size_t bytes));

struct list 
list_init(void (*free)(void *data), int (*compare)(void *data, void *data2, size_t bytes), void (*print)(void *data))
{
    struct list list;
    list.head = NULL;
    list.tail = NULL;
    list.tamanho = 0;
    list.free = free;
    list.compare = compare;
    list.print = print;
    return list;
}

void 
list_destroy(struct list *list)
{
    if (list->head == NULL) {
        return;
    }
    struct node *aux = list->head;
    struct node *aux2;
    while (aux != NULL) {
        aux2 = aux->next;
        node_destroy(aux);
        aux = aux2;
    }
}

void
list_add(struct list *list, void *data, size_t bytes)
{
    struct node *node = node_init(data, bytes, list->free);
    if (list->tamanho == 0) {
        list->head = node;
    }
    else {
        node->prev = list->tail;
        list->tail->next = node;
    }
    list->tail = node;
    list->tamanho++;
}

void *
list_query(struct list *list, void *data, size_t bytes, int (*compare)(void *data, void *data2, size_t bytes))
{
    int (*__compare)(void *data, void *data2, size_t bytes);
    __compare = (int (*)())set_fn(2, compare, list->compare);

    struct node *aux = list->head;
    while (aux != NULL) {
        int resultado = __compare(aux->data, data, bytes);
        if (resultado == 0) { 
           break;
        }
        aux = aux->next;
    }
    if (aux != NULL) {
        return aux->data;
    }
    return NULL;
}

void *
list_index(struct list *list, int index)
{
    if (index < 0 || index >= list->tamanho) {
        return NULL;
    }
    int i = 1;
    struct node *aux = list->head;
    while (aux != NULL && i < index) {
        aux = aux->next;
    }
    if (aux == NULL) {
        return NULL;
    }
    return aux->data;
}

void 
list_print(struct list *list)
{
    struct node *aux = list->head;
    while (aux != NULL) {
        list->print(aux->data);
        aux = aux->next;
    }
}

void 
list_quicksort(struct list *list, size_t bytes, int (*compare)(void *data, void *data2, size_t bytes))
{
    // Determinar função de comparação
    int (*__compare)(void *data, void *data2, size_t bytes);
    __compare = (int (*)())set_fn(2, compare, list->compare);
    __quicksort_recursive(list->head, list->tail, bytes, __compare);
}

void __node_swap(struct node *node1, struct node *node2)
{
    void *aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

struct node *
__list_partition(struct node *head, struct node *tail, size_t bytes, int (*compare)(void *data1, void *data2, size_t bytes))
{
    struct node *next_pivot = head; //< Pivot que será utilizado na próxmia chamada a esta função
    struct node *cursor_i = head;
    struct node *cursor_j = head;
    void *pivot_data = tail->data; //< Informação que será utilizada como pivot
    while (cursor_j != tail) {
        if (compare(cursor_j->data, pivot_data, bytes) < 0) { // Se a datarmação do cursor j for menor que o pivot,
                                                              // sob o critério da função `compare`, update
                                                              // `next_pivot`, trocar j com i, e incrementar i
            next_pivot = cursor_i;
            __node_swap(cursor_i, cursor_j);
            cursor_i = cursor_i->next;
        }
        cursor_j = cursor_j->next;
    }
    __node_swap(cursor_i, tail);
    return next_pivot;
}

void
__quicksort_recursive(struct node *head, struct node *tail, size_t bytes, int (*compare)(void *data, void *data2, size_t bytes))
{
    // Condição de saída
    if (head == tail || head == NULL || tail == NULL) {
        return;
    }
    // Realizar partição e receber próximo pivot
    struct node *pivot = __list_partition(head, tail, bytes, compare);
    if (pivot == NULL) {
        return;
    }
    // Se pivot for diferente do início, sort do início até o pivot
    if (head != pivot) {
        __quicksort_recursive(head, pivot, bytes, compare);
    }
    // Se o nó próximo ao pivot for diferente do tail, sort daquele até o tail
    // Se o nó próximo ao pivot for diferente do tail, sort daquele até o tail
    if (pivot->next != NULL && pivot->next != tail) {
        __quicksort_recursive(pivot->next, tail, bytes, compare);
    }
}

