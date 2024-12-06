#ifndef INGREDIENTE_H
#define INGREDIENTE_H

typedef struct Ingrediente{
    int id;
    char nome[50];
    float preco;
} Ingrediente;

void adicionarIngrediente();
void listarIngredientes();
void editarIngrediente();
void removerIngrediente();
void salvarIngredientes();
void carregarIngredientes();

#endif
