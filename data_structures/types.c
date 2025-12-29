#include "types.h"

#include <stdio.h>
#include <stdlib.h>

void freeReg(Item item, void* extra){
    UNUSED(extra);
    free(item);
}

bool checkAllocation(void* var, const char* text){
    // Caso a varia'vel passada for nula, lanca uma mensagem de erro.
    if(var == NULL){
        printf("\n[!] ERRO DE ALOCACAO: %s", text);
        return true;
    }
    return false;
}