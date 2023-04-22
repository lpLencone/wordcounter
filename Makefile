#!< INICIO MAKEFILE

.SILENT: simples dupla versao
.PHONY:  simples dupla versao

CC = gcc
SRC = $(shell find -name '*.c')
BIN = main
OPT = -O3 -march=native

simples: versao
	echo "#define VERSAO_SIMPLES" >> estruturas/versao.h
	${CC} ${SRC} -o ${BIN} ${OPT}
	echo "Versao simples pronta"
	
dupla: versao
	echo "#define VERSAO_DUPLA" >> estruturas/versao.h
	${CC} ${SRC} -o ${BIN} ${OPT}
	echo "Versao dupla pronta"

versao:
	rm estruturas/versao.h
	echo "// Define qual a versão da lista (simples ou dupla), devera ser utilizada na compilacao" >> estruturas/versao.h
	echo "// Ao executar 'make simples' sera utilizada a versao simples, em que o no possui apenas um pointeiro" >> estruturas/versao.h
	echo "// Ao executar 'make dupla', o no tera tanto o ponteiro para o proximo no na lista, quanto para o anterior" >> estruturas/versao.h
	echo "/**" >> estruturas/versao.h
	echo " * Na prática isso não faz diferença alguma; eu precisava criar uma versão do programa utilizando lista simples" >> estruturas/versao.h
	echo " * e outra versão utilizando lista dupla, então criei esse artifício para não precisar copiar e colar o código," >> estruturas/versao.h
	echo " * mas acabou que eu nem utilizei efetivamente o ponteiro para o nó anterior, mesmo quando compilada a versão dupla." >> estruturas/versao.h
	echo " */" >> estruturas/versao.h

#!< FINAL MAKEFILE
