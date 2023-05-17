#include "mytree.h"

stack new_stack() {
    stack a;
    a.head = NULL;
    return a;
}

Node* create_node(int type, int val, int rang) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = type;
    n->val = val;
    n->rang = rang;
    n->l = NULL;
    n->r = NULL;
    return n;
}

tree new_tree() {
    tree a;
    a.root = NULL;
    return a;
}

void push(stack* n, Node* a) {
    if (n->head == NULL){
        n->head = a;
        return;
    }
    a->l = n->head;
    n->head = a;
}

Node* delet(stack* n) { //удаление и взятие вершины стека
    Node* t = n->head;
    if (n->head == NULL)
        return NULL;
    if (n->head->l == NULL) {
        n->head = NULL;
        t->l = NULL;
        t->r = NULL;
        return t;
    }
    n->head = t->l;
    t->l = NULL;
    t->r = NULL;
    return t;
}

void stack_push(stack* st, stack* res, Node* n) {
    if (n->type == 0){
        if (n->val == 1) {
            push (st, n);
        } else {
            Node * t = delet(st);
            while (t->type != 0 || t->val != 1) {
                push (res, t);
                t = delet(st);
            }
            free(t);
            free(n);
        }
    }
    else if (n->type == 2) {
        Node * t = delet(st);
        while (t != NULL && n->rang <= t->rang) {
            push(res, t);
            t = delet(st);
        }
        if (t != NULL) 
            push(st, t);
        push(st, n);
    } else {
        push(res, n);
    }
}

Node* add(Node* n, stack* s) {
    if (n->type == 1 || n->type == 3)
        return n;
    Node * t = n;
    t->l = add(delet(s), s);
    t->r = add(delet(s), s);
    return t;
}

void build(tree* t, stack* s) {//строим дерево по стеку
    t->root = delet(s);
    t->root->l = add(delet(s), s);
    t->root->r = add(delet(s), s);
}

void decoding(Node * n) {
    if (n->type == 2) {
        if (n->val == 0) printf("-");
        else if (n->val == 1) printf("+");
        else if (n->val == 2) printf("*");
        else if (n->val == 3) printf("/");
        else printf("^");
    }
    else if (n->type == 3) printf ("%c",n->ch);
    else if (n->type == 1) printf ("%d",n->val);
}

void print_tree(Node* root, int n) {//форматированный вывод дерева
    if (root == NULL) {
        return;
    }
    print_tree(root->r, n + 1);
    for (int i = 0; i < n; i++) printf("\t");
    decoding(root);
    printf("\n");
    print_tree(root->l, n + 1);
}

Node* copy(Node* a){
    Node* n = create_node(a->type, a->val, a->rang);
    n->ch = a->ch;
    if (a->l != NULL)
        n->l = copy(a->l);
    if (a->r != NULL)
        n->r = copy(a->r);
    return n;
    
}

bool solving(Node* n) {
    if (n->type == 2 && n->val == 4 && n->l->type == 2 && n->l->val == 0){
        Node* a = n->r;
        Node* b = n->l->l;
        Node* c = n->l->r;
        Node* a2 = copy(a);
        n->val = 3;
        n->rang = 2;
        n->l->val = 4;
        n->l->rang = 4;
        n->r = create_node(2, 4, 4);
        n->r->r = a2;
        n->r->l = c;
        n->l->r = a;
        n->l->l = b;
        return 1;
    }
    bool p = false;
    bool q = false;
    if (n->l != NULL) 
        p = solving(n->l);
    if (n->r != NULL)
        q = solving(n->r);
    if (p || q)
        return 1;
    else
        return 0;
}

void transform(tree* t) {//преобразование выражения
    while (t->root != NULL && solving(t->root));
}

void print_node(Node* n, int l, int r) { //печать узла
    if (n->type == 1 || n->type == 3){
        for (int i = 0; i < l; i++)
            printf("(");
        if (n->type == 1)
            printf("%d", n->val);
        else
            printf("%c", n->ch);
        for (int i = 0; i < r; i++)
            printf(")");
        return;
    }
    if (n->r->type == 2 && n->r->rang < n->rang)
        print_node(n->r, l + 1, 1);
    else if (n->r->type == 1 || n->r->type == 3)
        print_node(n->r, l, 0);
    else
        print_node(n->r, l, 0);
    decoding(n);
    if (n->l->type == 2 && n->l->rang < n->rang)
        print_node(n->l, 1, r + 1);
    else if (n->l->type == 1 || n->l->type == 3)
        print_node(n->l, 0, r);
    else
        print_node(n->l, 0, r);
}

void print_infix(tree* t) { //печать выражения в обычном виде
    print_node(t->root, 0, 0);
    printf("\n");
}

void free_node(Node* n) {
    if (n->l != NULL)
        free_node(n->l);
    if (n->r != NULL)
        free_node(n->r);
    free(n);
}

void free_tree(tree* tr) {
    free_node(tr->root);
    tr->root = NULL;
}