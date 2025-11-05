#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <iostream>

struct Node {
    std::string val;
    Node *next;
    Node *prev;
    Node(){
        val = "";
        next = nullptr;
        prev = nullptr;
    }
};

struct Queue {
    Node* head;
    Node* tail;
    Queue(){
        head = nullptr;
        tail = nullptr;
    }
};

std::ostream &operator<<(std::ostream &os, const Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, const std::string &key);
void dequeue(Queue *q);
void saveToFile(Queue *q, const std::string &filename);
void loadFromFile(Queue *q, const std::string &filename);
void clear(Queue *q);

#endif