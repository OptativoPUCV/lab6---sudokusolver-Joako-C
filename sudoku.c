#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
    int row_check[9][10] = {0}; // Para verificar números en filas
    int col_check[9][10] = {0}; // Para verificar números en columnas
    int subgrid_check[9][10] = {0}; // Para verificar números en submatrices de 3x3

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int num = n->sudo[row][col];

            if (num < 1 || num > 9) {
                return 0; // Número fuera de rango
            }

            // Verificar fila
            if (row_check[row][num] == 1) {
                return 0; // Número repetido en la fila
            }
            row_check[row][num] = 1;

            // Verificar columna
            if (col_check[col][num] == 1) {
                return 0; // Número repetido en la columna
            }
            col_check[col][num] = 1;

            // Verificar submatriz de 3x3
            int subgrid = (row / 3) * 3 + (col / 3);
            if (subgrid_check[subgrid][num] == 1) {
                return 0; // Número repetido en la submatriz
            }
            subgrid_check[subgrid][num] = 1;
        }
    }

    return 1; // Si pasa todas las verificaciones, el Sudoku es válido
}



List* get_adj_nodes(Node* n) {
  List* list = createList();

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (n->sudo[row][col] == 0) {
        for (int num = 1; num <= 9; num++) {
          Node* adj_node = copy(n);
          adj_node->sudo[row][col] = num;
          pushBack(list, adj_node);
        }
      }
    }
  }
  return list;
}


int is_final(Node* n) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (n->sudo[row][col] == 0) {
        return 0;
      }
    }
  }
  return 1;
}


Node* DFS(Node* initial, int* cont) {
  if (!is_valid(initial)) {
    return NULL;
  }

  if (is_final(initial)) {
    return initial;
  }

  List* adj_nodes = get_adj_nodes(initial);
  
  while (!is_empty(adj_nodes)) {
    Node* adj_node = (Node*)front(adj_nodes);
    popFront(adj_nodes);
    
    Node* result = DFS(adj_node, cont);
    (*cont)++;
    
    if (result != NULL) {
      return result;
    }
  }
  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/