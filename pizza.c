#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/pizza.h"
#include "header/ingrediente.h"

Pizza *pizzas = NULL;
int numPizzas = 0;

void adicionarPizza() {
    pizzas = realloc(pizzas, (numPizzas + 1) * sizeof(pizzas));
    if (!pizzas) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    printf("ID da pizza: ");
    scanf("%d", &pizzas[numPizzas].id);
    printf("Nome da pizza: ");
    scanf(" %[^\n]", pizzas[numPizzas].nome);
    printf("Tamanho (P/M/G): ");
    scanf(" %c", &pizzas[numPizzas].tamanho);
    printf("Preço base: ");
    scanf("%f", &pizzas[numPizzas].preco);

    printf("Quantos ingredientes padrão? ");
    scanf("%d", &pizzas[numPizzas].numIngredientes);

    pizzas[numPizzas].ingredientes = malloc(pizzas[numPizzas].numIngredientes * sizeof(Ingrediente));
    if (!pizzas[numPizzas].ingredientes) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < pizzas[numPizzas].numIngredientes; i++) {
        printf("ID do ingrediente %d: ", i + 1);
        scanf("%d", &pizzas[numPizzas].ingredientes[i].id);
        printf("Nome do ingrediente: ");
        scanf(" %[^\n]", pizzas[numPizzas].ingredientes[i].nome);
        printf("Preço do ingrediente: ");
        scanf("%f", &pizzas[numPizzas].ingredientes[i].preco);
    }

    numPizzas++;
    printf("Pizza adicionada com sucesso!\n");
}

void listarPizzas() {
    if (numPizzas == 0) {
        printf("Nenhuma pizza cadastrada.\n");
        return;
    }

    printf("\n--- Cardápio de Pizzas ---\n");
    for (int i = 0; i < numPizzas; i++) {
        printf("ID: %d | Nome: %s | Tamanho: %c | Preço Base: %.2f\n",
               pizzas[i].id, pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco);
        printf("Ingredientes:\n");
        for (int j = 0; j < pizzas[i].numIngredientes; j++) {
            printf("  - %s (%.2f)\n",
                   pizzas[i].ingredientes[j].nome, pizzas[i].ingredientes[j].preco);
        }
    }
}

void editarPizza() {
    int id, encontrado = 0;
    printf("Informe o ID da pizza a ser editada: ");
    scanf("%d", &id);

    for (int i = 0; i < numPizzas; i++) {
        if (pizzas[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", pizzas[i].nome);
            printf("Novo tamanho (P/M/G): ");
            scanf(" %c", &pizzas[i].tamanho);
            printf("Novo preço base: ");
            scanf("%f", &pizzas[i].preco);
            printf("Pizza atualizada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pizza não encontrada.\n");
    }
}

void removerPizza() {
    int id, encontrado = 0;
    printf("Informe o ID da pizza a ser removida: ");
    scanf("%d", &id);

    for (int i = 0; i < numPizzas; i++) {
        if (pizzas[i].id == id) {
            free(pizzas[i].ingredientes);
            for (int j = i; j < numPizzas - 1; j++) {
                pizzas[j] = pizzas[j + 1];
            }
            pizzas = realloc(pizzas, (numPizzas - 1) * sizeof(Pizza));
            numPizzas--;
            encontrado = 1;
            printf("Pizza removida com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Pizza não encontrada.\n");
    }
}

void venderPizza() {
    if (numPizzas == 0) {
        printf("Nenhuma pizza disponível para venda.\n");
        return;
    }

    int id, encontrado = 0;
    printf("Informe o ID da pizza que deseja vender: ");
    scanf("%d", &id);

    for (int i = 0; i < numPizzas; i++) {
        if (pizzas[i].id == id) {
            float precoFinal = pizzas[i].preco;
            int opcao;

            printf("Pizza selecionada: %s (Tamanho: %c, Preço Base: %.2f)\n",
                   pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco);
            printf("Deseja adicionar ingredientes extras? (1-Sim / 0-Não): ");
            scanf("%d", &opcao);

            while (opcao == 1) {
                
                Ingrediente extra;
                printf("ID do ingrediente extra: ");
                scanf("%d", &extra.id);
                printf("Nome do ingrediente extra: ");
                scanf(" %[^\n]", extra.nome);
                printf("Preço do ingrediente extra: ");
                scanf("%f", &extra.preco);

                precoFinal += extra.preco;
                printf("Deseja adicionar outro ingrediente? (1-Sim / 0-Não): ");
                scanf("%d", &opcao);
                
               

            }

            printf("Venda concluída! Preço final da pizza: %.2f\n", precoFinal);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pizza não encontrada.\n");
    }
}
