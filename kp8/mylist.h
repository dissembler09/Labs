#ifndef MYLIST
#define MYLIST
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node *next;
} Node; //обозначим структуру на которой будет базироваться список

typedef struct List {
    Node* bar;
    int size;
} List;//структура самого списка

int sizeList(List* list);
Node* createNode(double data);
List* createList();
List* reversed_list(List* list);
void insertList(List* list, double data);
int removeNode(List* list, double data);
void printlist(List *list);
void clearList(List* list);
void removeLastKNodes(List* list, int k);
double get_element(List* list, int index);
void delete_elem_ind(List* list, int index);
void insert_elem_ind(List* list, double value, int index);
#endif
