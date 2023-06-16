#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localidade.h"


/*
    Funcao para criar o grafo inicial(Localidade)
*/
Localidade *criarLocalidade(int pontos, int ruas){
    
}
/*
    Funcao para remover vértice(PONTO) do grafo (LOCALIDADE)
*/
Localidade *removerPonto(Localidade *localidade, int ponto){}

/*
    Funcao para adicionar rua(ARESTA -> (A <---> B => distancia)) do grafo (LOCALIDADE)
*/
Localidade *adicionarRua(Localidade *localidae, int pontoA, int pontoB){}
/*
    Funcao para remover rua(ARESTA) do grafo (LOCALIDADE)
*/
Localidade *removerRua(Localidade *localidade, int pontoA, int pontoB){}
/*
    Funcao para atualizar distancia(em metros) entre dois vértices do grafo (LOCALIDADE)
*/
void actualizarDistancia(Localidade *localidade, int pontoA, int pontoB, int novaDistancia){}

/*
    Imprimir todas as ligações possíveis(Ai, Aj, distancia) no grafo (LOCALIDADE )
*/
void imprimirLigacoes(Localidade *localidade){}
void imprimirLigacoesOtimizadas(Localidade *localidade){}
int menorDistanciaAB(Localidade * localidade, int pontoA, int pontoB){}
void adicionarPonto(Localidade * localidade, int pontoA, int pontoB, int distancia){}
void destruirSimulacao(Localidade * localidade){}
