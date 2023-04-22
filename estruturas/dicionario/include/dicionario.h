//!< INICIO DICIONARIO_H

#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "registro.h"
#include "../../lista/include/lista.h"

#include <stddef.h>

enum pesquisa 
{
    CHAVE,
    VALOR
};

struct dicionario
{
    struct lista registros;
    void (*chave_print)(void *chave);
    void (*valor_print)(void *valor);
};

struct dicionario dicionario_iniciar(void (*chave_print)(void *chave), void (*valor_print)(void *valor));

void dicionario_destruir(struct dicionario *dicionario);

void dicionario_adicionar(struct dicionario *dicionario, void *chave, size_t chave_bytes, void *valor, size_t valor_bytes);

void dicionario_print(struct dicionario *dicionario);

void dicionario_quicksort(struct dicionario *dicionario, enum pesquisa pesquisa);

// Devolve valor que corresponde com chave providenciada como (void *)
void * dicionario_pesquisar(struct dicionario *dicionario, void *chave, size_t bytes);

void dicionario_editar(struct dicionario *dicionario, void *chave, size_t chave_bytes, void *valor, size_t valor_bytes);

#endif /* DICIONARIO_H */

//!< FINAL DICIONARIO_H
