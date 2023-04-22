//!< INICIO LEITOR_C

#include "leitor.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void __atualizar_palavra(struct dicionario *dicionario, char palavra[]);
int __obter_palavra(FILE *arquivo, char palavra[], int insensitivo, int *cursor);

void contar_palavras(FILE *arquivo, struct dicionario *dicionario, int insensitivo)
{
    char palavra[32] = {0};
    void *valor;
    int cursor;
    int final;
    do {
        final = __obter_palavra(arquivo, palavra, insensitivo, &cursor);
        if (strlen(palavra) > 0) {
            // Define final da palavra
            palavra[cursor] = '\0';

            __atualizar_palavra(dicionario, palavra);
        }

        // Reseta palavra e o cursor
        palavra[0] = '\0';
    } // Enquanto não chegar ao final do arquivo
    while (!final);
}

int __obter_palavra(FILE *arquivo, char palavra[], int insensitivo, int *cursor)
{
    int palavra_cursor = 0;
    char c;
    // Coloque caracteres alfabeticos em `palavra`
    while (isalpha(c = fgetc(arquivo))) {  
        if (insensitivo) {
            c = tolower(c);
        }
        palavra[palavra_cursor] = c;
        palavra_cursor++;
    }
    *cursor = palavra_cursor;
    if (c == EOF) {
        return 1;
    }
    return 0;
}

void __atualizar_palavra(struct dicionario *dicionario, char palavra[])
{
    const int VALOR_INICIAL = 1;
    void *valor;
    // Verifica se palavra ja se encontra no dicionario
    if ((valor = dicionario_pesquisar(dicionario, palavra, strlen(palavra) + 1)) != NULL) {
        // Incrementa ocorrencia
        (*(int *)valor)++;
        // Altera o valor da ocorrencia no dicionario
        dicionario_editar(dicionario, palavra, strlen(palavra) + 1, valor, sizeof(int));
    }
    // Se nao estiver, adiciona-a
    else {
        dicionario_adicionar(dicionario, palavra, strlen(palavra) + 1, (void *)&VALOR_INICIAL, sizeof(int));
    }
}

//!< FINAL LEITOR_C