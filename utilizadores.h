#ifndef HASHTABLE_H
#define HASHTABLE_H


#define TABLE_SIZE 97

#include <stdbool.h>
typedef struct HashNode{
	char * nome_usuario;
	char * senha;
	struct HashNode * prox;
}HashNode;

typedef struct HashTable{
	HashNode**array;
}HashTable;

HashTable* criarTabelaHash();

int calcularHash(char *chave);

bool inserirUsuario(HashTable* tabela, char * nome_usuario, char * senha);

HashNode  *buscarUsuario(HashTable* tabela, char *nome_usuario);

bool atualizarSenhaUsuario(HashTable * tabela, char *chave, char * senha_antiga, char * senha_nova);

bool removerUsuario(HashTable* tabela, char *nome_usuario, char *senha);

bool entrar(HashTable* tabela, char *nome_usuario, char *senha);

void liberarTabelaHash(HashTable* tabela);
#endif
