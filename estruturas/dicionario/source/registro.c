//!< INICIO REGISTRO_C

#include "../include/registro.h"

#include <stdlib.h>
#include <string.h>

struct registro 
registro_iniciar(void *chave, size_t chave_bytes, void (*chave_print)(void *chave), void *valor, size_t valor_bytes, void (*valor_print)(void *valor))
{
    struct registro registro;
    registro.chave = malloc(chave_bytes);
    registro.valor = malloc(valor_bytes);
    memcpy(registro.chave, chave, chave_bytes);
    memcpy(registro.valor, valor, valor_bytes);
    registro.chave_bytes = chave_bytes;
    registro.valor_bytes = valor_bytes;
    registro.chave_print = chave_print;
    registro.valor_print = valor_print;
    return registro;
}

void 
registro_destruir(struct registro *registro)
{
    free(registro->chave);
    free(registro->valor);
}

//!< FINAL REGISTRO_C
