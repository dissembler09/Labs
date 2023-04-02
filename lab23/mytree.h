#ifndef MYTREE
#define MYTREE
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create_Tree(int value);
Tree* insert(Tree* root, int value);
Tree* remove_Tree(Tree* root, int key);
void print_tree(Tree* root, int n);
void free_tree(Tree* root);
#endif
