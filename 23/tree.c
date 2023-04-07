#include <stdio.h>
#include <stdlib.h>
#include "mytree.h"

int check_tree(Tree* root) {
    if (root == NULL) {
        return 0;
    }
    
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) {
        return 1;
    }
    
    return check_tree(root->left) || check_tree(root->right);
}//рекурсивная проверка каждой вершины дерева

int main() {
    Tree* root = NULL;
    int value;
    int choice = 0;

    while (1) {
    	printf("1. Добавить вершину?\n");
        printf("2. Удалить вершину?\n");
        printf("3. Распечатать дерево?\n");
        printf("4. Проверить является ли дерево В-деревом?\n");
        printf("5. Закончить работу программы?\n");

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Вы выбрали команду: Добавить вершину\n");
                printf("Введите значение элемента: ");
        		scanf("%d", &value);
       	 		root = insert(root, value);
                break;
            case 2:
                printf("Вы выбрали команду: Удалить вершину\n");
                printf("Введите значение элемента для удаления: ");
        		scanf("%d", &value);
        		root = remove_Tree(root, value);
                break;
            case 3:
                printf("Вы выбрали команду: Распечатать дерево\n");
                printf("\nБинарное дерево: ");
    			printf("\n----------------------------------------\n");
    			print_tree(root, 1);
    			printf("\n----------------------------------------\n");
                break;
            case 4:
                printf("Вы выбрали команду: Проверить является ли дерево В-деревом\n");
                if (check_tree(root)) {
        			printf("\nБинарное дереве не является В-деревом.\n");
    			} else {
        			printf("\nБинарное дереве является В-деревом.\n");
    			}
                break;
            case 5:
                printf("Вы выбрали команду: Закончить работу программы\n");
                free_tree(root);
    			return 0;
                break;
            default:
                printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                break;
        }
    }
    free_tree(root);
    
    return 0;
}
