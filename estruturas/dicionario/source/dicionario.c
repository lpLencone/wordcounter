//!< INICIO DICIONARIO_C

#include "../include/dicionario.h"

#include <stdio.h>
#include <string.h>

///
/// Protótipos de funções privadas
///

// Libera memória associada a cada registro e sua chave e valor
void __destruir_registro(void *registro);

// Compara registros para ordenação por chave
int __comparar_registro_chave(void *registro, void *chave, size_t bytes);

// Compara registros para ordenação por valor
int __comparar_registro_valor(void *info1, void *info2, size_t bytes);

// Imprime o conteúdo do registro
void __print_registro(void *info);
struct registro *__encontrar_registro(struct dicionario *dicionario, void *chave, size_t bytes);

// Função que define qual função de comparação será utilizada para encontrar um registro
typedef int (*funcao_comparar)(void *info, void *info2, size_t bytes);
funcao_comparar __definir_comparar(enum pesquisa pesquisa);

struct dicionario
dicionario_iniciar(void (*chave_print)(void *chave), void (*valor_print)(void *valor))
{
    struct dicionario dicionario;
    dicionario.registros = lista_iniciar(__destruir_registro, __comparar_registro_chave, __print_registro);
    dicionario.chave_print = chave_print;
    dicionario.valor_print = valor_print;
    return dicionario;
}

void
dicionario_destruir(struct dicionario *dicionario)
{
    lista_destruir(&dicionario->registros);
}

void
dicionario_adicionar(struct dicionario *dicionario, void *chave, size_t chave_bytes, void *valor, size_t valor_bytes)
{
    struct registro *pesquisa = __encontrar_registro(dicionario, chave, chave_bytes);
    if (pesquisa != NULL) {
        printf("Registro já existe.\n");
        return;
    }
    struct registro registro = registro_iniciar(chave, chave_bytes, dicionario->chave_print, valor, valor_bytes, dicionario->valor_print);
    lista_adicionar(&dicionario->registros, &registro, sizeof(struct registro));
}

void *
dicionario_pesquisar(struct dicionario *dicionario, void *chave, size_t bytes)
{
    struct registro *registro = __encontrar_registro(dicionario, chave, bytes);
    if (registro != NULL) {
        return registro->valor;
    }
    return NULL;
}

void
dicionario_editar(struct dicionario *dicionario, void *chave, size_t chave_bytes, void *valor, size_t valor_bytes)
{
    struct registro *registro = __encontrar_registro(dicionario, chave, chave_bytes);
    if (registro == NULL) {
        printf("Registro não existe.\n");
        return;
    }
    memcpy(registro->valor, valor, valor_bytes);
}

void
dicionario_print(struct dicionario *dicionario)
{
    lista_print(&dicionario->registros);
}

void
dicionario_quicksort(struct dicionario *dicionario, enum pesquisa pesquisa)
{
    int (*comparar)(void *info, void *info2, size_t bytes);
    comparar = __definir_comparar(pesquisa);
    lista_quicksort(&dicionario->registros, 0, comparar);
}

// Funções privadas
void
__destruir_registro(void *registro)
{
    registro_destruir((struct registro *)registro);
}

int
__comparar_registro_chave(void *info1, void *info2, size_t bytes)
{
    struct registro *registro1 = (struct registro *)info1;
    struct registro *registro2 = (struct registro *)info2;
    void *chave1 = registro1->chave;
    void *chave2 = registro2->chave;
    // É utilizado a maior quantidade de bytes para comparação pois pode acontecer do elemento de menor número de bytes estar 'incluso' no elemento de maior número de bytes.
    bytes = (registro1->chave_bytes > registro2->chave_bytes) ? 
             registro1->chave_bytes : registro2->chave_bytes;
    return memcmp(chave1, chave2, bytes);
}

int
__comparar_registro_valor(void *info1, void *info2, size_t bytes)
{
    struct registro *registro1 = (struct registro *)info1;
    struct registro *registro2 = (struct registro *)info2;
    void *valor1 = registro1->valor;
    void *valor2 = registro2->valor;
    // É utilizado a maior quantidade de bytes para comparação pois pode acontecer do elemento de menor número de bytes estar 'incluso' no elemento de maior número de bytes.
    bytes = (registro1->valor_bytes > registro2->valor_bytes) ? 
             registro1->valor_bytes : registro2->valor_bytes;
    return memcmp(valor1, valor2, bytes);
}

void 
__print_registro(void *info)
{
    struct registro *registro = (struct registro *)info;
    void *chave = registro->chave;
    void *valor = registro->valor;
    registro->chave_print(chave);
    registro->valor_print(valor);
}

// Retorna uma função de comparação com base em `pesquisa`
funcao_comparar 
__definir_comparar(enum pesquisa pesquisa)
{
    int (*comparar)(void *info, void *info2, size_t bytes);
    if (pesquisa == CHAVE) {
        comparar = __comparar_registro_chave;
    }
    else if (pesquisa == VALOR) {
        comparar = __comparar_registro_valor;
    }
    else {
        return NULL;
    }
    return comparar;
}

/* Retorna registro no dicionario com a chave fornecida, se houver
Senao, retorna NULL */
struct registro *
__encontrar_registro(struct dicionario *dicionario, void *chave, size_t bytes)
{
    int pesquisa_valor = 0;
    struct registro pesquisa = registro_iniciar(chave, bytes, NULL, &pesquisa_valor, sizeof(int), NULL);
    struct registro *registro = (struct registro *)lista_pesquisar(&dicionario->registros, &pesquisa, bytes, NULL);
    registro_destruir(&pesquisa);
    return registro;
}

//!< FINAL DICIONARIO_C
