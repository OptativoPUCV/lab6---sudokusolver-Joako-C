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
    // Verificar filas
    for (int row = 0; row < 9; row++) {
        int seen[10] = {0}; // Inicializar un arreglo para verificar números vistos
        for (int col = 0; col < 9; col++) {
            int num = n->sudo[row][col];
            if (num != 0) {
                if (seen[num] == 1) {
                    return 0; // Número repetido en la fila
                }
                seen[num] = 1;
            }
        }
    }

    // Verificar columnas
    for (int col = 0; col < 9; col++) {
        int seen[10] = {0}; // Inicializar un arreglo para verificar números vistos
        for (int row = 0; row < 9; row++) {
            int num = n->sudo[row][col];
            if (num != 0) {
                if (seen[num] == 1) {
                    return 0; // Número repetido en la columna
                }
                seen[num] = 1;
            }
        }
    }

    // Verificar submatrices de 3x3
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            int seen[10] = {0}; // Inicializar un arreglo para verificar números vistos
            for (int row = i; row < i + 3; row++) {
                for (int col = j; col < j + 3; col++) {
                    int num = n->sudo[row][col];
                    if (num != 0) {
                        if (seen[num] == 1) {
                            return 0; // Número repetido en la submatriz
                        }
                        seen[num] = 1;
                    }
                }
            }
        }
    }

    return 1; // El estado es válido
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