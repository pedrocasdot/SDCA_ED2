#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilizadores.h"
#include "localidade.h"
#include "menu.h"
int main(){
   HashTable *ht = criarTabelaHash();
   Localidade *localidade;
    
    
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
    Localidade*localidade = criarLocalidade(4, 3);
    imprimirLigacoes(localidade);
    removerPonto(localidade, 1);
    puts("depois de remover 1");
    imprimirLigacoes(localidade);

    puts("testando com o José");
    return 0;
}