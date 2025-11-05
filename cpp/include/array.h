#ifndef ARRAY_H
#define ARRAY_H

#include <string>

struct Array{
    int size;
    std::string *value;
    Array(){
        size = 0;
        value = new std::string[size];
    }
    ~Array(){
        delete[] value;
    }
};

void push_index(Array *arr, int index, const std::string &key);
void push_back(Array *arr, const std::string &key);
void pop_index(Array *arr, int index);
void replace(Array *arr, int index, const std::string& key);
void print(Array *arr);
std::string get(Array *arr, int index);
int length(Array *arr);
void saveToFile(Array *arr, const std::string &filename);
void loadFromFile(Array *arr, const std::string &filename);
void clear(Array *arr);

#endif