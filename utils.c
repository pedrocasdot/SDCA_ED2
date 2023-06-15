#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
    Usando cifra de césar para encriptar e 
        decriptar senhas de usuários na tabela de usuaŕios.
*/

char *encriptarSenha(char *senha) {
    for(int i = 0; senha[i] != '\0'; i++){
        if(isalpha(senha[i])){
            if(isalpha(senha[i]))
                senha[i] = ((((tolower(senha[i]) - 97) + 3)%26) + 97);
        }    
    }
	return senha;
}

char *decriptarSenha(char *senha) {
    for(int i = 0; senha[i] != '\0'; i++){
        if(isalpha(senha[i]))
            senha[i] = (((((tolower(senha[i]) - 97) - 3)%26) + 97));
    }
	return senha;
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
