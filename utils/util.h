#ifndef UTIL_H
#define UTIL_H

typedef void * (*funcao_resultado)();

/// @brief O objetivo dessa função é receber uma sequência de funções das quais não se sabe se são nulas ou não. Será retornado da sequência a primeira função não nula, então elas devem ser passadas em ordem de prioriadade.
/// @param n_funcoes A quantidade de funções subsequentes
/// @return Retorna a primeira função não nula da sequência. 
funcao_resultado definir_funcao(int n_funcoes, ...);

#endif /* UTIL_H */