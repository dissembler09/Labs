#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* create_list () {
    List *l = (List*)malloc(sizeof(List));
    l->head = NULL;
    l->sorted = 0;
    l->size = 0;
    return l;
}

void read_table(List* l, FILE* fp) {
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char* key_str = strtok(line, " \t");
        char* value_str = strtok(NULL, "\n");
        char* key = (char*)malloc(7 * sizeof(char));
        strncpy(key, key_str, 6);
        key[6] = '\0';
        char* value = (char*)malloc((strlen(value_str)+1) * sizeof(char));
        strcpy(value, value_str);

        Node* new_node = (Node*)malloc(sizeof(Node));

        if (!key || !value || !new_node) {
            printf("Memory allocation error!\n");
            exit(1);
        }        

        strcpy(new_node->key, key);
        new_node->data = value;
        new_node->next = NULL;

        if (l->head == NULL) {
            new_node->prev = NULL;
            l->head = new_node;
        }
        else {
            Node* current = l->head;
            while (current->next != NULL) {
                current = current->next;
            }
            new_node->prev = current;
            current->next = new_node;
        }

        l->size++;
        free(key);
    }
}

void add_to_list(List* l, const char* key, const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->key, key);
    new_node->data = strdup(data);
    new_node->next = NULL;

    if (l->head == NULL) {
        new_node->prev = NULL;
        l->head = new_node;
    }
    else {
        Node* current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        new_node->prev = current;
        current->next = new_node;
    }

    l->size++;
}


void table_pop(List* l) {
    if (l->head == NULL) {
        return;
    }
    
    Node* current = l->head;
    while (current->next != NULL) {
        current = current->next;
    }

    if (current->prev == NULL) {
        l->head = NULL;
    } else {
        current->prev->next = NULL;
    }

    free(current->data);
    free(current);
    l->size--;
}

void table_print(List* l) {
    printf("\n");
    if (l->size == 0) {
        printf("List is empty\n");
        return;
    }
    Node* n = begin_list(l);
    for (int i = 0; i < l->size; i++) {
        printf("%s::%s\n", n->key, n->data);
        n = n->next;
    }
    printf("\n");
}

void free_List(List* l) {
    Node* current = l->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(l);
}
int list_size (List* l) {
    return l->size;
}

Node* begin_list(List* l) {
    if (!l || !l->head) {
        return NULL;
    }
    return l->head;
}

Node* plus(Node* n, int x) {
    for (int i = 0; i < x; i++) {
        n = n->next;
    }
    return n;
}

void swap (List* l, int x, int y) {
    Node* n_x = begin_list(l);
    n_x = plus(n_x, x);
    Node* n_y = begin_list(l);
    n_y = plus(n_y, y);

    char key[7];
    char* data;

    strncpy(key, n_x->key, 6);
    key[6] = '\0';
    data = n_x->data;

    strncpy(n_x->key, n_y->key, 6);
    n_x->key[6] = '\0';
    n_x->data = n_y->data;

    strncpy(n_y->key, key, 6);
    n_y->key[6] = '\0';
    n_y->data = data;
}

int compare_keys(char* key1, char* key2) {
    return strncmp(key1, key2, 6);
}

Node* find(List* l, int position) {
    Node* a = begin_list(l);
    for (int i = 0; i<position; i++){
        a = a->next;
    }
    return a;
}

void ShakerSort(List* l) {
    int left = 0;
    int right = l->size-1; 
    int flag = 1;
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; i++) {
            if (compare_keys(find(l, i)->key, find(l, i+1)->key) > 0) {             
                swap(l, i, i+1);
                flag = 1;     
            }
        }
        right--;
        for (int i = right; i>left; i--) {
            if (compare_keys(find(l, i-1)->key, find(l, i)->key) > 0) {            
                swap(l, i-1, i);
                flag = 1;
            }
        }
        left++;
    }
}

char* binary_search(List* lst, char key[7]) {
    if (!lst || !lst->head) {
        printf("List is empty!");
        return NULL;
    }

    Node* left = lst->head;
    Node* right = left;

    while (right->next && strcmp(right->key, key) < 0) {
        left = right;
        right = right->next;
    }

    if (!strcmp(right->key, key)) {
        return right->data;
    }

    return NULL;
}

void reverse_list(List* l) {
    Node* current = l->head;
    Node* temp = NULL;
    
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (temp != NULL) {
        l->head = temp->prev;
    }
}

void write_list(FILE* fp, List* l) {
    Node* current = l->head;
    while (current) {
        fprintf(fp, "%s\t%s\n", current->key, current->data);
        current = current->next;
    }
}

bool is_list_sorted(List* l, bool asc_order) {
  if (l == NULL || l->size == 0) {
    return true;
  }
  
  Node* current = l->head;
  int compare_result = strcmp(current->key, current->next->key);

  if (asc_order) {
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result > 0) {
        return false;
      }
    }
  } else { // для порядка убывания
    for (; current->next != NULL; current = current->next) {
      compare_result = strcmp(current->key, current->next->key);
      if (compare_result < 0) { // знак сравнения меняем на обратный
        return false;
      }
    }
  }
  return true;
}
