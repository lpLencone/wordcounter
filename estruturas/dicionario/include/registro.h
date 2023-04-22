//!< INICIO REGISTRO_H

#ifndef REGISTRO_H
#define REGISTRO_H

#include <stddef.h>

/**
 * O registro armazenará uma chave, um valor, e funções que possibilitem
 * suas informações serem apresentadas.
 * 
 * Visto que a chave e o valor são (void *), ou seja, dados genéricos que podem 
 * representar qualquer informação (int, char[], qualquer outra struct, etc)
 * o criador do registro deverá providenciar as funções que aprensentarão o conteúdo da chave e do valor.
*/
struct registro
{
    void *chave;
    size_t chave_bytes;
    void *valor;
    size_t valor_bytes;
    void (*chave_print)(void *chave);
    void (*valor_print)(void *valor);
};

struct registro registro_iniciar(void *chave, size_t chave_bytes, void (*chave_print)(void *chave), void *valor, size_t valor_bytes, void (*valor_print)(void *valor));

void registro_destruir(struct registro *registro);

#endif /* REGISTRO_H */

//!< FINAL REGISTRO_H