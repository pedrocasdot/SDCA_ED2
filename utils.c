#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"

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
