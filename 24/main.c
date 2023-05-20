#include "mytree.h"
#include <ctype.h>

int main(){
    stack st = new_stack();
    stack result = new_stack();
    Node* n = create_node(OPERATOR, 1, -1);
    char symb;
    printf("Введите выражение:\n");
    scanf("%c", &symb);
    while (symb != '\n'){
        if (isdigit(symb)) {
            if (n->type == NUMBER || n->type == VARIABLE) 
                n->val = n->val * 10 + (symb - '0');
            else{
                stack_push(&st, &result, n);
                n = create_node(NUMBER, symb - '0', -1);
            }
        } else if (isalpha(symb)) {
            if (n->type == NUMBER || n->type == VARIABLE){
                push (&result, n);
                stack_push(&st, &result, create_node(SIGN, 2, 2));
                n = create_node(VARIABLE, -1, -1);
                n->ch = symb;
            }
            else {
                stack_push(&st, &result, n);
                n = create_node(VARIABLE, -1, -1);
                n->ch = symb;
            }
        } else {
            switch(symb) {
                case '(':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(OPERATOR, 1, -1);     
                    break;
                case ')':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(OPERATOR, -1, -1);
                    break;
                case '-':
                    if (n->type == NUMBER || n->type == VARIABLE) {
                        push(&result, n);
                        n = create_node(SIGN, 0, 1);
                    } else if (n->type == OPERATOR && n->val != 1) {
                        stack_push(&st, &result, n);
                        n = create_node(SIGN, 0, 1);
                    } else {
                        stack_push(&st, &result, n);
                        push(&result, create_node(NUMBER, -1, -1));
                        n = create_node (SIGN, 2, 2);
                    }
                    break;
                case '+':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, 1, 1);
                    break;
                case '*':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, 2, 2);
                    break;
                case '/':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else   
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, 3, 3);
                    break;
                case '^':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, 4, 4);
                    break;
            }
        }
        scanf("%c", &symb);
    }
    if (n->type == NUMBER || n->type == VARIABLE)
        push(&result, n);
    else
        stack_push(&st, &result, n);
    stack_push(&st, &result, create_node(OPERATOR, -1, -1));
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