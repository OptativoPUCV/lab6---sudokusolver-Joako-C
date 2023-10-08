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
  for (int row = 0; row < 9; row++) {
    int seen[10] = {0};
    for (int col = 0; col < 9; col++) {
      int num = n->sudo[row][col];
      if (num != 0) {
        if (seen[num] == 1) {
          return 0;
        }
        seen[num] = 1;
      }
    }
  }
  
  for (int col = 0; col < 9; col++) {
    int seen[10] = {0};
    for (int row = 0; row < 9; row++) {
      int num = n->sudo[row][col];
      if (num != 0) {
        if (seen[num] == 1) {
          return 0;
        }
        seen[num] = 1;
      }
    }
  }
  
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      int seen[10] = {0};
      for (int row = i; row < i + 3; row++) {
        for (int col = j; col < j + 3; col++) {
          int num = n->sudo[row][col];
          if (num != 0) {
            if (seen[num] == 1) {
              return 0;
            }
            seen[num] = 1;
          }
        }
      }
    }
  }
  return 1;
}



List* get_adj_nodes(Node* n) {
  List* list = createList();
  
  int empty_row = -1;
  int empty_col = -1;
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (n->sudo[row][col] == 0) {
        empty_row = row;
        empty_col = col;
        break;
      }
    }
    if (empty_row != -1) {
      break;
    }
  }

  if (empty_row == -1) {
    return list;
  }

  for (int num = 1; num <= 9; num++) {
    Node* adj_node = copy(n);
    adj_node->sudo[empty_row][empty_col] = num;
    
    if (is_valid(adj_node)) {
      pushBack(list, adj_node);
    } else {
      free(adj_node);
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
  List* stack = createList();
  pushBack(stack, initial);

  while (!is_empty(stack)) {
    Node* current = (Node*)last(stack);
    popBack(stack);

    if (is_final(current)) {
      clean(stack);
      return current;
    }

    int empty_row = -1;
    int empty_col = -1;
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        if (current->sudo[row][col] == 0) {
          empty_row = row;
          empty_col = col;
          break;
        }
      }
      if (empty_row != -1) {
        break;
      }
    }

    if (empty_row != -1) {
      for (int num = 1; num <= 9; num++) {
        Node* adj_node = copy(current);
        adj_node->sudo[empty_row][empty_col] = num;

        if (is_valid(adj_node)) {
          pushBack(stack, adj_node);
        } else {
          free(adj_node);
        }
      }
    }

    (*cont)++;
  }

  return NULL;
}



/*
int main( int argc, char *argv[]) {
  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/