//!< INICIO LISTA_C

#include "../include/lista.h"
#include "../../../utils/util.h"

#include <stdio.h>

void 
__quicksort_recursivo(struct no *inicio, struct no *final, size_t bytes, int (*comparar)(void *info, void *info2, size_t bytes));

struct lista 
lista_iniciar(void (*free_info)(void *info), int (*comparar)(void *info, void *info2, size_t bytes), void (*print)(void *info))
{
    struct lista lista;
    lista.inicio = NULL;
    lista.final = NULL;
    lista.tamanho = 0;
    lista.free_info = free_info;
    lista.comparar = comparar;
    lista.print = print;
    return lista;
}

void 
lista_destruir(struct lista *lista)
{
    if (lista->inicio == NULL) {
        return;
    }
    struct no *aux = lista->inicio;
    struct no *aux2;
    while (aux != NULL) {
        aux2 = aux->prox;
        no_destruir(aux);
        aux = aux2;
    }
}

void 
lista_adicionar(struct lista *lista, void *info, size_t bytes)
{
    struct no *no = no_iniciar(info, bytes, lista->free_info);
    if (lista->tamanho == 0) {
        lista->inicio = no;
    }
    else {
        #ifdef VERSAO_DUPLA
            no->ante = lista->final;
        #endif
        lista->final->prox = no;
    }
    lista->final = no;
    lista->tamanho++;
}

void *
lista_pesquisar(struct lista *lista, void *info, size_t bytes, int (*comparar)(void *info, void *info2, size_t bytes))
{
    // Determinar função de comparação
    int (*__comparar)(void *info, void *info2, size_t bytes);
    __comparar = (int (*)())definir_funcao(2, comparar, lista->comparar);

    struct no *aux = lista->inicio;
    while (aux != NULL) {
        int resultado = __comparar(aux->info, info, bytes);
        if (resultado == 0) { 
           break;
        }
        aux = aux->prox;
    }
    if (aux != NULL) {
        return aux->info;
    }
    return NULL;
}

void *
lista_posicao(struct lista *lista, int posicao)
{
    if (posicao < 0 || posicao >= lista->tamanho) {
        return NULL;
    }
    int i = 1;
    struct no *aux = lista->inicio;
    while (aux != NULL && i < posicao) {
        aux = aux->prox;
    }
    if (aux == NULL) {
        return NULL;
    }
    return aux->info;
}

void 
lista_print(struct lista *lista)
{
    struct no *aux = lista->inicio;
    while (aux != NULL) {
        lista->print(aux->info);
        aux = aux->prox;
    }
}

void 
lista_quicksort(struct lista *lista, size_t bytes, int (*comparar)(void *info, void *info2, size_t bytes))
{
    // Determinar função de comparação
    int (*__comparar)(void *info, void *info2, size_t bytes);
    __comparar = (int (*)())definir_funcao(2, comparar, lista->comparar);

    __quicksort_recursivo(lista->inicio, lista->final, bytes, __comparar);
}

// Funções privadas
void __no_swap(struct no *no1, struct no *no2)
{
    void *aux = no1->info;
    no1->info = no2->info;
    no2->info = aux;
}

struct no *
__lista_partition(struct no *inicio, struct no *final, size_t bytes, int (*comparar)(void *info1, void *info2, size_t bytes))
{
    struct no *proximo_pivot = inicio; //< Pivot que será utilizado na próxmia chamada a esta função
    struct no *cursor_i = inicio;
    struct no *cursor_j = inicio;
    void *pivot_info = final->info; //< Informação que será utilizada como pivot
    while (cursor_j != final) {
        if (comparar(cursor_j->info, pivot_info, bytes) < 0) { // Se a informação do cursor j for menor que o pivot,
                                                               // sob o critério da função `comparar`, atualizar
                                                               // `proximo_pivot`, trocar j com i, e incrementar i
            proximo_pivot = cursor_i;
            __no_swap(cursor_i, cursor_j);
            cursor_i = cursor_i->prox;
        }
        cursor_j = cursor_j->prox;
    }
    __no_swap(cursor_i, final);
    return proximo_pivot;
}

void
__quicksort_recursivo(struct no *inicio, struct no *final, size_t bytes, int (*comparar)(void *info, void *info2, size_t bytes))
{
    // Condição de saída
    if (inicio == final || inicio == NULL || final == NULL) {
        return;
    }
    // Realizar partição e receber próximo pivot
    struct no *pivot = __lista_partition(inicio, final, bytes, comparar);
    if (pivot == NULL) {
        return;
    }
    // Se pivot for diferente do início, ordenar do início até o pivot
    if (inicio != pivot) {
        __quicksort_recursivo(inicio, pivot, bytes, comparar);
    }
    // Se o nó próximo ao pivot for diferente do final, ordenar daquele até o final
    if (pivot->prox != NULL && pivot->prox != final) {
        __quicksort_recursivo(pivot->prox, final, bytes, comparar);
    }
}

//!< FINAL LISTA_C
