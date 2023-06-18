#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "localidade.h"
#include "utils.h"


/*
    Funcao para criar o grafo inicial(Localidade)
*/
No * novo_no(int destino, int distancia){

    No * no = (No *)malloc(sizeof(No));
    if(!no){
        printf("Erro: não foi possível criar um novo 'NO'");
        return NULL;
    }
    no->destino = destino;
    no->distancia = distancia;
    no->prox = NULL;
    
    return no;
}

Localidade *criarLocalidade(int pontos, int ruas){
    Localidade *nova_localidade = (Localidade *)malloc(sizeof(Localidade));
    
    nova_localidade->numero_pontos = pontos;

    nova_localidade->ruas = (AdjList *)malloc((pontos  + 1)* sizeof(AdjList));

    int i = 0;
    for( ; i < pontos + 1; i++){
        nova_localidade->ruas[i].principal = NULL;
    }
    
    int pontoA, pontoB, distancia;
    for(i = 0; i<ruas; i++){
        printf("Digite os dois pontos que ligam a rua %d e distância.[A  B Distancia]\n", i + 1);
        scanf("%d %d %d", &pontoA, &pontoB, &distancia);
        adicionarRua(nova_localidade, pontoA, pontoB, distancia);
    }

    return nova_localidade;
}
/*
    Funcao para remover vértice(PONTO) do grafo (LOCALIDADE)
*/
void removerPonto(Localidade *localidade, int ponto){
    No *aux;
    /*
        Para cada lista associada a um ponto, remove-se o ponto a ser
        procurado.
    */
    for(int i = 0; i < localidade->numero_pontos + 1; i++){
        aux = localidade->ruas[i].principal;

        // Verificar se o primeiro nó precisa ser removido
        while (aux != NULL && aux->destino == ponto) {
            No *temp = aux;
            aux = aux->prox;
            localidade->ruas[i].principal = aux;  // Atualizar o ponteiro principal
            free(temp);
        }

        // Remover outros nós
        while (aux != NULL && aux->prox != NULL) {
            if (aux->prox->destino == ponto) {
                No *temp = aux->prox;
                aux->prox = temp->prox;
                free(temp);
            } else {
                aux = aux->prox;
            }
        }
    }
    /*
        Depois remove-se a lista do ponto em questão
    */
    aux = localidade->ruas[ponto].principal;
    while(aux){
        No *temp = aux;
        aux = aux->prox;
        localidade->ruas[ponto].principal = aux;
        free(temp);
    }
}

/*
    Funcao para adicionar rua(ARESTA -> (A <---> B => distancia)) do grafo (LOCALIDADE)
*/
void adicionarRua(Localidade *localidade, int pontoA, int pontoB, int distancia){
    No * aux = NULL;
    No *novoNo = novo_no(pontoB, distancia);

    if(localidade->ruas[pontoA].principal == NULL){
        novoNo->prox = localidade->ruas[pontoA].principal;
        localidade->ruas[pontoA].principal = novoNo;
    }else{

        aux = localidade->ruas[pontoA].principal;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novoNo;
    }
    // assumindo que o grafo não é direcionado
    // então se A ---> B, B ---> A => A <--> B
    novoNo = novo_no(pontoA, distancia);

    if(localidade->ruas[pontoB].principal == NULL){
        novoNo->prox = localidade->ruas[pontoB].principal;
        localidade->ruas[pontoB].principal = novoNo;
    }else{

        aux = localidade->ruas[pontoB].principal;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novoNo;
    }
}
/*
    Funcao para remover rua(ARESTA) do grafo (LOCALIDADE)
*/
Localidade *removerRua(Localidade *localidade, int pontoA, int pontoB){
    
}
/*
    Funcao para atualizar distancia(em metros) entre dois vértices do grafo (LOCALIDADE)
*/
void actualizarDistancia(Localidade *localidade, int pontoA, int pontoB, int novaDistancia){
    No * aux = NULL;
    if(localidade->ruas[pontoA].principal == NULL 
            || localidade->ruas[pontoB].principal == NULL){
                printf("Não existe ligação entre estes dois pontos");
                return;
    }
    /*
        Assumindo que o grafo é não-direcionado, então
        se actualizarmos a distância de A ---> B, temos de alterar também
        a distância de B ---> A
    */
    aux = localidade->ruas[pontoA].principal;
    bool existeLigacao = false;
    while(aux){
        if(aux->destino == pontoB){
            aux->distancia = novaDistancia;
            existeLigacao|=true;
        }
        aux = aux->prox;
    }
    aux = localidade->ruas[pontoB].principal;

    while(aux){
        if(aux->destino == pontoA){
            aux->distancia = novaDistancia;
            existeLigacao|=true;
        }
        aux = aux->prox;
    }
    if(!existeLigacao){
        printf("Não foi possível actualizar a distância entre estes dois pontos\n,porque não são adjacentes.\n");
    }else{
        printf("A distância entre os pontos %d  e %d foi actualizada com sucesso.\n", pontoA, pontoB);
    }
}

/*
    Imprimir todas as ligações possíveis(Ai, Aj, distancia) no grafo (LOCALIDADE )
*/
void imprimirLigacoes(Localidade *localidade){
    int i = 0;
    for(; i < localidade->numero_pontos; i++){
        No * aux = localidade->ruas[i + 1].principal;
        while(aux){
            printf("%d <--> %d distancia de %d metros.\n", i + 1, aux->destino, aux->distancia);
            aux = aux->prox;
        }
    }
}

void _imprimirMST(Localidade *localidade, int pai[]) {
    for (int i = 1; i <= localidade->numero_pontos; i++) {
        printf ("%d <--> %d, distância de %d metros.\n"
            pai[i], i, localidade->ruas[pai[i]]);
    }
}

/*
    Imprime a conexão mais barata entre pontos.
    Consiste em construir uma árvore de expansão mínima usando o algoritmo de Prim.
*/
void imprimirLigacoesOtimizadas(Localidade *localidade){
    No *aux = NULL;
    int numv = localidade->numero_pontos;
    bool na_mst[numv+1];      // O nó está na MST?
    int distancia[numv+1];    // Custo de adicionar ao mst
    int pai[numv];          // mst
    int ponto;              // Vértice a ser processado
    int prox_ponto;         // Próximo vértice candidato
    int dist;               // no->distancia, valor da aresta
    int melhor_dist;        // Atual melhor distância do princípio

    for (int i = 1; i <= numv; i++) {
        na_mst[i] = false;
        distancia[i] = INT_MAX;
        pai[i] = -1;
    }

    // O algoritmo começa no primeiro nó
    // 1-index based
    distancia[1] = 0;
    ponto = 1;

    while (na_mst[ponto] == false) {
        na_mst[ponto] = true;
        aux = localidade->ruas[ponto]->principal;
        while (aux != NULL) {
            melhor_dist = aux->destino;
            dist = aux->distancia;
            if ((distancia[melhor_dist] > dist) && (mst[melhor_dist] == false)) {
                distancia[melhor_dist] = dist;
                pai[melhor_dist] = ponto;
            }
            aux = aux->prox;
        }
    }

    dist = 1;
    melhor_dist = INT_MAX;
    for (int i = 1; i <= numv; i++)
        if ((na_mst[i] == false) && (melhor_dist > distancia[i])) {
            melhor_dist = distancia[i];
            ponto = i;
        }

    _imprimirMST(localidade, pai);
}

int menorDistanciaAB(Localidade * localidade, int pontoA, int pontoB){
    int menorDistancia = dijkstra(localidade, pontoA, pontoB);
    if(menorDistancia == INT_MAX){
        return -1;
    }
    return menorDistancia;
}
void adicionarPonto(Localidade * localidade, int pontoA, int pontoB, int distancia){}
void destruirSimulacao(Localidade * localidade){}
