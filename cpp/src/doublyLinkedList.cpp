#include <iostream>
#include <string>
#include <fstream>
#include "doublyLinkedList.h"

using namespace std;

bool isEmpty(DLList* ls){
    return ls->nil->next == ls->nil;
}

int find_index(DLList *ls, const string &key){
    DLLNode *current = ls->nil->next;
    int index = 0;
    while (current != ls->nil and current->val != key){
        current = current->next;
        ++index;
    }
    if (current != ls->nil) return index;
    return -1;
}

DLLNode* search_key(DLList *ls, const string &key){
    DLLNode *current = ls->nil->next;
    while (current != ls->nil and current->val != key){
        current = current->next;
    }
    if (current != ls->nil) return current;
    return nullptr;
}

DLLNode* search_index(DLList *ls, int index){
    if (index >= ls->size or index < 0) return nullptr;
    int count = 0;
    DLLNode *current = ls->nil->next;
    while (count != index){
        current = current->next;
        count++;
    }
    return current;
}

void push_front(DLList *ls, const string &key){
    DLLNode *newNode = new DLLNode;
    newNode->val = key;
    newNode->next = ls->nil->next;
    newNode->prev = ls->nil;
    ls->nil->next->prev = newNode;
    ls->nil->next = newNode;
    ls->size++;
}

void push_back(DLList *ls, const string &key){
    DLLNode *newNode = new DLLNode;
    newNode->val = key;
    newNode->next = ls->nil;
    newNode->prev = ls->nil->prev;
    ls->nil->prev->next = newNode;
    ls->nil->prev = newNode;
    ls->size++;
}

void pop_back(DLList *ls){
    if (isEmpty(ls)) return;
    DLLNode *temp = ls->nil->prev;
    temp->prev->next = ls->nil;
    ls->nil->prev = temp->prev;
    delete temp;
    ls->size--;
}

void pop_front(DLList *ls){
    if (isEmpty(ls)) return;
    DLLNode *temp = ls->nil->next;
    temp->next->prev = ls->nil;
    ls->nil->next = temp->next;
    delete temp;
    ls->size--;
}

void insert_after(DLList *ls, int index, const string &key){
    if (index < 0 or index > ls->size-1) return;
    DLLNode *current = search_index(ls, index);
    DLLNode *newNode = new DLLNode;
    newNode->val = key;
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    ls->size++;
}

void insert_before(DLList *ls, int index, const string &key){
    if (index < 0 or index > ls->size - 1) return;
    DLLNode *current = search_index(ls, index);
    DLLNode *newNode = new DLLNode;
    newNode->val = key;
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    ls->size++;
}

void remove(DLLNode* delNode){
    if (delNode == nullptr) return;
    delNode->prev->next = delNode->next;
    delNode->next->prev = delNode->prev;
    delete delNode;
}

void remove_key(DLList *ls, const string &key){
    DLLNode *delNode = search_key(ls, key);
    if (delNode != nullptr) {
        remove(delNode);
        ls->size--;
    }
}

void remove_after(DLList *ls, int index){
    if (index >= 0 and index < ls->size - 1) {
        remove(search_index(ls, index + 1));
        ls->size--;
    }
}

void remove_before(DLList *ls, int index){
    if (index > 0 and index < ls->size) {
        remove(search_index(ls, index - 1));
        ls->size--;
    }
}

void print(DLList *ls){
    DLLNode *current = ls->nil->next;
    while (current != ls->nil){
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;
}

void reverse_print(DLList *ls){
    DLLNode *current = ls->nil->prev;
    while (current != ls->nil){
        cout << current->val << " ";
        current = current->prev;
    }
    cout << endl;
}

void saveToFile(DLList *ls, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    DLLNode *current = ls->nil->next;
    while (current != ls->nil) {
        file << current->val << endl;
        current = current->next;
    }
    
    file.close();
}

void loadFromFile(DLList *ls, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    clear(ls);
    string line;
    while (getline(file, line)) {
        push_back(ls, line);
    }
    
    file.close();
}

void clear(DLList *ls) {
    while (!isEmpty(ls)) {
        pop_front(ls);
    }
}