#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingrediente.h"

Ingrediente *ingredientes = NULL;
int numIngredientes = 0;

void adicionarIngrediente() {
    ingredientes = realloc(ingredientes, (numIngredientes + 1) * sizeof(Ingrediente));
    if (!ingredientes) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    printf("ID do ingrediente: ");
    scanf("%d", &ingredientes[numIngredientes].id);
    printf("Nome do ingrediente: ");
    scanf(" %[^\n]", ingredientes[numIngredientes].nome);
    printf("Preco do ingrediente: ");
    scanf("%f", &ingredientes[numIngredientes].preco);

    numIngredientes++;
    printf("Ingrediente adicionado com sucesso!\n");
}

void listarIngredientes() {
    if (numIngredientes == 0) {
        printf("Nenhum ingrediente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Ingredientes ---\n");
    for (int i = 0; i < numIngredientes; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f\n",
               ingredientes[i].id, ingredientes[i].nome, ingredientes[i].preco);
    }
}

void editarIngrediente() {
    int id, encontrado = 0;
    printf("Informe o ID do ingrediente a ser editado: ");
    scanf("%d", &id);

    for (int i = 0; i < numIngredientes; i++) {
        if (ingredientes[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", ingredientes[i].nome);
            printf("Novo preço: ");
            scanf("%f", &ingredientes[i].preco);
            printf("Ingrediente atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Ingrediente não encontrado.\n");
    }
}

void removerIngrediente() {
    int id, encontrado = 0;
    printf("Informe o ID do ingrediente a ser removido: ");
    scanf("%d", &id);

    for (int i = 0; i < numIngredientes; i++) {
        if (ingredientes[i].id == id) {
            for (int j = i; j < numIngredientes - 1; j++) {
                ingredientes[j] = ingredientes[j + 1];
            }
            ingredientes = realloc(ingredientes, (numIngredientes - 1) * sizeof(Ingrediente));
            numIngredientes--;
            encontrado = 1;
            printf("Ingrediente removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Ingrediente nao encontrado.\n");
    }
}

void salvarIngredientes() {
    FILE *arquivo = fopen("ingredientes.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar ingredientes.\n");
        return;
    }

    fprintf(arquivo, "%d\n", numIngredientes);
    for (int i = 0; i < numIngredientes; i++) {
        fprintf(arquivo, "%d\n%s\n%.2f\n",
                ingredientes[i].id, ingredientes[i].nome, ingredientes[i].preco);
    }

    fclose(arquivo);
    printf("Ingredientes salvos com sucesso!\n");
}

void carregarIngredientes() {
    FILE *arquivo = fopen("ingredientes.txt", "r");
    if (!arquivo) {
        printf("Nenhum arquivo de ingredientes encontrado. Começando com lista vazia.\n");
        return;
    }

    fscanf(arquivo, "%d\n", &numIngredientes);
    ingredientes = malloc(numIngredientes * sizeof(Ingrediente));
    for (int i = 0; i < numIngredientes; i++) {
        fscanf(arquivo, "%d\n", &ingredientes[i].id);
        fscanf(arquivo, " %[^\n]\n", ingredientes[i].nome);
        fscanf(arquivo, "%f\n", &ingredientes[i].preco);
    }

    fclose(arquivo);
    printf("Ingredientes carregados com sucesso!\n");
}
