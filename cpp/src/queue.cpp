#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"

using namespace std;

ostream &operator<<(ostream &os, const Queue *q){
    Node *current = q->head;
    while (current != nullptr){
        os << current->val << ' ';
        current = current->next;
    }
    return os;
}

bool isEmpty(Queue *q){
    return q->head == nullptr;
}

void enqueue(Queue *q, const string &key){
    Node *newNode = new Node;
    newNode->val = key;
    if (isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
    } else {
        newNode->prev = q->tail;
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void dequeue(Queue *q){
    if (isEmpty(q)) return;
    if (q->tail == q->head){
        Node *temp = q->head;
        q->head = nullptr;
        q->tail = nullptr;
        delete temp;
    } else {
        Node *temp = q->head;
        q->head = q->head->next;
        q->head->prev = nullptr;
        delete temp;
    }
}

void saveToFile(Queue *q, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    Node *current = q->head;
    while (current != nullptr) {
        file << current->val << endl;
        current = current->next;
    }
    
    file.close();
}

void loadFromFile(Queue *q, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    clear(q);
    string line;
    while (getline(file, line)) {
        enqueue(q, line);
    }
    
    file.close();
}

void clear(Queue *q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}