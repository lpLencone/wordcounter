#include "util.h"

#include <stdlib.h>
#include <stdarg.h>

/**
 * Retorna de uma lista variável de ponteiros de funções
 * o primeiro ponteiro não nulo.
 * 
 * Motivo: Em algumas circunstâncias no programa há casos em que
 * é conveniente dar prioridade para ponteiros à funções recebidas
 * através de um parâmetro. No entanto, no caso delas não serem fornecidas
 * será utilizada uma função por padrão. Nesse caso, há uma situação
 * em que uma função tem prioridade sobre a outra, e para evitar que em 
 * cada uma dessas instâncias fosse necessária a verificação de se
 * a função prioritária foi fornecida ou não, a função abaixo foi definida
 * para lidar com esse caso particular.
*/
funcao_resultado definir_funcao(int n_funcoes, ...)
{
    va_list v;
    va_start(v, n_funcoes);
    void *(*fn)() = NULL;
    for (int i = 0; i < n_funcoes; i++) {
        fn = va_arg(v, void *(*)());
        if (fn != NULL) {
            break;
        }
    }
    va_end(v);
    return fn;
}