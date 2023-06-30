#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "localidade.h"
#include "utils.h"
#include "minHeap.h"


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
    if(pontos < 0){
        printf("Número de pontos inválido.\n");
        return NULL;
    }
    if(ruas < 0){
        printf("Número de ruas inválidas.\n");
        return NULL;
    }
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
    if(localidade == NULL){
        printf("Localidade inexistente\n");
        return;
    }
    if(!(localidade->numero_pontos>=ponto && ponto>0)){
        printf("Ponto inválido.\n");
        return;
    }
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
    if(localidade == NULL){
        printf("Localidade inexistente\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoA && pontoA>0)){
        printf("Ponto A inválido.\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoB && pontoB>0)){
        printf("Ponto B inválido.\n");
        return;
    }
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
void removerRua(Localidade *localidade, int pontoA, int pontoB){
    if(localidade == NULL){
        printf("Localidade inexistente\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoA && pontoA>0)){
        printf("Ponto A inválido.\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoB && pontoB>0)){
        printf("Ponto B inválido.\n");
        return;
    }
    No *aux = localidade->ruas[pontoA].principal;
    while (aux != NULL && aux->destino == pontoB) {
            No *temp = aux;
            aux = aux->prox;
            localidade->ruas[pontoA].principal = aux;  // Atualizar o ponteiro principal
            free(temp);
        }
        // Remover outros nós
        while (aux != NULL && aux->prox != NULL) {
            if (aux->prox->destino == pontoB) {
                No *temp = aux->prox;
                aux->prox = temp->prox;
                free(temp);
            } else {
                aux = aux->prox;
            }
        }
        aux = localidade->ruas[pontoB].principal;
        while (aux != NULL && aux->destino == pontoA) {
            No *temp = aux;
            aux = aux->prox;
            localidade->ruas[pontoB].principal = aux;  // Atualizar o ponteiro principal
            free(temp);
        }

        // Remover outros nós
        while (aux != NULL && aux->prox != NULL) {
            if (aux->prox->destino == pontoA) {
                No *temp = aux->prox;
                aux->prox = temp->prox;
                free(temp);
            } else {
                aux = aux->prox;
            }
        }
}
/*
    Funcao para atualizar distancia(em metros) entre dois vértices do grafo (LOCALIDADE)
*/
void actualizarDistancia(Localidade *localidade, int pontoA, int pontoB, int novaDistancia){
    if(localidade == NULL){
        printf("Localidade inexistente\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoA && pontoA>0)){
        printf("Ponto A inválido.\n");
        return;
    }
    if(!(localidade->numero_pontos>=pontoB && pontoB>0)){
        printf("Ponto B inválido.\n");
        return;
    }
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
    if(localidade == NULL){
        printf("Localidade inexistente.\n");
        return;
    }
    int i = 0;
    for(; i < localidade->numero_pontos; i++){
        No * aux = localidade->ruas[i + 1].principal;
        while(aux){
            printf("%d <--> %d distancia de %d metros.\n", i + 1, aux->destino, aux->distancia);
            aux = aux->prox;
        }
    }
}

void _imprimirMST(int parent[], int n) {
    for (int i = 1; i <= n; i++) {
        printf ("%d <--> %d\n", parent[i], i);
    }
}

/*
    Imprime a conexão mais barata entre pontos.
    Consiste em construir uma árvore de expansão mínima usando o algoritmo de Prim.
*/
void imprimirLigacoesOtimizadas(Localidade *localidade){
    int V = localidade->numero_pontos;
    int parent[V];
    int key[V];

    MinHeap *heap = criarMinHeap(V);

    for (int v = 1; v <= V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        heap->array[v] = novoMinHeapNo(v, key[v]);
        heap->pos[v] = v;
    }

    key[0] = 0;
    heap->array[0] = novoMinHeapNo(0, key[0]);
    heap->pos[0] = 0;

    heap->size = V;

    while (!vazio(heap)) {
        MinHeapNode *node = mininoElemento(heap);
        int u = node->v;

        No *pCrawl = localidade->ruas[u].principal;
        while (pCrawl != NULL) {
            int v = pCrawl->destino;

            if (estaNoHeap(heap, v) && pCrawl->distancia < key[v]) {
                    key[v] = pCrawl->distancia;
                    parent[v] = u;
                    atualizarHeap(heap, v, key[v]);
            }
            
            pCrawl = pCrawl->prox;
        }

        _imprimirMST(parent, V);
    }
}

int menorDistanciaAB(Localidade * localidade, int pontoA, int pontoB){
    if(localidade == NULL){
        printf("Localidade inexistente.\n");
        return -1;
    }
    if(!(localidade->numero_pontos>=pontoA && pontoA>0)){
        printf("Ponto A inválido.\n");
        return -1;
    }
    if(!(localidade->numero_pontos>=pontoB && pontoB>0)){
        printf("Ponto B inválido.\n");
        return -1;
    }
    int menorDistancia = dijkstra(localidade, pontoA, pontoB);
    if(menorDistancia == INT_MAX){
        return -1;
    }
    return menorDistancia;
}
void adicionarPonto(Localidade * localidade, int pontoA){
    if(localidade == NULL){
        printf("Localidade inexistente!");
        return;
    }
    if(pontoA > 0 && pontoA<= localidade->numero_pontos ){
        if(localidade->ruas[pontoA].principal != NULL){
            printf("Este ponto já existe!");
            return;
        }
    }
    int numPontosAnterior = localidade->numero_pontos;
    localidade->numero_pontos = pontoA;
    localidade->ruas = (AdjList *)realloc(localidade->ruas, (localidade->numero_pontos  + 1)* sizeof(AdjList));
    
    int i;
    for(i = numPontosAnterior; i<=localidade->numero_pontos; i++)
        localidade->ruas[i].principal = NULL;
    
    int numero_ligacoes;
    printf("Quantas ligações deseja adicionar?\n");
    scanf("%d", &numero_ligacoes);
    int pontoB, distancia;
    for(i = 0; i<numero_ligacoes; i++){
        printf("%d - Digite o ponto e a distancia para a ligação do ponto %d\n", i + 1, pontoA);
        scanf("%d%d", &pontoB, &distancia);
        adicionarRua(localidade, pontoA, pontoB, distancia);
    }
    printf("Ponto adicionado com sucesso\n");
}
void destruirSimulacao(Localidade * localidade){
    for (int i = 1; i <=localidade->numero_pontos; i++) {
        No* noActual = localidade->ruas[i].principal;
        while (noActual != NULL) {
            No* noRemover = noActual;
            noActual = noActual->prox;
            free(noRemover);
        }
    }
    free(localidade->ruas);
    free(localidade);
}