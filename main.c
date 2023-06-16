#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilizadores.h"

int main(){
    
    HashTable *ht = criarTabelaHash();
    
    if(inserirUsuario(ht, "adilsonpedro", "teste")){
        puts("criado com sucesso");
    }
    if(atualizarSenhaUsuario(ht, "adilsonpedro", "teste", "ABC123")){
        puts("FEITOOO");
    }
    if(removerUsuario(ht, "adilsonpedro", "ABC123")){
        puts("GOOO");
    }
    if(buscarUsuario(ht, "adilsonpedro") == NULL){
        puts("USUARIO INEXISTENTE");
    }
   
    return 0;
}