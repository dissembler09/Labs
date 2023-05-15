#ifndef MYLIST
#define MYLIST
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node *next;
} Node; //обозначим структуру на которой будет базироваться список

typedef struct List {
    Node* head;
    int size;
} List;//структура самого списка

int sizeList(List* list);
Node* createNode(double data);
List* createList();
void insertList(List* list, double data);
void removeNode(List* list, double data);
void printlist(List *list);
void clearList(List* list);
void removeLastKNodes(List* list, int k);
#endif
