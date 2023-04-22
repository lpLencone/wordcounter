//!< INICIO NO_C

#include "../include/no.h"

#include <stdlib.h>
#include <string.h>

struct no * 
no_iniciar(void *info, size_t bytes, void (*free_info)(void *info))
{
    struct no *no = (struct no *)malloc(sizeof(struct no));
    
    // Alterar ponteiro para nó anterior apenas caso a versão definida do programa seja `dupla`
    #ifdef VERSAO_DUPLA
        no->ante = NULL;
    #endif
    no->prox = NULL;
    no->info = malloc(bytes);
    memcpy(no->info, info, bytes);
    no->free_info = free_info;
    return no;
}

void 
no_destruir(struct no *no)
{
    // Se houver, liberar memória alocada para ponteiros armazenados dentro de `info` com função personalizada
    if (no->free_info != NULL) {
        // Tal função não deverá liberar a memória do próprio membro
        no->free_info(no->info);
    }
    free(no->info);
    free(no);
}

//!< FINAL NO_C