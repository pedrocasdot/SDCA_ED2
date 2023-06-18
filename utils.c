#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"
#include "minHeap.h"
#include "limits.h"

/*
    Usando cifra de césar para encriptar e 
        decriptar senhas de usuários na tabela de usuaŕios.
*/

char *encriptarSenha(char *senha) {
    char* resultado = (char*)malloc((strlen(senha) + 1) * sizeof(char));
    for(int i = 0; i < strlen(senha); i++){
        if(isalpha(senha[i])){
            resultado[i]= ((tolower(senha[i]) - 'a' + 3) % 26) + 'a';
        }else resultado[i] = senha[i];    
    }
    return resultado;
}

char *decriptarSenha(char *senha) {
    char* resultado = (char*)malloc((strlen(senha) + 1) * sizeof(char));
    for(int i = 0; i < strlen(senha); i++){
        if(isalpha(senha[i])){
            resultado[i]= ((tolower(senha[i]) - 'a' - 3) % 26) + 'a';
        }else resultado[i] = senha[i];    
    }
    return resultado;
}

char *tudoMinusculo(char *string) {
    char* resultado = (char*)malloc((strlen(string) + 1) * sizeof(char));
    for(int i = 0; i < strlen(string); i++){
        if(isalpha(string[i])){
            resultado[i]= tolower(string[i]);
        }else resultado[i] = string[i];    
    }
    return resultado;
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

