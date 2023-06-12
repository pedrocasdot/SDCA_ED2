#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "utils.h"

HashTable* criarTabelaHash() {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    tabela->array = (HashNode**)malloc(TABLE_SIZE * sizeof(HashNode*));

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela->array[i] = NULL;
    }

    return tabela;
}

int calcularHash(char *chave) {
    int hash_soma = 0;
	for(int i = 0; chave[i] != '\0'; i++){
		hash_soma = hash_soma * 31 + chave[i];
	}
	return hash_soma % TABLE_SIZE;
}

bool inserirUsuario(HashTable* tabela, char *nome_usuario, char *senha) {
    int indice = calcularHash(nome_usuario);
    if(buscarUsuario(tabela,  nome_usuario) != NULL){
        printf("Nome de usuário já existente no sistema.\n");
        return false;
    }
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    novoNo->nome_usuario = strdup(nome_usuario);
    novoNo->senha = strdup(encriptarSenha(senha));
    novoNo->prox = NULL;

    if (tabela->array[indice] == NULL) {
		tabela->array[indice] = novoNo;
    } else {
        HashNode* noAtual = tabela->array[indice];
        while (noAtual->prox != NULL) {
            noAtual = noAtual->prox;
        }
        noAtual->prox = novoNo;
    }
    return true;
}

HashNode * buscarUsuario(HashTable* tabela, char *nome_usuario) {
    
    int indice = calcularHash(chave);
    HashNode* noAtual = tabela->array[indice];
    while (noAtual != NULL) {
        if (strcmp(noAtual->chave, chave) == 0) {
            return noAtual;
        }
        noAtual = noAtual->prox;
    }
    return NULL;
}

bool entrar(HashTable* tabela, char *nome_usuario, char *senha){
    HashNode *no = buscar(tabela, nome_usuario);
    if(no == NULL){
        printf("Usuário inexistente.\n");
        return false;
    }    
    if(strcmp(no->nome_usuario, nome_usuario) == 0 && strcmp(decriptarSenha(no->senha), senha) == 0){
        return true;
    }else{
        printf("Senha incorrecta, tente novamente.\n");
        return false;
    }
}

bool removerUsuario(HashTable* tabela, char *nome_usuario, char *senha) {
    int indice = calcularHash(chave);
    HashNode* noAtual = tabela->array[indice];
    HashNode* noAnterior = NULL;
    
    while (noAtual != NULL) {
        if (strcmp(noAtual->nome_usuario, nome_usuario) == 0) {
            if(strcmp(decriptarSenha(noAtual->senha),  senha) != 0){
                printf("Senha de usuário incorrecta.\n");
                return false;
            }
            if (noAnterior == NULL) {
                tabela->array[indice] = noAtual->prox;
            } else {
                noAnterior->prox = noAtual->prox;
            }
            free(noAtual);
        }
        noAnterior = noAtual;
        noAtual = noAtual->prox;
    }
    return true;    
}
bool atualizarSenhaUsuario(HashTable * tabela, char *nome_usuario, char * senha_antiga, char *senha_nova){
    if(!tabela){
        printf("Nenhum usuario registrado\n");
        return false;
    }
    HashNode *no = buscar(tabela, nome_usuario);
    if(no == NULL){
        printf("Usuario inexistente\n");
        return false;
    }
    if(strcmp(decriptarSenha(no->senha), senha_antiga) == 0){
        if(!validarSenha(senha_nova)){
            printf("A senha deve ter no mínimo 3 caracteres e uma letra do alfabeto\n");
            return false;
        }
        no->senha = strdup(encriptarSenha(senha_nova));    
        printf("A senha para o usuário %s foi alterada com sucesso\n", nome_usuario);
    }else{
        printf("Senha inválida para este nome de usuário, tente novamente...");
        return false;
    }
    return true;
}

void liberarTabelaHash(HashTable* tabela) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* noAtual = tabela->array[i];
        while (noAtual != NULL) {
            HashNode* noRemover = noAtual;
            noAtual = noAtual->prox;
            free(noRemover);
        }
    }

    free(tabela->array);
    free(tabela);
}
