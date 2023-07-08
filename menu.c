#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "localidade.h"
#include "utilizadores.h"
#include "utils.h"

int obter_opcao(int min, int max);
int imprimir_menu_iniciar_e_obter_opcao();
void iniciar();
Localidade *opcao_criar_localidade();
HashTable *opcao_cadastrar_utilizadores(HashTable *utilizadores);
void opcao_alterar_senha(HashTable *utilizadores);
void opcao_remover_utilizador(HashTable *utilizadores);
int opcao_simulacao(Localidade *localidade, HashTable *utilizadores);
bool autenticar(HashTable *utilizadores);

// Funções para as opções da simulação
void opcao_adicionar_ponto(Localidade *localidade);
void opcao_adicionar_rua(Localidade *localidade);
void opcao_remover_ponto(Localidade *localidade);
void opcao_adicionar_rua(Localidade *localidade);
void opcao_eliminar_rua(Localidade *localidade);
void opcao_actualizar_distancia(Localidade *localidade);
void opcao_custo_optimo(Localidade *localidade);

void iniciar() {
	Localidade *localidade = NULL;
	HashTable *utilizadores = NULL;
	while (true) {
		int opcao = imprimir_menu_iniciar_e_obter_opcao();
		printf("\n");

		switch (opcao)
		{ 
			case 1:
				localidade = opcao_criar_localidade();
				break;

			case 2:
				utilizadores = opcao_cadastrar_utilizadores(utilizadores);
				break;

			case 3:
				opcao_alterar_senha(utilizadores);
				break;

			case 4:
				opcao_remover_utilizador(utilizadores);
				break;

			case 5:
				int op = opcao_simulacao(localidade, utilizadores);
				if (op == 9)
					localidade = NULL;
				break;
			case 0:
				break;

		}
		printf("\n");
		if (opcao == 0)
			break;
	}
}
int obter_opcao(int min, int max) {
	int opcao;
	while (true) {
		printf("Opção[%d-%d]: ", min, max);
		scanf("%d", &opcao);
		if (opcao >= min && opcao <= max)
			break;
		else
			printf("Erro: Opção inválida.\n");
	}
	return opcao;
}

// Imprime o menu e retorna a opção
int imprimir_menu_iniciar_e_obter_opcao() {
	printf("[1] Criar localidade      \n");
	printf("[2] Cadastrar utilizador  \n");
	printf("[3] Alterar senha         \n");
	printf("[4] Remover utilizador    \n");
	printf("[5] Simulação             \n");
	printf("[0] Sair                  \n\n");
	return obter_opcao(0, 5);
}

Localidade *opcao_criar_localidade() {
	int pontos, ruas;
	while (true) {
		printf("Quantos cruzamentos a sua localidade tem?: ");
		scanf("%d", &pontos);
		if (pontos > 0)
			break;
		else
			printf("Erro: Insira um número maior que zero\n");
	}

	while (true) {
		printf("Quantas ruas a sua localidade tem?: ");
		scanf("%d", &ruas);
		if (ruas > 0)
			break;
		else
			printf("Erro: Insira um número maior que zero\n");
	}

	return criarLocalidade(pontos, ruas);
}


HashTable *opcao_cadastrar_utilizadores(HashTable *utilizadores) {
	HashTable *users = utilizadores;
	if (utilizadores == NULL) 
		users = criarTabelaHash();
	
	int qtd_users;
	while(true) {
		printf ("Quantos usuários pretende cadastrar?[1-%d]: ", TABLE_SIZE);
		scanf("%d", &qtd_users);
		if (qtd_users >= 1 && qtd_users <= TABLE_SIZE)
			break;
		else {
			printf("Erro: Só pode cadastrar entre 1 e %d usuários\n", TABLE_SIZE);
		}
	}

	/* 
		Remove algum '\n' do stdin, se houver.
		Melhor curso de ação seria escrever uma solução personalisada para leitura de dados.
	*/
	getchar(); 
	for (int i = 1; i <= qtd_users; i++) {
		char nome_usuario[TAM_STR + 1]; // TAM_STR + 1 para acomodar o '\0'
		char senha[TAM_STR + 1];
		printf ("Usuário %d:\n", i);

		printf ("Nome de usuário: ");
		ler_linha(nome_usuario, TAM_STR);

		printf ("Senha: ");
		ler_linha(senha, TAM_STR);

		inserirUsuario(users, nome_usuario, senha);
	}

	return users;
}

void opcao_alterar_senha(HashTable *utilizadores) {
	char nome_usuario[TAM_STR + 1], antiga_senha[TAM_STR + 1],
		nova_senha[TAM_STR + 1];
	printf ("Nome de usuário: ");
	getchar();
	ler_linha(nome_usuario, TAM_STR);

	printf("Antiga senha: ");
	ler_linha(antiga_senha, TAM_STR);
	
	printf("Nova senha: ");
	ler_linha(nova_senha, TAM_STR);

	atualizarSenhaUsuario(utilizadores, nome_usuario, antiga_senha, nova_senha);
}

void opcao_remover_utilizador(HashTable *utilizadores) {
	if (tabelaVazia(utilizadores)) {
		printf("Tabela de utilizadores vazia\n");
		return;
	}
	char nome_usuario[TAM_STR + 1], senha[TAM_STR + 1];

	printf ("Nome de usuário: ");
	getchar();
	ler_linha(nome_usuario, TAM_STR);

	printf("Senha: ");
	ler_linha(senha, TAM_STR);
	
	removerUsuario(utilizadores, nome_usuario, senha);
}

// Retorna a última opção escolhida pelo usuário
int opcao_simulacao(Localidade *localidade, HashTable *utilizadores) {
	if (localidade == NULL) {
		printf ("Erro: Localidade inexistente.\n");
		return -1;
	}

	if (utilizadores == NULL || tabelaVazia(utilizadores)) {
		printf("Erro: Tabela de utilizadores nula\n");
		return -1;
	}
	bool autenticado = autenticar(utilizadores);
	if (!autenticado) {
		printf("Erro: Nome de usuário ou senha incorretas\n");
		return -1;
	}

	int opcao;
	while (true) {
		printf("[1] Adicionar ponto   \n");
		printf("[2] Remover ponto     \n");
		printf("[3] Adicionar rua      \n");
		printf("[4] Eliminar rua      \n");
		printf("[5] Actualizar distância               \n");
		printf("[6] Imprimir todas as ligaçoes e custo \n");
		printf("[7] Imprimir ligações optimizadas      \n"); 
		printf("[8] Custo óptimo entre dois pontos     \n");
		printf("[9] Destruir simulação      \n");
		printf("[0] Voltar\n");
		int opcao = obter_opcao(0, 9);
		printf("\n");

		switch (opcao) {
			case 1:
				opcao_adicionar_ponto(localidade);
				break;
			case 2:
				opcao_remover_ponto(localidade);
				break;
			case 3:
				opcao_adicionar_rua(localidade);
				break;
			case 4:
				opcao_eliminar_rua(localidade);
				break;
			case 5:
				opcao_actualizar_distancia(localidade);
				break;
			case 6:
				imprimirLigacoes(localidade);
				break;
			case 7:
				imprimirLigacoesOtimizadas(localidade);
				break;
			case 8:
				opcao_custo_optimo(localidade);
				break;
			case 9:
				destruirSimulacao(localidade);
				break;
			case 0:
				break;
		}
		printf("\n");
		if (opcao == 9 || opcao == 0)
			return opcao;
	}
}

bool autenticar(HashTable *utilizadores) {
	char nome_usuario[TAM_STR + 1], senha[TAM_STR + 1];
	printf ("Nome de usuário: ");
	getchar();
	ler_linha(nome_usuario, TAM_STR);

	printf("Senha: ");
	ler_linha(senha, TAM_STR);
	return entrar(utilizadores, nome_usuario, senha);
}

void opcao_adicionar_ponto(Localidade *localidade) {
	int ponto;
	while (true) {
		printf ("Digite o ponto a ser adicionado: ");
		scanf("%d", &ponto);
		if (ponto > 0)
			break;
		else
			printf ("Erro: ponto deve ser maior que zero\n");	
	}

	adicionarPonto(localidade, ponto);
}


void opcao_remover_ponto(Localidade *localidade) {
	int ponto;
	while (true) {
		printf("Digite o ponto a ser removido: ");
		scanf ("%d", &ponto);
		if (ponto > 0)
			break;
		else
			printf ("Erro: ponto deve ser maior que zero\n");
	}

	removerPonto(localidade, ponto);
}

void opcao_adicionar_rua(Localidade *localidade) {
	int pontoA, pontoB, distancia;

	while (true) {
		printf ("Digite o ponto A, ponto B e a distância [A B distância]: ");
		scanf("%d %d %d", &pontoA, &pontoB, &distancia);
		if (pontoA > 0 && pontoB > 0 && distancia > 0)
			break;
		else
			printf ("Erro: todos os valores devem ser maiores que zero\n");
	}

	adicionarRua(localidade, pontoA, pontoB, distancia);	
}

void opcao_eliminar_rua(Localidade *localidade) {
	int pontoA, pontoB;
	while (true) {
		printf ("Digite o ponto A e o ponto B [A B]: ");
		scanf("%d %d", &pontoA, &pontoB);
		if (pontoA > 0 && pontoB > 0)
			break;
		else
			printf ("Erro: todos os valores devem ser maiores que zero\n");
	}

	removerRua(localidade, pontoA, pontoB);
}


void opcao_actualizar_distancia(Localidade *localidade) {
	int pontoA, pontoB, distancia;

	while (true) {
		printf ("Digite o ponto A, ponto B e a nova distância [A B distância]: ");
		scanf("%d %d %d", &pontoA, &pontoB, &distancia);
		if (pontoA > 0 && pontoB > 0 && distancia > 0)
			break;
		else
			printf ("Erro: todos os valores devem ser maiores que zero\n");
	}

	actualizarDistancia(localidade, pontoA, pontoB, distancia);
}


void opcao_custo_optimo(Localidade *localidade) {
	int pontoA, pontoB;
	while (true) {
		printf ("Digite o ponto A e o ponto B [A B]: ");
		scanf("%d %d", &pontoA, &pontoB);
		if (pontoA > 0 && pontoB > 0)
			break;
		else
			printf ("Erro: todos os valores devem ser maiores que zero\n");
	}
	int custo = menorDistanciaAB(localidade, pontoA, pontoB);
	printf ("Custo óptimo entre %d e %d: %d m = %d kz\n", pontoA, pontoB, custo, custo * CUSTO_POR_METRO);
}