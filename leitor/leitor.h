//!< INICIO LEITOR_H

#ifndef LEITOR_H
#define LEITOR_H

#include "../estruturas/estruturas.h"

#include <stdio.h>

// Lê as palavras de um arquivo, adicionando-as ao dicionário, e incrementando sua ocorrência
// caso apareçam repetidas vezes.
void contar_palavras(FILE *arquivo, struct dicionario *dicionario, int insensitivo);

#endif /* LEITOR_H */

//!< FINAL LEITOR_H