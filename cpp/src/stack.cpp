#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"

using namespace std;

ostream& operator<<(ostream& os, const Stack *s){
    StackNode* current = s->top;
    while (current != nullptr) {
        os << current->val << ' ';
        current = current->next;
    }
    return os;
}

bool isEmpty(Stack *s){
    return s->top == nullptr;
}

void pop(Stack *s){
    if (isEmpty(s)) {
        return;
    }
    StackNode *temp = s->top;
    s->top = s->top->next;
    delete temp;
}

void push(Stack *s, const string &key){
    StackNode *newNode = new StackNode(key);
    newNode->next = s->top;
    s->top = newNode;
}

void saveToFile(Stack *s, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    // Создаем временный стек для реверса
    Stack temp;
    StackNode *current = s->top;
    
    // Копируем элементы в обратном порядке
    while (current != nullptr) {
        StackNode *newNode = new StackNode(current->val);
        newNode->next = temp.top;
        temp.top = newNode;
        current = current->next;
    }
    
    // Сохраняем временный стек (он уже в правильном порядке)
    current = temp.top;
    while (current != nullptr) {
        file << current->val << endl;
        current = current->next;
    }
    
    // Очищаем временный стек
    while (temp.top != nullptr) {
        StackNode *tempNode = temp.top;
        temp.top = temp.top->next;
        delete tempNode;
    }
    
    file.close();
}

void loadFromFile(Stack *s, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // Файл не существует - это нормально для первого запуска
        return;
    }
    
    clear(s);
    
    // Просто читаем и пушим в том порядке, в котором идут строки в файле
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            push(s, line);
        }
    }
    
    file.close();
}

//bool get(Stack* s, const string &key){
//    StackNode* current = s->top;
//    while (current != nullptr){
//        if (current->val == key) return true;
//        current = current->next;
//    }
//    return false;
//}

void clear(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}