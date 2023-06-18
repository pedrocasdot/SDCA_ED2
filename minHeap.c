#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "minHeap.h"
#include "localidade.h"

MinHeapNode * novoMinHeapNo(int v, int dist){
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
MinHeap* criarMinHeap(int capacity){
     MinHeap* minHeap =
         ( MinHeap*)
      malloc(sizeof( MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         ( MinHeapNode**)
                 malloc(capacity *
       sizeof( MinHeapNode*));
    return minHeap;
}
/*
    Função para trocar nós
*/
void trocarMinHeapNo( MinHeapNode** a, MinHeapNode** b){
     MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(MinHeap* minHeap, int idx){
    int menor, esquerda, direita;
    menor = idx;
    esquerda = 2 * idx + 1;
    direita = 2 * idx + 2;

    if (esquerda < minHeap->size && minHeap->array[esquerda]->dist < minHeap->array[menor]->dist)
        menor = esquerda;

    if (direita < minHeap->size && minHeap->array[direita]->dist < minHeap->array[menor]->dist)
        menor = direita;

    if (menor != idx)
    {
        // Os nós a serem trocados no heap mínimo
        MinHeapNode *menorNo = minHeap->array[menor];
        MinHeapNode *idxNo = minHeap->array[idx];

        // Troca as posições
        minHeap->pos[menorNo->v] = idx;
        minHeap->pos[idxNo->v] = menor;

        // Troca os nós
        trocarMinHeapNo(&minHeap->array[menor], &minHeap->array[idx]);

        minHeapify(minHeap, menor);
    }
}
/* 
    Funcao para verificar se o heap
    está vazio ou não
*/
int vazio( MinHeap* minHeap){
    return minHeap->size == 0;
}
 
 MinHeapNode* mininoElemento( MinHeap* minHeap){
    if (vazio(minHeap))
        return NULL;
 
     MinHeapNode* root =
                   minHeap->array[0];
 
     MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void atualizarHeap( MinHeap* minHeap, int v, int dist){
    int i = minHeap->pos[v];
 
    minHeap->array[i]->dist = dist;
 
    while (i && minHeap->array[i]->dist <
           minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        trocarMinHeapNo(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}

/*
    Função para verificar se um dado
    vertice está no heap
*/
bool estaNoHeap( MinHeap *minHeap, int v){
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}