#include <iostream>
#include <string>
#include <fstream>
#include "forwardList.h"

using namespace std;

ostream& operator<<(ostream& os, const FList* list) {
    FLNode* current = list->head;
    while (current != nullptr) {
        os << current->val << ' ';
        current = current->next;
    }
    return os;
}

int searchKey(FList *ls, const string &key){
    FLNode *current = ls->head;
    int index = 0;
    while (current != nullptr and current->val != key)
    {
        current = current->next;
        ++index;
    }
    if (current == nullptr) return -1;
    return index;
}

FLNode* searchIndex(FList *ls, int index){
    if (index >= ls->size or index < 0) return nullptr;
    int count = 0;
    FLNode *current = ls->head;
    while (count != index){
        current = current->next;
        count++;
    }
    return current;
}

void insert(FLNode* prev, const string &key){
    FLNode *newNode = new FLNode;
    newNode->val = key;
    newNode->next = prev->next;
    prev->next = newNode;
}

void push_front(FList *ls, const string &key){
    FLNode* newNode = new FLNode;
    newNode->val = key;
    if (ls->head != nullptr){
        newNode->next = ls->head;
    }
    ls->head = newNode;
    ls->size++;
}

void push_back(FList *ls, const string &key){
    if (ls->size == 0) push_front(ls, key);
    else{
        insert(searchIndex(ls, ls->size - 1), key);
        ls->size++;
    }
}

void insert_after(FList* ls, int index, const string &key){
    if (index < 0 or index > ls->size-1) return;
    if (index == ls->size - 1) push_back(ls, key); 
    else {
        FLNode *prev = searchIndex(ls, index);
        insert(prev, key);
        ls->size++;
    }
}

void insert_before(FList* ls, int index, const string &key){
    if (index < 0 or index > ls->size - 1) return;
    if(index == 0) push_front(ls, key);
    else {
        FLNode *prev = searchIndex(ls, index-1);
        insert(prev, key);
        ls->size++;
    }
}

void pop_front(FList *ls){
    if (ls->size == 0) return;
    FLNode *temp = ls->head;
    ls->head = ls->head->next;
    delete temp;
    ls->size--;
}

void pop_back(FList *ls){
    if (ls->size == 0) return;
    if (ls->size == 1) pop_front(ls);
    else {
        FLNode *prev = searchIndex(ls, ls->size - 2);
        delete prev->next;
        prev->next = nullptr;
    }
    ls->size--;
}

void removeIndex(FList *ls, int index) {
    if (ls->size == 0 || index < 0 || index >= ls->size) return;
    
    if (index == 0) {
        pop_front(ls);
    } else {
        FLNode *prev = searchIndex(ls, index - 1);
        FLNode *temp = prev->next;
        prev->next = temp->next;
        delete temp;
        ls->size--;
    }
}

void remove_before(FList *ls, int index) {
    if (index > 0 and index < ls->size) {
        removeIndex(ls, index - 1);
    }
}

void remove_after(FList *ls, int index) {
    if (index >= 0 and index < ls->size - 1) {
        removeIndex(ls, index + 1);
    }
}

void removeKey(FList *ls, const string &key) {
    int index = 0;
    FLNode *current = ls->head;
    while (current != nullptr && current->val != key) {
        current = current->next;
        index++;
    }    
    if (current != nullptr) {
        removeIndex(ls, index);
    }
}

void print(FList *ls){
    FLNode *current = ls->head;
    while (current != nullptr){
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;
}

void saveToFile(FList *ls, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    // Сохраняем элементы в правильном порядке
    FLNode *current = ls->head;
    while (current != nullptr) {
        file << current->val << endl;
        current = current->next;
    }
    
    file.close();
}

void loadFromFile(FList *ls, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // Файл не существует - это нормально для первого запуска
        return;
    }
    
    clear(ls);
    
    // Читаем строки и добавляем их в конец списка
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            push_back(ls, line);
        }
    }
    
    file.close();
}

void clear(FList *ls) {
    while (ls->size > 0) {
        pop_front(ls);
    }
}