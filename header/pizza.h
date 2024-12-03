#ifndef PIZZA_H
#define PIZZA_H

#include "ingrediente.h"

typedef struct Pizza{
    int id;
    char nome[50];
    char tamanho; 
    float preco;
    int numIngredientes;
    Ingrediente *ingredientes; 
} Pizza;

void adicionarPizza();
void listarPizzas();
void editarPizza();
void removerPizza();
void venderPizza();

#endif
