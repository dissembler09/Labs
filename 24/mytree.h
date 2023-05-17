#ifndef MYTREE
#define MYTREE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    int type, val, rang;
    /*type - тип узла: "0" - оператор, "1" - число, "2" - знак операции, "3" - переменная;
    val - значение узла - число или ASCII-код переменной;
    rang - приоритет операции;*/
    char ch;
    struct _node *l, *r;//указатели на правый и левый дочерние узлы
}Node;

typedef struct _stack{
    Node* head;
}stack;

typedef struct _tree{
    Node* root;
}tree;

tree new_tree();
stack new_stack();
Node* create_node(int type, int val, int rang);
void push(stack* now, Node* a);
Node* delet(stack* n);
void stack_push(stack* st, stack* res, Node* now);
Node* add (Node* now, stack* s);
void build(tree* t, stack* s);
void decoding(Node * n);
void print_tree(Node* root, int n);
void print_node(Node* n, int l, int r);
Node* copy (Node* a);
bool solving(Node* n);
void transform(tree* t);
void print_infix(tree* t);
void free_node(Node* n);
void free_tree(tree* tr);
#endif