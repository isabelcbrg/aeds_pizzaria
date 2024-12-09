#include <stdio.h>
#include <stdlib.h>
#include "pizza.h"
#include "header/ingrediente.h"

// Funções de menu
void menuIngredientes() {

    int opcao;
    do {
        printf("\n--- Menu de Ingredientes ---\n");
        printf("1. Adicionar Ingrediente\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Editar Ingrediente\n");
        printf("4. Remover Ingrediente\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarIngrediente();
                break;
            case 2:
                listarIngredientes();
                break;
            case 3:
                editarIngrediente();
                break;
            case 4:
                removerIngrediente();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menuPizzas() {

    int opcao;
    do {
        printf("\n--- Menu de Pizzas ---\n");
        printf("1. Adicionar Pizza\n");
        printf("2. Listar Pizzas\n");
        printf("3. Editar Pizza\n");
        printf("4. Remover Pizza\n");
        printf("5. Vender Pizza\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarPizza();
                break;
            case 2:
                listarPizzas();
                break;
            case 3:
                editarPizza();
                break;
            case 4:
                removerPizza();
                break;
            case 5:
                venderPizza();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    carregarIngredientes();
    carregarPizzas();

    int opcao;
    do {
        printf("\n=== Sistema da Pizzaria ===\n");
        printf("1. Gerenciar Ingredientes\n");
        printf("2. Gerenciar Pizzas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuIngredientes();
                break;
            case 2:
                menuPizzas();
                break;
            case 0:
                printf("Saindo do sistema. Salvando dados...\n");
                salvarIngredientes(); // Salva os ingredientes no arquivo
                salvarPizzas();       // Salva as pizzas no arquivo
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

