#ifndef FLIST_H
#define FLIST_H

#include <string>
#include <iostream>

struct FLNode {
    std::string val;
    FLNode *next;
    FLNode(){
        val = "";
        next = nullptr;
    }
};

struct FList {
    FLNode *head;
    int size;
    FList(){
        head = nullptr;
        size = 0;
    }
};

std::ostream& operator<<(std::ostream& os, const FList* list);
int searchKey(FList *ls, const std::string &key);
FLNode* searchIndex(FList *ls, int index);
void insert(FLNode* prev, const std::string &key);
void push_front(FList *ls, const std::string &key);
void push_back(FList *ls, const std::string &key);
void insert_after(FList* ls, int index, const std::string &key);
void insert_before(FList* ls, int index, const std::string &key);
void pop_front(FList *ls);
void pop_back(FList *ls);
void removeIndex(FList *ls, int index);
void remove_before(FList *ls, int index);
void remove_after(FList *ls, int index);
void removeKey(FList *ls, const std::string &key);
void print(FList *ls);
void saveToFile(FList *ls, const std::string &filename);
void loadFromFile(FList *ls, const std::string &filename);
void clear(FList *ls);

#endif