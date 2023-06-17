#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilizadores.h"
#include "localidade.h"

int main(){
    
    /*
    HashTable *ht = criarTabelaHash();
    
    if(inserirUsuario(ht, "teste", "teste")){
        puts("criado com sucesso");
    }
    if(atualizarSenhaUsuario(ht, "", "teste", "teste")){
        puts("FEITOOO");
    }
    if(removerUsuario(ht, "teste", "ABC123")){
        puts("GOOO");
    }
    if(buscarUsuario(ht, "teste") != NULL){
        puts("USUARIO EXISTENTE");
    }
    */
    Localidade *localidade = criarLocalidade(4, 3);
    imprimirLigacoes(localidade);
    removerPonto(localidade, 1);
    puts("depois de remover 1");
    imprimirLigacoes(localidade);
    
    return 0;
}