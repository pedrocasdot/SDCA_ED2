#ifndef LOCALIDADE_H
#define LOCALIDADE_H

typedef struct No{
    int destino, distancia;
    struct No *prox;    
}No;

typedef struct Localidade{
    int pontos;
    No * ruas;
}Localidade;


#endif
