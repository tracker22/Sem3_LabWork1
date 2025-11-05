#ifndef DLLIST_H
#define DLLIST_H

#include <string>

struct DLLNode {
    std::string val;
    DLLNode *next;
    DLLNode *prev;
    DLLNode(){
        val = "";
        next = nullptr;
        prev = nullptr;
    }
};

struct DLList {
    DLLNode *nil;
    int size;
    DLList(){
        nil = new DLLNode;
        nil->next = nil;
        nil->prev = nil;
        size = 0;
    }
};

bool isEmpty(DLList* ls);
int find_index(DLList *ls, const std::string &key);
DLLNode* search_key(DLList *ls, const std::string &key);
DLLNode* search_index(DLList *ls, int index);
void push_front(DLList *ls, const std::string &key);
void push_back(DLList *ls, const std::string &key);
void pop_back(DLList *ls);
void pop_front(DLList *ls);
void insert_after(DLList *ls, int index, const std::string &key);
void insert_before(DLList *ls, int index, const std::string &key);
void remove(DLLNode* delNode);
void remove_key(DLList *ls, const std::string &key);
void remove_after(DLList *ls, int index);
void remove_before(DLList *ls, int index);
void print(DLList *ls);
void reverse_print(DLList *ls);
void saveToFile(DLList *ls, const std::string &filename);
void loadFromFile(DLList *ls, const std::string &filename);
void clear(DLList *ls);

#endif