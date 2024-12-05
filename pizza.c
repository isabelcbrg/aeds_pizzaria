#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#include "ingrediente.h"

Pizza *pizzas = NULL;
int numPizzas = 0;

void adicionarPizza() {
    pizzas = realloc(pizzas, (numPizzas + 1) * sizeof(Pizza));
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

void salvarPizzas() {
    FILE *arquivo = fopen("pizzas.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar pizzas.\n");
        return;
    }

    fprintf(arquivo, "%d\n", numPizzas);
    for (int i = 0; i < numPizzas; i++) {
        fprintf(arquivo, "%d\n%s\n%c\n%.2f\n%d\n",
                pizzas[i].id, pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco, pizzas[i].numIngredientes);
        for (int j = 0; j < pizzas[i].numIngredientes; j++) {
            fprintf(arquivo, "%d\n%s\n%.2f\n",
                    pizzas[i].ingredientes[j].id, pizzas[i].ingredientes[j].nome, pizzas[i].ingredientes[j].preco);
        }
    }

    fclose(arquivo);
    printf("Pizzas salvas com sucesso!\n");
}

void carregarPizzas() {
    FILE *arquivo = fopen("pizzas.txt", "r");
    if (!arquivo) {
        printf("Nenhum arquivo de pizzas encontrado. Começando com lista vazia.\n");
        return;
    }

    fscanf(arquivo, "%d\n", &numPizzas);
    pizzas = malloc(numPizzas * sizeof(Pizza));
    for (int i = 0; i < numPizzas; i++) {
        fscanf(arquivo, "%d\n", &pizzas[i].id);
        fscanf(arquivo, " %[^\n]\n", pizzas[i].nome);
        fscanf(arquivo, " %c\n", &pizzas[i].tamanho);
        fscanf(arquivo, "%f\n", &pizzas[i].preco);
        fscanf(arquivo, "%d\n", &pizzas[i].numIngredientes);

        pizzas[i].ingredientes = malloc(pizzas[i].numIngredientes * sizeof(Ingrediente));
        for (int j = 0; j < pizzas[i].numIngredientes; j++) {
            fscanf(arquivo, "%d\n", &pizzas[i].ingredientes[j].id);
            fscanf(arquivo, " %[^\n]\n", pizzas[i].ingredientes[j].nome);
            fscanf(arquivo, "%f\n", &pizzas[i].ingredientes[j].preco);
        }
    }

    fclose(arquivo);
    printf("Pizzas carregadas com sucesso!\n");
}
