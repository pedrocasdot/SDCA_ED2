#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "localidade.h"

char *encriptarSenha(char *senha);
char *decriptarSenha(char *senha);
char *tudoMinusculo(char *string);
bool validarSenha(char *senha);
void removerNo(No * head, int ponto);
int dijkstra( Localidade* localidade, int src, int dest);
#endif