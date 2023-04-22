// Define qual a versão da lista (simples ou dupla), devera ser utilizada na compilacao
// Ao executar 'make simples' sera utilizada a versao simples, em que o no possui apenas um pointeiro
// Ao executar 'make dupla', o no tera tanto o ponteiro para o proximo no na lista, quanto para o anterior
/**
 * Na prática isso não faz diferença alguma; eu precisava criar uma versão do programa utilizando lista simples
 * e outra versão utilizando lista dupla, então criei esse artifício para não precisar copiar e colar o código,
 * mas acabou que eu nem utilizei efetivamente o ponteiro para o nó anterior, mesmo quando compilada a versão dupla.
 */
#define VERSAO_SIMPLES
