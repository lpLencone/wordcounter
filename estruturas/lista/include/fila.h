//!< INICIO FILA_H

// Filas foram utilizadas nesse programa para auxiliar a função de contar palavras em um arquivo

#ifndef FILA_H
#define FILA_H

#include "no.h"

struct fila {
    struct no *primeiro;
    struct no *ultimo;
    void (*free_info)(void *info);
};

struct fila fila_iniciar(void (*free_info)(void *info));

void fila_destruir(struct fila *fila);

void fila_enfileirar(struct fila *fila, void *info, size_t bytes);

// Retorna a info presente no nó em primeiro na fila
void *fila_espiar(struct fila *fila);

// Retira o nó em primeiro na fila
void fila_retirar(struct fila *fila);

#endif /* FILA_H */

//!< FINAL FILA_H