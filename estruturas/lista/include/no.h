//!< INICIO NO_H

#ifndef NO_H
#define NO_H

#include "../../versao.h"

#include <stddef.h>

/** 
 * O nó armazenará uma informação genéria, um ponteiro para o próximo nó em uma lista,
 * e uma função (OPCIONAL) que desaloca a memória CONTIDA na informação, MAS NÃO INCLUINDO-NA.
 * 
 * A função de destruição do nó lidará com o desalocamento da memória dedicada a si e a informação armazenada.
 */
struct no
{
    #ifdef VERSAO_DUPLA
        struct no *ante;
    #endif
    struct no *prox;
    void *info;
    void (*free_info)(void *info);
};

/* Recebe opcionalmente uma função para liberar memória alocada para membros da estrutura presente em info
    caso seja necessário liberar blocos de memória aos quais o nó não possui acesso */
struct no *no_iniciar(void *info, size_t bytes, void (*free_info)(void *info));
void no_destruir(struct no *no);

#endif /* NO_H */

//!< FINAL NO_H