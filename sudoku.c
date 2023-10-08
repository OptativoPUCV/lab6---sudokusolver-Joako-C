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
  int used[10];

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 10; j++) {
      used[j] = 0;
    }
    for (int j = 0; j < 9; j++) {
      int num = n->sudo[i][j];
      if (num < 1 || num > 9 || used[num]) {
        return 0;
      }
      used[num] = 1;
    }
    for (int j = 0; j < 10; j++) {
      used[j] = 0;
    }
    for (int j = 0; j < 9; j++) {
      int num = n->sudo[j][i];
      if (num < 1 || num > 9 || used[num]) {
        return 0;
      }
      used[num] = 1;
    }
  }
  for (int startRow = 0; startRow < 9; startRow += 3) {
    for (int startCol = 0; startCol < 9; startCol += 3) {
      for (int j = 0; j < 10; j++) {
        used[j] = 0;
      }
      for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
          int num = n->sudo[i][j];
          if (num < 1 || num > 9 || used[num]) {
            return 0;
          }
          used[num] = 1;
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n, int row, int col) {
  List* list = createList();

  for (int j = 0; j < 9; j++) {
    if (j != col) {
      Node* adj_node = copy(n);
      adj_node->sudo[row][col] = adj_node->sudo[row][j];
      adj_node->sudo[row][j] = n->sudo[row][col];
      pushBack(list, adj_node); lista
        }
  }
  for (int i = 0; i < 9; i++) {
    if (i != row) {
      Node* adj_node = copy(n);
      adj_node->sudo[row][col] = adj_node->sudo[i][col];
      adj_node->sudo[i][col] = n->sudo[row][col];
      pushBack(list, adj_node);
    }
  }
  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3;
  for (int i = startRow; i < startRow + 3; i++) {
    for (int j = startCol; j < startCol + 3; j++) {
      if (i != row || j != col) {
        Node* adj_node = copy(n);
        adj_node->sudo[row][col] = adj_node->sudo[i][j];
        adj_node->sudo[i][j] = n->sudo[row][col];
        pushBack(list, adj_node);
      }
    }
  }
  return list;
}



int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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