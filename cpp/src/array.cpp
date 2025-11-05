#include <iostream>
#include <string>
#include <fstream>
#include "array.h"

using namespace std;

void push_index(Array *arr, int index, const string &key){
    string *newV = new string[arr->size + 1];
    int i = 0;
    while (i != index){
        newV[i] = arr->value[i];
        i++;
    }
    newV[i] = key;
    while (i < arr->size){
        newV[i+1] = arr->value[i];
        i++;
    }
    delete [] arr->value;
    arr->value = newV;
    arr->size++;
}

void push_back(Array *arr, const string &key){
    string *newV = new string[arr->size + 1];
    int i = 0;
    while (i < arr->size){
        newV[i] = arr->value[i];
        i++;
    }
    newV[i] = key;
    delete [] arr->value;
    arr->value = newV;
    arr->size++;
}

void pop_index(Array *arr, int index){
    if (index >= arr->size) return;
    string *newV =  new string[arr->size - 1];
    int i = 0;
    while (i != index){
        newV[i] = arr->value[i];
        i++;
    }
    while (i < arr->size - 1){
        newV[i] = arr->value[i+1];
        i++;
    }
    delete [] arr->value;
    arr->value = newV;
    arr->size--;
}

void replace(Array *arr, int index, const string& key){
    if (index < 0 or index >= arr->size) return;
    arr->value[index] = key;
}

void print(Array *arr){
    for (int i = 0; i < arr->size; i++){
        cout << arr->value[i] << " ";
    }
    cout << endl;
}

string get(Array *arr, int index){
    if (index < 0 or index >= arr->size) return "Out of range";
    return arr->value[index];
}

int length(Array *arr){
    return arr->size;
}

void saveToFile(Array *arr, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    for (int i = 0; i < arr->size; i++) {
        file << arr->value[i] << endl;
    }
    
    file.close();
}

void loadFromFile(Array *arr, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    clear(arr);
    string line;
    while (getline(file, line)) {
        push_back(arr, line);
    }
    
    file.close();
}

void clear(Array *arr) {
    delete[] arr->value;
    arr->size = 0;
    arr->value = new string[0];
}