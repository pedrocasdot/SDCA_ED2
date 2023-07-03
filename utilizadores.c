#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "utilizadores.h"

HashTable* criarTabelaHash() {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    tabela->array = (Usuario**)malloc(TABLE_SIZE * sizeof(Usuario*));
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

bool inserirUsuario(HashTable* tabela, char *nome_usuario, char * senha) {
    int indice = calcularHash(nome_usuario);
    if(buscarUsuario(tabela,  nome_usuario) != NULL){
        printf("Nome de usuário já existente no sistema.\n");
        return false;
    }

    Usuario* novoNo = (Usuario*)malloc(sizeof(Usuario));
    novoNo->nome_usuario = strdup(nome_usuario);
    novoNo->senhaHasheada = hashSenha(senha);
    novoNo->prox = NULL;

    if (tabela->array[indice] == NULL) {
		tabela->array[indice] = novoNo;
    } else {
        Usuario* noAtual = tabela->array[indice];
        while (noAtual->prox != NULL) {
            noAtual = noAtual->prox;
        }
        noAtual->prox = novoNo;
    }
    return true;
}

Usuario * buscarUsuario(HashTable* tabela, char *nome_usuario) {
    
    int indice = calcularHash(nome_usuario);
    Usuario* noAtual = tabela->array[indice];
    while (noAtual != NULL) {
        if (strcmp(noAtual->nome_usuario, nome_usuario) == 0) {
            return noAtual;
        }
        noAtual = noAtual->prox;
    }
    return NULL;
    }

bool entrar(HashTable* tabela, char *nome_usuario, char *senha){
    Usuario *no = buscarUsuario(tabela, nome_usuario);
    if(no == NULL){
        printf("Usuário inexistente.\n");
        return false;
    } 

    unsigned long long senha_hash = hashSenha(senha);
    bool senha_correta = senha_hash == no->senhaHasheada;
    if(senha_correta)
        return senha_correta;
    else{
        printf("Senha incorrecta, tente novamente.\n");
        return false;
    }
}

bool removerUsuario(HashTable* tabela, char *nome_usuario, char *senha) {
    int indice = calcularHash(nome_usuario);
    Usuario* noAtual = tabela->array[indice];
    Usuario* noAnterior = NULL;
    
    while (noAtual != NULL) {
        if (strcmp(noAtual->nome_usuario, nome_usuario) == 0) {
            unsigned long long senha_hash = hashSenha(senha);
            bool senha_correta = senha_hash == noAtual->senhaHasheada;
            if(!senha_correta){
                printf("Senha de usuário incorrecta.\n");
                return false;
            }
            if (noAnterior == NULL) {
                tabela->array[indice] = noAtual->prox;
            } else {
                noAnterior->prox = noAtual->prox;
            }
            free(noAtual);
            printf("Usuario '%s' foi removido com sucesso.\n", nome_usuario);
            return true;
        }
        noAnterior = noAtual;
        noAtual = noAtual->prox;
    }
    printf("Usuário inexistente.\n");
    return false;
}
bool atualizarSenhaUsuario(HashTable * tabela, char *nome_usuario, char * senha_antiga, char *senha_nova){
    if(!tabela){
        printf("Nenhum usuario registrado\n");
        return false;
    }
    Usuario *no = buscarUsuario(tabela, nome_usuario);
    if(no == NULL){
        printf("Usuario inexistente\n");
        return false;
    }
     unsigned long long senha_hash = hashSenha(senha_antiga);
    bool senha_correta = senha_hash == no->senhaHasheada;
    if(senha_correta){
        no->senhaHasheada = hashSenha(senha_nova);
        printf("A senha para o usuário %s foi alterada com sucesso.\n", nome_usuario);
    }else{
        printf("Senha inválida para este nome de usuário, tente novamente....\n");
        return false;
    }
    return true;
}

void liberarTabelaHash(HashTable* tabela) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Usuario* noAtual = tabela->array[i];
        while (noAtual != NULL) {
            Usuario* noRemover = noAtual;
            noAtual = noAtual->prox;
            free(noRemover);
        }
    }

    free(tabela->array);
    free(tabela);
}
