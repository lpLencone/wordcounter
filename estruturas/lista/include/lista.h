//!< INICIO LISTA_H

#ifndef LISTA_H
#define LISTA_H

#include "no.h"

struct lista
{
    struct no *inicio;
    struct no *final;
    int tamanho;
    void (*free_info)(void *info);
    int (*comparar)(void *info, void *info2, size_t bytes);
    void (*print)(void *info);
};

/* Parametro 'free_info' OPCIONAL
    Será chamado individualmente na destruição de cada nó, em caso de seu membro 'info' precisar ter sua memória desalocada personalizadamente. 
    
    Parametro 'comparar' OPCIONAL
    Será a função default utilizada para fazer comparações necessárias para achar um determinado nó com base na info fornecida para pesquisá-lo. Se uma outra função de comparação for passada para a função de pesquisar ou de ordenar, esta terá prioridade de uso. 
    
    Parâmetro 'print' OPCIONAL
    Será utilizado caso seja desejado que o conteúdo da lista seja apresentado. Como os nós guardam informação genérica, é necessário que uma função personalizada para apresentação seja fornecida conforme o conteúdo dos nós que participarão da lista. 
    
    Todas essas funções assumem que o conteúdo dos nós presentes na lista sejam homogêneos, ou seja, são de um mesmo tipo. */
struct lista lista_iniciar(
    void (*free_info)(void *info), 
    int (*comparar)(void *info, void *info2, size_t bytes), 
    void (*print)(void *info)
);

void lista_destruir(struct lista *lista);

// Adiciona no com `info` ao fim da lista
void lista_adicionar(struct lista *lista, void *info, size_t bytes);

void *lista_pesquisar(
    struct lista *lista, 
    void *info, 
    size_t bytes,
    int (*comparar)(void *info, void *info2, size_t bytes)
);

void *lista_posicao(struct lista *lista, int posicao);

void lista_print(struct lista *lista);

void lista_quicksort(
    struct lista *lista, 
    size_t bytes, 
    int (*comparar)(void *info, void *info2, size_t bytes)
);

#endif /* LISTA_H */

//!< FINAL LISTA_H