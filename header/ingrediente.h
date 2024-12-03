#ifndef INGREDIENTE_H
#define INGREDIENTE_H

typedef struct Ingrediente{
    int id;
    char nome[50];
    float preco;
} Ingrediente;

// Funções CRUD para ingredientes
void adicionarIngrediente();
void listarIngredientes();
void editarIngrediente();
void removerIngrediente();

#endif
