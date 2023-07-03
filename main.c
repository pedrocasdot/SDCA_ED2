#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilizadores.h"
#include "localidade.h"
#include "menu.h"
int main(){
  // HashTable *ht = criarTabelaHash();
   //Localidade *localidade;
    
    HashTable *ht = criarTabelaHash();
    
    if(inserirUsuario(ht, "teste", "123")){
        puts("criado com sucesso");
    }
    if(atualizarSenhaUsuario(ht, "teste", "123", "teste")){
        puts("FEITOOO");
    }
    if(removerUsuario(ht, "teste", "teste")){
        puts("GOOO");
    }
    if(buscarUsuario(ht, "teste") != NULL){
        puts("USUARIO EXISTENTE");
    }

    Localidade*localidade = criarLocalidade(10, 14);
    imprimirLigacoes(localidade);
    //imprimirLigacoesOtimizadas(localidade);
    adicionarPonto(localidade, 11);

    printf("menor distancia %d\n", menorDistanciaAB(localidade, 1, 11)); 
    imprimirLigacoes(localidade);
    //destruirSimulacao(localidade);
    return 0;
}