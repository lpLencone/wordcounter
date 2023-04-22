//!< INICIO MAIN_C

#include "leitor/leitor.h"
#include "estruturas/lista/include/fila.h"

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __print_palavra(void *palavra);
void __print_contagem(void *contagem);
void __zerar_palavra(char *palavra, int tamanho);

// Argumentos do programa
struct {
    int ajuda;
    int ordenar;
    int insensitivo;
    int imprimir;

    FILE *arquivo;

    struct {
        int flag;
        FILE *arquivo;
    } salvar;

    struct {
        int flag;
        struct fila palavras;
    } pesquisar;

    FILE *output;
}
argumentos;

void inicializar_argumentos();
// Ler argumentos do terminal
void argumentos_terminal(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    inicializar_argumentos();

    argumentos_terminal(argc, argv);

    if (argumentos.ajuda) {
        printf("Modo de uso: %s [-a arquivo] [-hi] [-o modo] [-p palavras] [-s arquivo]\n", argv[0]);
        printf("  -a, --arquivo         fornecer caminho do arquivo para ser lido (padrao: stdin)\n\n");
        printf("  -h, --ajuda           mostrar informações sobre uso do programa\n\n");
        printf("  -i, --insensitivo     fazer leitura insensitiva das palavras\n\n");
        printf("  -o, --ordenar         ordenar as palavras do arquivo (p para palavra ou c para contagem)\n\n");
        printf("  -p, --pesquisar       pesquisar uma ou mais palavras no arquivo (separadas,por,virgula)\n\n");
        printf("  -s, --salvar          salvar o resultado em um arquivo\n\n");
        exit(EXIT_FAILURE);
    }

    struct dicionario dicionario = dicionario_iniciar(__print_palavra, __print_contagem);

    if (argumentos.arquivo == stdin) {
        printf("Lendo diretamente do terminal...\nEntre Ctrl+D para enviar texto fornecido.\n\n");
    }
    contar_palavras(argumentos.arquivo, &dicionario, argumentos.insensitivo); // Popular dicionário com as palavras no arquivo
    fclose(argumentos.arquivo); 

    if (argumentos.ordenar != -1) {
        dicionario_quicksort(&dicionario, argumentos.ordenar);
    }

    if (argumentos.salvar.flag) {
        // Redireciona output para o arquivo de salvamento
        argumentos.output = argumentos.salvar.arquivo;
    }

    if (argumentos.imprimir) {
        // Imprime todo o resultado da leitura caso o usuário não especifique palavras para pesquisar
        printf("\n");
        dicionario_print(&dicionario);
    }

    if (argumentos.pesquisar.flag) {
        void *palavra_pesquisa;
        // Enquanto houver palavras para pesquisar
        while ((palavra_pesquisa = fila_espiar(&argumentos.pesquisar.palavras)) != NULL) {
            // Obter contagem da palavra
            void *resultado = dicionario_pesquisar(&dicionario, palavra_pesquisa, strlen((char *)palavra_pesquisa) + 1);
            __print_palavra(palavra_pesquisa);
            // Se a palavra existir, apresente-a com a sua contagem
            if (resultado != NULL) {
                __print_contagem(resultado);
            }
            // Senao...
            else {
                fprintf(argumentos.output, "nao existe no arquivo\n");
            }
            fila_retirar(&argumentos.pesquisar.palavras);
        }
    }

    fila_destruir(&argumentos.pesquisar.palavras);
    dicionario_destruir(&dicionario);
    if (argumentos.salvar.flag) {
        fclose(argumentos.salvar.arquivo);
    }

    return 0;
}

void __obter_palavras_pesquisa(char *optarg);

void argumentos_terminal(int argc, char *argv[])
{
    struct option opcoes[] = {
        {"ajuda",       no_argument,       NULL, 'h'},
        {"insensitivo", no_argument,       NULL, 'i'},
        {"arquivo",     required_argument, NULL, 'a'},
        {"ordenar",     required_argument, NULL, 'o'},
        {"salvar",      required_argument, NULL, 's'},
        {"pesquisar",   required_argument, NULL, 'p'},
        {NULL, 0, NULL, '\0'},
    };

    char opt;
    int opcoes_indice = 0;
    while ((opt = getopt_long(argc, argv, "ha:o:s:p:i", opcoes, &opcoes_indice)) != -1) {
        switch (opt)
        {
        case 'a':
            argumentos.arquivo = fopen(optarg, "r");
            if (argumentos.arquivo == NULL) {
                fprintf(stderr, "%s::%d: fopen: %s\n", __FILE__, __LINE__ - 2, strerror(errno));
                exit(errno);
            }
            break;

        case 's':
            argumentos.salvar.arquivo = fopen(optarg, "w");
            if (argumentos.salvar.arquivo == NULL) {
                fprintf(stderr, "%s::%d: fopen: %s\n", __FILE__, __LINE__ - 2, strerror(errno));
                exit(errno);
            }
            argumentos.salvar.flag = 1;
            break;

        case 'h':
            argumentos.ajuda = 1;
            break;

        case 'o':
            switch (tolower(optarg[0])) {
            case 'p':
                argumentos.ordenar = CHAVE;
                break;
            case 'c':
                argumentos.ordenar = VALOR;
                break;
            default:
                printf("Opcao de ordenacao nao reconhecida: %s\n\n", optarg);
                break;
            }
            break;

        case 'i':
            argumentos.insensitivo = 1;
            break;
            
        case 'p':
            __obter_palavras_pesquisa(optarg);
            argumentos.pesquisar.flag = 1;
            argumentos.imprimir = 0;
            break;

        default:
            break;
        }
    }
}

void inicializar_argumentos()
{
    argumentos.ajuda = 0;
    argumentos.ordenar = -1;
    argumentos.imprimir = 1;
    argumentos.insensitivo = 0;

    argumentos.arquivo = stdin;

    argumentos.salvar.flag = 0;
    argumentos.salvar.arquivo = NULL;

    argumentos.pesquisar.flag = 0;
    argumentos.pesquisar.palavras = fila_iniciar(NULL);

    argumentos.output = stdout;
}

void __obter_palavras_pesquisa(char *optarg)
{
    int cursor = 0;
    char palavra[32] = {0};
    int i = 0;
    do {
        if (isalpha(optarg[i])) {
            palavra[cursor] = optarg[i];
            cursor++;
        }
        else if (cursor != 0) {
            // Terminar palavra
            palavra[cursor] = '\0';
            // Adicioná-la à fila
            fila_enfileirar(&argumentos.pesquisar.palavras, (void *)palavra, strlen(palavra) + 1);
            // Zerar palavra até o cursor
            __zerar_palavra(palavra, cursor);
            cursor = 0;
        }
    }
    while (optarg[i++] != '\0');
}

void __zerar_palavra(char *palavra, int tamanho)
{
    for (int i = 0; i < tamanho; i++) {
        palavra[i] = '\0';
    }
}

void __print_palavra(void *palavra)
{
    fprintf(argumentos.output, "%-12s ", (char *)palavra);
}

void __print_contagem(void *contagem)
{
    fprintf(argumentos.output, "%d\n", *(int *)contagem);
}

//!< FINAL MAIN_C
