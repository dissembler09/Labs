#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 24

typedef struct _node {
    char key[7];
    char* data;
    struct _node* next;
    struct _node* prev;
}Node;

typedef struct list {
    Node* head;
    int sorted;
    int size;
}List;

List* create_list ();
void add_to_list(List* list, const char* key, const char* data);
void table_print (List* l);
int list_size (List* l);
void table_pop (List* l);
void free_List (List* l);
Node* begin_list(List* l);
Node* plus(Node* it, int x);
int compare_keys(char* key1, char* key2);
Node* find(List* l, int position);
void swap (List* l, int x, int y);
void ShakerSort(List* l);
char* binary_search(List* lst, char key[7]);
void read_table(List* list, FILE* fp);
void write_list(FILE* fp, List* l);
bool is_list_sorted(List* l, bool asc_order);
void reverse_list(List* l);