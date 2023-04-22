//!< INICIO FILA_C

#include "../include/fila.h"

struct fila
fila_iniciar(void (*free_info)(void *info))
{
    struct fila fila;
    fila.primeiro = NULL;
    fila.ultimo = NULL;
    fila.free_info = free_info;
    return fila;
}

void fila_destruir(struct fila *fila)
{
    while (fila->primeiro != NULL) {
        fila_retirar(fila);
    }
}

void fila_enfileirar(struct fila *fila, void *info, size_t bytes)
{
    struct no *no = no_iniciar(info, bytes, fila->free_info);
    if (fila->ultimo == NULL) {
        fila->primeiro = fila->ultimo = no;
    }
    else {
        fila->ultimo->prox = no;
        fila->ultimo = no;
    }
}

void *fila_espiar(struct fila *fila)
{
    if (fila->primeiro == NULL) {
        return NULL;
    }
    return fila->primeiro->info;
}

void fila_retirar(struct fila *fila)
{
    if (fila->primeiro != NULL) {
        struct no *aux = fila->primeiro->prox;
        no_destruir(fila->primeiro);
        fila->primeiro = aux;
    }
}

//!< FINAL FILA_C
