#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "localidade.h"
#include "utilizadores.h"
#include "utils.h"
#define  MAX 50
void menu_iniciar(HashTable *tabela,Localidade *localidade)
{int opcao;
    printf("[1]-Criar localidade      \n");
    printf("[2]-Cadastrar utilizador  \n");
    printf("[3]-Alterar senha         \n");
    printf("[4]-Remover utilizador    \n");
    printf("[5]-Simulação             \n");
    printf("[0]-Sair                  \n");
    scanf("%d\n",& opcao);

    switch (opcao)
    { case 1:
     int pontos,ruas;
     printf("digite os numero pontos:\n ");
     scanf("%d\n",& pontos);
     printf("digite os numero ruas:\n ");
     scanf("%d\n",& ruas);
     criarLocalidade(pontos,ruas);
      break;

      case 2:
      char nome_usuario[MAX],senha[MAX];
     printf("Digite o nome do usuario:\n ");
     scanf("%s",& nome_usuario);
     printf("digite a senha:\n ");
     scanf("%s",& senha);
     inserirUsuario(tabela,nome_usuario,senha);
      break;

     case 3:
     char nome_usuario[MAX],senha_nova[MAX],senha_antiga[MAX];
    printf("Digite o nome do usuario:\n ");
     scanf("%s",& nome_usuario);
     printf("digite a senha antiga:\n ");
     scanf("%s",& senha_antiga);
     printf("digite a senha nova:\n ");
     scanf("%s",& senha_nova);
     atualizarSenhaUsuario(tabela,nome_usuario,senha_antiga,senha_nova);
      break;

     case 4:
     char nome_usuario[MAX],senha[MAX];
     printf("Digite o nome do usuario:\n ");
     scanf("%s",& nome_usuario);
     printf("digite a senha:\n ");
     scanf("%s",& senha);
     removerUsuario(tabela,nome_usuario,senha);
      break;

        case 5:
         int opcao_2;
       printf("[1]-Adicionar Ponto   \n");
       printf("[2]-Remover Ponto     \n");
       printf("[3]-Adicionar rua      \n");
       printf("[4]-Eliminar  rua      \n");
       printf("[5]-Actualizar distancia               \n");
       printf("[6]-Imprimir todas as ligacoes e custo \n");
       printf("[7]-Imprimir ligações optimizadas      \n"); 
       printf("[8]-Custo optimo entre dois pontos     \n");
       printf("[9]-Destruir simulacao      \n");
        scanf("%d\n",&opcao_2);
        switch (opcao_2)
        { 
             //adicionar ponto
            case 1:
            int pontoA,pontoB,distancia;
            printf("digite o ponto A:\n ");
            scanf("%d",& pontoA);
             printf("digite o ponto B:\n ");
            scanf("%d",& pontoB);
            printf("digite a distancia:\n ");
            scanf("%d",& distancia);
            adicionarPonto(localidade,pontoA,pontoB,distancia);
            break;

            //remover ponto
             case 2:
              int ponto;
              printf("Digite o ponto:\n ");
              scanf("%d",& ponto);
              removerPonto(localidade,ponto);
            break;

            //adicionar rua 
             case 3:
             int pontoA,pontoB,distancia;
             printf("digite o ponto A:\n ");
             scanf("%d",& pontoA);
             printf("digite o ponto B:\n ");
             scanf("%d",& pontoB);
             printf("digite a distancia:\n ");
             scanf("%d",& distancia);
             adicionarRua(localidade,pontoA,pontoB,distancia);
            break;

            //remover rua 
             case 4:
             int pontoA,pontoB;
             printf("digite o ponto A:\n ");
             scanf("%d",& pontoA);
             printf("digite o ponto B:\n ");
             scanf("%d",& pontoB);
             removerRua(localidade,pontoA,pontoB);
            break;

            //Actualizar distancia
             case 5:
             int pontoA,pontoB,novaDistancia;
             printf("digite o ponto A:\n ");
             scanf("%d",& pontoA);
             printf("digite o ponto B:\n ");
             scanf("%d",& pontoB);
             printf("digite a nova distancia:\n ");
             scanf("%d",& novaDistancia);
             actualizarDistancia(localidade,pontoA,pontoB,novaDistancia);
            break;

            //Imprimir todas ligações e custo
             case 6:
             imprimirLigacoes(localidade);
            break;

            // Imprimir ligações otimizadas
             case 7:
             imprimirLigacoesOtimizadas(localidade);
             break;

            //Custo optimo entre dois pontos
             case 8:
            int pontoA,pontoB;
             printf("digite o ponto A:\n ");
             scanf("%d",& pontoA);
             printf("digite o ponto B:\n ");
             scanf("%d",& pontoB);
             menorDistanciaAB(localidade,pontoA,pontoB);
            break;

            //destruir simulador 
             case 9:
            destruirSimulacao(localidade);
            break;
            
            default:
            printf("digite novamente o numero\n");

        }

      break;

        case 0:
       break;

       default:
       printf("digite novamente o numero\n");

    }


}