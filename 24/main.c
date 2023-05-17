#include "mytree.h"

int main(){
    stack st = new_stack();
    stack result = new_stack();
    Node* n = create_node(0, 1, -1);
    char symb;
    printf("Введите выражение:\n");
    scanf("%c", &symb);
    while (symb != '\n'){
        if (symb >= '0' && symb <= '9') {
            if (n->type == 1 || n->type == 3) 
                n->val = n->val * 10 + (symb - '0');
            else{
                stack_push(&st, &result, n);
                n = create_node(1, symb - '0', -1);
            }
        }
        else if (symb == '(') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else
                stack_push(&st, &result, n);
            n = create_node(0, 1, -1);
        }
        else if (symb == ')') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else
                stack_push(&st, &result, n);
            n = create_node(0, -1, -1);
        }
        else if (symb == '-') {
            if (n->type == 1 || n->type == 3) {
                push(&result, n);
                n = create_node(2, 0, 1);
            }
            else if (n->type == 0 && n->val != 1) {
                stack_push(&st, &result, n);
                n = create_node(2, 0, 1);
            }
            else {
                stack_push(&st, &result, n);
                push(&result, create_node(1, -1, -1));
                n = create_node (2, 2, 2);
            }
        }
        else if (symb == '+') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else
                stack_push(&st, &result, n);
            n = create_node(2, 1, 1);
        }
        else if (symb == '*') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else
                stack_push(&st, &result, n);
            n = create_node(2, 2, 2);
        }
        else if (symb == '/') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else   
                stack_push(&st, &result, n);
            n = create_node(2, 3, 3);
        }
        else if (symb == '^') {
            if (n->type == 1 || n->type == 3)
                push(&result, n);
            else
                stack_push(&st, &result, n);
            n = create_node(2, 4, 4);
        }
        else if ((symb >= 'a' && symb <= 'z') || (symb >= 'A' && symb <= 'Z')) {
            if (n->type == 1 || n->type == 3){
                push (&result, n);
                stack_push(&st, &result, create_node(2, 2, 2));
                n = create_node(3, -1, -1);
                n->ch = symb;
            }
            else {
                stack_push(&st, &result, n);
                n = create_node(3, -1, -1);
                n->ch = symb;
            }
        }
        scanf("%c", &symb);
    }
    if (n->type == 1 || n->type == 3)
        push(&result, n);
    else
        stack_push(&st, &result, n);
    stack_push(&st, &result, create_node(0, -1, -1));
    tree tree_ = new_tree();
    build (&tree_, &result);
    printf("Дерево исходного выражения:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");
    transform(&tree_);
    printf("Преобразованное выражение:\n");
    print_infix(&tree_);
    printf("\n");
    printf("Дерево преобразованного выражения:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");
    free_tree(&tree_);
    return 0;
}