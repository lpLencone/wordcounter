#include "reader.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void __update_word(struct dictionary *dictionary, char word[]);
int __get_word(FILE *file, char word[], int insensitive, int *cursor);

void count_words(FILE *file, struct dictionary *dictionary, int insensitive)
{
    char word[32] = {0};
    void *value;
    int cursor;
    int tail;
    do {
        tail = __get_word(file, word, insensitive, &cursor);
        if (strlen(word) > 0) {
            word[cursor] = '\0';
            __update_word(dictionary, word);
        }

        word[0] = '\0';
    }
    while (!tail);
}

int __get_word(FILE *file, char word[], int insensitive, int *cursor)
{
    int word_cursor = 0;
    char c;
    while (isalpha(c = fgetc(file))) {  
        if (insensitive) {
            c = tolower(c);
        }
        word[word_cursor] = c;
        word_cursor++;
    }
    *cursor = word_cursor;
    if (c == EOF) {
        return 1;
    }
    return 0;
}

void __update_word(struct dictionary *dictionary, char word[])
{
    const int INITIAL_VALUE = 1;
    void *value;
    if ((value = dictionary_query(dictionary, word, strlen(word) + 1)) != NULL) {
        (*(int *)value)++;
        dictionary_alter(dictionary, word, strlen(word) + 1, value, sizeof(int));
    }
    else {
        dictionary_add(dictionary, word, strlen(word) + 1, (void *)&INITIAL_VALUE, sizeof(int));
    }
}

