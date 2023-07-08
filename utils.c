#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"
#include "minHeap.h"
#include "limits.h"

/*
    Função hash criada criada para encriptar a senha de usuário,
*/

unsigned long long hashSenha(const char* str) {
    unsigned long long hash = 0;

    unsigned long long prime = 1099511628211ULL;  // Primo adequado para hash
    unsigned long long offset = 14695981039346656037ULL;  // Offset para hash

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        hash ^= str[i];
        hash *= prime;
    }

    hash ^= (hash >> 33);
    hash *= 0xff51afd7ed558ccdULL;
    hash ^= (hash >> 33);
    hash *= 0xc4ceb9fe1a85ec53ULL;
    hash ^= (hash >> 33);

    return hash + offset;
}


/*
    CRITÉRIOS DE VALIDAÇÃO DE SENHA:
        -Tamanho mínimo: 3
        -Deve ter pelo menos uma letra do alfabeto
*/
bool validarSenha(char *senha){
    int i;
    bool hasAlpha = false;
    for(i = 0; i<strlen(senha); i++){
        if(isalpha(senha[i]))
            hasAlpha = true;
    }
    return strlen(senha) >= 3 && hasAlpha;
}

bool validarLocalidade(Localidade *localidade, int ponto){
    bool problema  = true;
    if(localidade == NULL){
        printf("Localidade inexistente.\n");
        problema = false;
    }
    if(!(ponto>=1 && ponto<=localidade->numero_pontos)){
        printf("Ponto não encontrado.\n");
        problema = false;
    }
    return problema;
}
/*
    Algoritmo de Dijkstra para calcular a menor distancia
    apartir de um vertice de origem até todos os possíveis vertices
    no mesmo componente conexo
*/
int dijkstra( Localidade* localidade, int src, int dest){
     
    int V = localidade->numero_pontos;
   
    int dist[V + 1];    
 
    MinHeap* minHeap = criarMinHeap(V + 1);
 
    for (int v = 0; v <=V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = novoMinHeapNo(v,
                                      dist[v]);
        minHeap->pos[v] = v;
    }
 
    minHeap->array[src] =
          novoMinHeapNo(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    atualizarHeap(minHeap, src, dist[src]);
    minHeap->size = V + 1;
 
    while (!vazio(minHeap))
    {
         MinHeapNode* minHeapNode =
                     mininoElemento(minHeap);
       
        int u = minHeapNode->v;
 
        No* aux = localidade->ruas[u].principal;
        while (aux != NULL)
        {
            int v = aux->destino;
         if (estaNoHeap(minHeap, v) &&
                      dist[u] != INT_MAX &&
              aux->distancia + dist[u] < dist[v])
            {
                dist[v] = dist[u] + aux->distancia;
                atualizarHeap(minHeap, v, dist[v]);
            }
            aux = aux->prox;
        }
    }
 
    return dist[dest];
}

int ler_linha(char str[], int n) {
    int ch, i = 0;
    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;

    str[i] = '\0';
    return i;
}
