#include "mylist.h"

#include <stdio.h>

int sizeList(List* list) {
    return list->size;
} //является ли стек пустым

//функция создания нового узла списка
Node* createNode(double data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = data;
    newNode->next = NULL;
    return newNode;
}

//функция создания нового списка
List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    newList->bar = createNode(0); //создаем барьерный элемент со значением 0
    newList->size = 0;
    return newList;
}

//функция для вставки нового элемента в список
void insertList(List* list, double data) {
    Node* newNode = createNode(data);
    newNode->next = list->bar->next;
    list->bar->next = newNode;
    list->size++;
}

//функция для удаления элемента из списка
int removeNode(List* list, double data) {
    Node* currentNode = list->bar->next;
    Node* prevNode = list->bar;
    int check = 0;
    while (currentNode != NULL) {
        if (currentNode->value == data) {
            prevNode->next = currentNode->next;
            free(currentNode);
            list->size--;
            check = 1;
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    return check;
}

//функция для печати списка
void printlist(List* list) {
    Node* currentNode = list->bar;
    while (currentNode->next != NULL) {
        printf("%lf ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

double get_element(List* list, int index) {
    Node* current = list->bar;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

List* reversed_list(List* list) {
    List* reversed = (List*)malloc(sizeof(List));
    reversed->bar = NULL;
    reversed->size = 0;
    
    Node* current = list->bar;
    while (current != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->value = current->value;
        newNode->next = reversed->bar;
        reversed->bar = newNode;
        reversed->size++;
        current = current->next;
    }
    
    return reversed;
}

void removeLastKNodes(List* list, int k) {
    if (k >= list->size) return; //если k больше или равен размеру списка, список не 
    Node* current = list->bar;
    Node* previous = NULL;
    int count = 0;
    
    while (current != NULL && count < k) {
        previous = current;
        current = current->next;
        free(previous);
        count++;
    }
    
    list->bar = current;
    list->size -= count;
}

void clearList(List* list) {
    // Очистка памяти для каждого узла списка
    Node* currentNode = list->bar;
    while (currentNode != NULL) {
        Node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }

    // Очистка памяти для списка
    free(list);
} 

void delete_elem_ind(List* list, int index) {
    Node* currentNode = list->bar;
    if (index == 0) {
        list->bar = currentNode->next;
        free(currentNode);
        list->size--;
        return;
    }
    for (int i = 0; i < index - 1; i++) {
        currentNode = currentNode->next;
    }
    Node* nextNode = currentNode->next->next;
    free(currentNode->next);
    currentNode->next = nextNode;
    list->size--;
}

void insert_elem_ind(List* list, double value, int index) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    if (index == 0) {
        newNode->next = list->bar;
        list->bar = newNode;
        list->size++;
        return;
    }
    Node* currentNode = list->bar;
    for (int i = 0; i < index - 1; i++) {
        currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    list->size++;
}

