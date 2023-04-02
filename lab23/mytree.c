#include "mytree.h"

#include <stdio.h>

Tree* create_Tree(int value) {
    Tree* new_Tree = (Tree*)malloc(sizeof(Tree));
    new_Tree->value = value;
    new_Tree->left = NULL;
    new_Tree->right = NULL;
    return new_Tree;
}//функция создания нового узла

Tree* insert(Tree* root, int value) {
	if(root == NULL) 
		return create_Tree(value);
    	if(value < root->value)
    		root->left = insert(root->left, value);
    	else if(value > root->value)
    		root->right = insert(root->right, value);
    return root;
}//функция вставки новой вершины: если элемент меньше корневого - влево, если больше - вправо.


Tree* remove_Tree(Tree* root, int key) {//функция удаления вершины
    if (root == NULL)
    	return root;

    if (key < root->value)
        root->left = remove_Tree(root->left, key);

    else if (key > root->value)
        root->right = remove_Tree(root->right, key);

    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }

        Tree* temp = create_Tree(root->right->value);

        while (temp->left != NULL)
            temp = temp->left;

        root->value = temp->value;
        root->right = remove_Tree(root->right, temp->value);
    }
    return root;
}

void print_tree(Tree* root, int n) {//форматированный вывод дерева
    if (root == NULL) {
        return;
    }
    print_tree(root->right, n + 1);
    for (int i = 0; i < n; i++) printf("\t");
    printf("%d\n", root->value);
    print_tree(root->left, n + 1);
}

void free_tree(Tree* root) {
    if(root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
