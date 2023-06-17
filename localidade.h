#ifndef LOCALIDADE_H
#define LOCALIDADE_H

typedef struct No{
    int destino, distancia;
    struct No *prox;    
}No;

typedef struct AdjList{
    No *principal; 
}AdjList;



typedef struct Localidade{
    int numero_pontos;
    AdjList * ruas;
}Localidade;


void removerPonto(Localidade *localidade, int ponto);
Localidade *criarLocalidade(int pontos, int ruas);
void adicionarRua(Localidade *localidade, int pontoA, int pontoB, int distancia);
Localidade *removerRua(Localidade *localidade, int pontoA, int pontoB);
void actualizarDistancia(Localidade *localidade, int pontoA, int pontoB, int novaDistancia);
void imprimirLigacoes(Localidade *localidade);
void imprimirLigacoesOtimizadas(Localidade *localidade);
int menorDistanciaAB(Localidade * localidade, int pontoA, int pontoB);
void adicionarPonto(Localidade * localidade, int pontoA, int pontoB, int distancia);
void destruirSimulacao(Localidade * localidade);

#endif
