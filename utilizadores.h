#ifndef HASHTABLE_H
#define HASHTABLE_H


#define TABLE_SIZE 97
#define TAM_STR 100

#include <stdbool.h>
typedef struct Usuario{
	char * nome_usuario;
	unsigned long long  senhaHasheada;
	struct Usuario * prox;
}Usuario;

typedef struct HashTable{
	Usuario**array;
}HashTable;

HashTable* criarTabelaHash();

int calcularHash(char *chave);

bool inserirUsuario(HashTable* tabela, char * nome_usuario, char * senha);

Usuario  *buscarUsuario(HashTable* tabela, char *nome_usuario);

bool atualizarSenhaUsuario(HashTable * tabela, char *nome_usuario, char * senha_antiga, char * senha_nova);

bool removerUsuario(HashTable* tabela, char *nome_usuario, char *senha);

bool entrar(HashTable* tabela, char *nome_usuario, char *senha);

bool tabelaVazia(HashTable *tabela);

void liberarTabelaHash(HashTable* tabela);
#endif
