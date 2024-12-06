#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#include "ingrediente.h"

extern Ingrediente *ingredientes;
extern int numIngredientes;

Pizza *pizzas = NULL;
int numPizzas = 0;

void adicionarPizza() {
    pizzas = realloc(pizzas, (numPizzas + 1) * sizeof(Pizza));
    if (!pizzas) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    printf("ID da pizza: ");
    scanf("%d", &pizzas[numPizzas].id);
    printf("Nome da pizza: ");
    scanf(" %[^\n]", pizzas[numPizzas].nome);
    printf("Tamanho (P/M/G): ");
    scanf(" %c", &pizzas[numPizzas].tamanho);
    printf("Preco base: ");
    scanf("%f", &pizzas[numPizzas].preco);

    printf("Quantos ingredientes padrao? ");
    scanf("%d", &pizzas[numPizzas].numIngredientes);

    pizzas[numPizzas].ingredientes = malloc(pizzas[numPizzas].numIngredientes * sizeof(Ingrediente));
    if (!pizzas[numPizzas].ingredientes) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    for (int i = 0; i < pizzas[numPizzas].numIngredientes; i++) {
        int idIngrediente, encontrado = 0;
        printf("ID do ingrediente %d: ", i + 1);
        scanf("%d", &idIngrediente);

        for (int j = 0; j < numIngredientes; j++) {
            if (ingredientes[j].id == idIngrediente) {
                pizzas[numPizzas].ingredientes[i] = ingredientes[j];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Ingrediente nao encontrado. Tente novamente.\n");
            i--;
        }
    }

    numPizzas++;
    printf("Pizza adicionada com sucesso!\n");
}

void listarPizzas() {
    if (numPizzas == 0) {
        printf("Nenhuma pizza cadastrada.\n");
        return;
    }

    printf("\n--- Cardapio de Pizzas ---\n");
    for (int i = 0; i < numPizzas; i++) {
        printf("ID: %d | Nome: %s | Tamanho: %c | Preco Base: %.2f\n",
               pizzas[i].id, pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco);
        printf("Ingredientes:\n");
        for (int j = 0; j < pizzas[i].numIngredientes; j++) {
            printf("  - %s (%.2f)\n",
                   pizzas[i].ingredientes[j].nome, pizzas[i].ingredientes[j].preco);
        }
    }
}

void venderPizza() {
    if (numPizzas == 0) {
        printf("Nenhuma pizza cadastrada.\n");
        return;
    }

    int idPizza, idIngrediente, numExtras;
    Pizza *pizzaSelecionada = NULL;

    printf("\n--- Venda de Pizza ---\n");
    printf("Informe o ID da pizza que deseja vender: ");
    scanf("%d", &idPizza);

    for (int i = 0; i < numPizzas; i++) {
        if (pizzas[i].id == idPizza) {
            pizzaSelecionada = &pizzas[i];
            break;
        }
    }

    if (!pizzaSelecionada) {
        printf("Pizza nao encontrada.\n");
        return;
    }

    printf("Pizza selecionada: %s (Preco Base: %.2f)\n", pizzaSelecionada->nome, pizzaSelecionada->preco);

    printf("Quantos ingredientes adicionais deseja adicionar? ");
    scanf("%d", &numExtras);

    float precoFinal = pizzaSelecionada->preco;
    for (int i = 0; i < numExtras; i++) {
        int encontrado = 0;
        printf("ID do ingrediente adicional %d: ", i + 1);
        scanf("%d", &idIngrediente);

        for (int j = 0; j < numIngredientes; j++) {
            if (ingredientes[j].id == idIngrediente) {
                printf("Ingrediente adicional adicionado: %s (%.2f)\n",
                       ingredientes[j].nome, ingredientes[j].preco);
                precoFinal += ingredientes[j].preco;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Ingrediente nao encontrado. Tente novamente.\n");
            i--;
        }
    }

    printf("Venda registrada com sucesso!\n");
    printf("Preco final da pizza: %.2f\n", precoFinal);
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
        printf("Nenhum arquivo de pizzas encontrado. Comecando com lista vazia.\n");
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
