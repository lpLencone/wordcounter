#include "reader/reader.h"
#include "dstructs/list/include/queue.h"

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __print_word(void *word);
void __print_count(void *count);
void __reset_word(char *word, int n);

struct {
    int help;
    int sort;
    int insensitive;
    int print;

    FILE *file;

    struct {
        int flag;
        FILE *file;
    } save;

    struct {
        int flag;
        struct queue words;
    } query;

    FILE *output;
}
args;

void init_args();
void args_terminal(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    init_args();

    args_terminal(argc, argv);

    if (args.help) {
        printf("Modo de uso: %s [-a file] [-hi] [-o modo] [-p words] [-s file]\n", argv[0]);
        printf("  -f, --file			file path (default: stdin)\n");
        printf("  -h, --help			this menu\n");
        printf("  -i, --insensitive		insensitive reading of the words\n");
        printf("  -s, --sort			-sw sort by word, -sf sort by frequency\n");
        printf("  -q, --query			query one or more words (separated,by,comma)\n");
        printf("  -w, --write			write result to a file\n");
        exit(EXIT_FAILURE);
    }

    struct dictionary dictionary = dictionary_init(__print_word, __print_count);

    if (args.file == stdin) {
        printf("Reading from the terminal...\nEnter Ctrl+D to stop\n\n");
    }
    count_words(args.file, &dictionary, args.insensitive); 
    fclose(args.file); 

    if (args.sort != -1) {
        dictionary_quicksort(&dictionary, args.sort);
    }

    if (args.save.flag) {
        args.output = args.save.file;
    }

    if (args.print) {
        printf("\n");
        dictionary_print(&dictionary);
    }

    if (args.query.flag) {
        void *word_query;
        while ((word_query = queue_peek(&args.query.words)) != NULL) {
            void *result = dictionary_query(&dictionary, word_query, strlen((char *)word_query) + 1);
            __print_word(word_query);
            if (result != NULL) {
                __print_count(result);
            }
            else {
                fprintf(args.output, "not found in the file\n");
            }
            queue_pop(&args.query.words);
        }
    }

    queue_destroy(&args.query.words);
    dictionary_destroy(&dictionary);
    if (args.save.flag) {
        fclose(args.save.file);
    }

    return 0;
}

void __get_words_query(char *optarg);

void args_terminal(int argc, char *argv[])
{
    struct option options[] = {
        {"help",        no_argument,        NULL,   'h' },
        {"insensitive", no_argument,        NULL,   'i' },
        {"file",        required_argument,  NULL,   'f' },
        {"sort",        required_argument,  NULL,   's' },
        {"write",       required_argument,  NULL,   'w' },
        {"query",       required_argument,  NULL,   'q' },
        {NULL,          0,                  NULL,   '\0'},
    };

    char opt;
    int options_index = 0;
    while ((opt = getopt_long(argc, argv, "hf:s:w:q:i", options, &options_index)) != -1) {
        switch (opt)
        {
        case 'f':
            args.file = fopen(optarg, "r");
            if (args.file == NULL) {
                fprintf(stderr, "%s::%d: fopen: %s\n", __FILE__, __LINE__ - 2, strerror(errno));
                exit(errno);
            }
            break;

        case 'w':
            args.save.file = fopen(optarg, "w");
            if (args.save.file == NULL) {
                fprintf(stderr, "%s::%d: fopen: %s\n", __FILE__, __LINE__ - 2, strerror(errno));
                exit(errno);
            }
            args.save.flag = 1;
            break;

        case 'h':
            args.help = 1;
            break;

        case 's':
            switch (tolower(optarg[0])) {
            case 'w':
                args.sort = KEY;
                break;
            case 'f':
                args.sort = VALUE;
                break;
            default:
                printf("Unknown sort mode: %s; use w (word) or f (frequency) instead\n\n", optarg);
                break;
            }
            break;

        case 'i':
            args.insensitive = 1;
            break;
            
        case 'q':
            __get_words_query(optarg);
            args.query.flag = 1;
            args.print = 0;
            break;

        default:
            break;
        }
    }
}

void init_args()
{
    args.help = 0;
    args.sort = -1;
    args.print = 1;
    args.insensitive = 0;

    args.file = stdin;

    args.save.flag = 0;
    args.save.file = NULL;

    args.query.flag = 0;
    args.query.words = queue_init(NULL);

    args.output = stdout;
}

void __get_words_query(char *optarg)
{
    int cursor = 0;
    char word[32] = {0};
    int i = 0;
    do {
        if (isalpha(optarg[i])) {
            word[cursor] = optarg[i];
            cursor++;
        }
        else if (cursor != 0) {
            word[cursor] = '\0';
            queue_push(&args.query.words, (void *)word, strlen(word) + 1);
            __reset_word(word, cursor);
            cursor = 0;
        }
    }
    while (optarg[i++] != '\0');
}

void __reset_word(char *word, int n)
{
    for (int i = 0; i < n; i++) {
        word[i] = '\0';
    }
}

void __print_word(void *word)
{
    fprintf(args.output, "%-14s ", (char *)word);
}

void __print_count(void *count)
{
    fprintf(args.output, "%d\n", *(int *)count);
}

