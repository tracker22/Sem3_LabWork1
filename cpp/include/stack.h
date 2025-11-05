#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

struct StackNode {
    std::string val;
    StackNode *next;
    StackNode(const std::string &value = ""){
        val = value;
        next = nullptr;
    }
};

struct Stack {
    StackNode* top;
    Stack(){
        top = nullptr;
    }
};

std::ostream& operator<<(std::ostream& os, const Stack *s);
bool isEmpty(Stack *s);
void pop(Stack *s);
void push(Stack *s, const std::string &key);
void saveToFile(Stack *s, const std::string &filename);
void loadFromFile(Stack *s, const std::string &filename);
//bool get(Stack* s, const string &key);
void clear(Stack *s);

#endif