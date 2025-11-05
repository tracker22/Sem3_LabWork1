// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "array.h"
#include "doublyLinkedList.h"
#include "forwardList.h"
#include "queue.h"
#include "redBlackTree.h"
#include "stack.h"

using namespace std;

void parseArguments(int argc, char* argv[], string& filename, string& query) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
}

vector<string> parseQuery(const string& query) {
    vector<string> tokens;
    stringstream ss(query);
    string token;
    
    // Удаляем одинарные кавычки если они есть
    string cleanQuery = query;
    if (!cleanQuery.empty() && cleanQuery.front() == '\'' && cleanQuery.back() == '\'') {
        cleanQuery = cleanQuery.substr(1, cleanQuery.length() - 2);
    }
    
    ss = stringstream(cleanQuery);
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void handleArrayOperation(const vector<string>& tokens, const string& filename) {
    static Array arr;
    
    if (fileExists(filename)) {
        loadFromFile(&arr, filename);
    }
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "APUSH" && tokens.size() >= 2) {
        push_back(&arr, tokens[1]);
        cout << ">> " << tokens[1] << endl;
    } else if (operation == "APUSH_INDEX" && tokens.size() >= 3) {
        int index = stoi(tokens[1]);
        push_index(&arr, index, tokens[2]);
        cout << ">> " << tokens[2] << "' at index " << index << " in array" << endl;
    } else if (operation == "APOP_INDEX" && tokens.size() >= 2) {
        int index = stoi(tokens[1]);
        string itemToDelete = arr.value[index];
        pop_index(&arr, index);
        cout << "<<" << itemToDelete << endl;
    } else if (operation == "AGET" && tokens.size() >= 2) {
        int index = stoi(tokens[1]);
        string result = get(&arr, index);
        cout << "<< " << result << endl;
    } else if (operation == "APRINT") {
        cout << "Array: ";
        print(&arr);
    } else if(operation == "AREPLACE" && tokens.size() >= 3){
        cout << arr.value[stoi(tokens[1])] << " replaced with " << tokens[2] << " at index " << tokens[1] << endl;
        replace(&arr, stoi(tokens[1]), tokens[2]);
    } else if (operation == "ALENGTH") {
        cout << "Array length: " << length(&arr) << endl;
    } else {
        cout << "Error: Invalid array operation or missing parameters" << endl;
        return;
    }
    
    saveToFile(&arr, filename);
}

void handleDLLOperation(const vector<string>& tokens, const string& filename) {
    static DLList dll;
    
    if (fileExists(filename)) {
        loadFromFile(&dll, filename);
    }
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "DLLPUSH_FRONT" && tokens.size() >= 2) {
        push_front(&dll, tokens[1]);
        cout << "<< " << tokens[1] <<  endl;
    } else if (operation == "DLLPUSH_BACK" && tokens.size() >= 2) {
        push_back(&dll, tokens[1]);
        cout << "<< " << tokens[1] << endl;
    } else if(operation == "DLLSEARCH_KEY" && tokens.size() >= 2){
        int index = find_index(&dll, tokens[1]);
        if (index != -1){
            cout << tokens[1] << " index " << index << endl;
        } else {
            cout << "item not found";
        }
    } else if(operation == "DLLINSERT_AFTER"){
        int index = stoi(tokens[1]);
        insert_after(&dll, index, tokens[2]);
        cout << ">> " << tokens[2] << " after " << index << endl;
    } else if(operation == "DLLINSERT_BEFORE"){
        int index = stoi(tokens[1]);
        insert_before(&dll, index, tokens[2]);
        cout << ">> " << tokens[2] << " before " << index << endl;
    } else if (operation == "DLLPOP_FRONT") {
        string itemToDelete = dll.nil->next->val;
        pop_front(&dll);
        cout << "<< "<< itemToDelete << endl;
    } else if (operation == "DLLPOP_BACK") {
        string itemToDelete = dll.nil->prev->val;
        pop_back(&dll);
        cout << "<< " << itemToDelete << endl;
    } else if(operation == "DLLREMOVE_AFTER" && tokens.size() >= 2){
        int index = stoi(tokens[1]);
        if (index >= 0 && index < dll.size - 1) {
            cout << "<< " << search_index(&dll, index + 1)->val << " after " << index << endl;
            remove_after(&dll, index);
        } else {
            cout << "Error: Invalid index or no element after index " << index << endl;
        }
    } else if(operation == "DLLREMOVE_BEFORE" && tokens.size() >= 2){
        int index = stoi(tokens[1]);
        if (index >= 0 && index < dll.size) {
            cout << "<< " << search_index(&dll, index - 1)->val << " before " << index << endl;
            remove_before(&dll, index);
        } else {
            cout << "Error: Invalid index or no element after index " << index << endl;
        }
    } else if(operation =="DLLREMOVE_KEY"){
        cout << "<< " << tokens[1] << endl;
        remove_key(&dll, tokens[1]);
    } else if (operation == "DLLPRINT") {
        cout << "Doubly linked list contents: ";
        print(&dll);
    } else {
        cout << "Error: Invalid doubly linked list operation or missing parameters" << endl;
        return;
    }
    
    saveToFile(&dll, filename);
}

void handleFLOperation(const vector<string>& tokens, const string& filename) {
    static FList fl;
    
    // Загружаем данные из файла перед операцией
    if (fileExists(filename)) {
        loadFromFile(&fl, filename);
    }
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "FLPUSH_FRONT" && tokens.size() >= 2) {
        push_front(&fl, tokens[1]);
        cout << ">> " << tokens[1]  << endl;
    } else if (operation == "FLPUSH_BACK" && tokens.size() >= 2) {
        push_back(&fl, tokens[1]);
        cout << ">> " << tokens[1]  << endl;
    } else if (operation == "FLINSERT_AFTER" && tokens.size() >= 3) {
        int index = stoi(tokens[1]);
        if (index >= 0 && index < fl.size) {
            insert_after(&fl, index, tokens[2]);
            cout << ">> " << tokens[2] << " after " << index << endl;
        } else {
            cout << "Error: Invalid index " << index << endl;
        }
    } else if (operation == "FLINSERT_BEFORE" && tokens.size() >= 3) {
        int index = stoi(tokens[1]);
        if (index >= 0 && index < fl.size) {
            insert_before(&fl, index, tokens[2]);
            cout << ">> " << tokens[2] << " before " << index << endl;
        } else {
            cout << "Error: Invalid index " << index << endl;
        }
    } else if (operation == "FLPOP_FRONT") {
        if (fl.size > 0) {
            cout << "<< " << fl.head->val << endl;
            pop_front(&fl);
        } else {
            cout << "Forward list is empty" << endl;
        }
    } else if (operation == "FLPOP_BACK") {
        if (fl.size > 0) {
            cout << "<< " << (*searchIndex(&fl, fl.size-1)).val << endl;
            pop_back(&fl);
        } else {
            cout << "Forward list is empty" << endl;
        }
    } else if (operation == "FLREMOVE_AFTER" && tokens.size() >= 2) {
        int index = stoi(tokens[1]);
        if (index >= 0 && index < fl.size - 1) {
            cout << "<< " << searchIndex(&fl, index + 1)->val << " after " << index << endl;
            remove_after(&fl, index);
        } else {
            cout << "Error: Invalid index or no element after index " << index << endl;
        }
    } else if (operation == "FLREMOVE_BEFORE" && tokens.size() >= 2) {
        int index = stoi(tokens[1]);
        if (index > 0 && index < fl.size) {
            cout << "<< " << searchIndex(&fl, index - 1)->val << " before " << index << endl;
            remove_before(&fl, index);
        } else {
            cout << "Error: Invalid index or no element before index " << index << endl;
        }
    } else if(operation == "FLSEARCH_KEY" && tokens.size() >= 2){
        int index = searchKey(&fl, tokens[1]);
        if (index != -1){
            cout << tokens[1] << " index " << index << endl;
        } else {
            cout << "item not found";
        }
    } else if(operation == "FLREMOVE_KEY" && tokens.size() >= 2){
        cout << "<< " << tokens[1] << endl;
        removeKey(&fl, tokens[1]);
    } else if (operation == "FLPRINT") {
        if (fl.size == 0) {
            cout << "Forward list is empty" << endl;
        } else {
            cout << "Forward list contents: ";
            print(&fl);
        }
    } else {
        cout << "Error: Invalid forward list operation or missing parameters" << endl;
        return;
    }
    
    saveToFile(&fl, filename);
}
void handleQueueOperation(const vector<string>& tokens, const string& filename) {
    static Queue q;
    
    if (fileExists(filename)) {
        loadFromFile(&q, filename);
    }
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "QPUSH" && tokens.size() >= 2) {
        enqueue(&q, tokens[1]);
        cout << ">> " << tokens[1] << endl;
    } else if (operation == "QPOP") {
        if (!isEmpty(&q)) {
            cout << "<< " << q.head->val << endl;
            dequeue(&q);
        } else {
            cout << "Queue is empty" << endl;
        }
    } else if (operation == "QPRINT") {
        cout << "Queue contents: " << &q << endl;
    } else {
        cout << "Error: Invalid queue operation or missing parameters" << endl;
        return;
    }
    
    saveToFile(&q, filename);
}

void handleStackOperation(const vector<string>& tokens, const string& filename) {
    static Stack s;
    
    loadFromFile(&s, filename);
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "SPUSH" && tokens.size() >= 2) {
        push(&s, tokens[1]);
        cout << ">> " << tokens[1] << endl;
    } else if (operation == "SPOP") {
        if (!isEmpty(&s)) {
            string topValue = s.top->val;
            pop(&s);
            cout << "<< " << topValue << endl;
        } else {
            cout << "Stack is empty" << endl;
        }
    } else if (operation == "SPRINT") {
        if (isEmpty(&s)) {
            cout << "Stack is empty" << endl;
        } else {
            cout << "Stack (top to bottom): " << &s << endl;
        }
    } else {
        cout << "Error: Invalid stack operation" << endl;
        return;
    }
    
    saveToFile(&s, filename);
}

void handleTreeOperation(const vector<string>& tokens, const string& filename) {
    static RBTree tree;
    
    if (fileExists(filename)) {
        loadFromFile(&tree, filename);
    }
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return;
    }
    
    string operation = tokens[0];
    
    if (operation == "TINSERT" && tokens.size() >= 2) {
        insert(&tree, tokens[1]);
        cout << ">> " << tokens[1] << endl;
    } else if (operation == "TSEARCH" && tokens.size() >= 2) {
        TreeNode* result = search(&tree, tokens[1]);
        if (result != tree.nil) {
            cout << ">> TRUE" << endl;
        } else {
            cout << ">> FALSE" << endl;
        }
    } else if (operation == "TPRINT") {
        cout << "Tree contents (inorder):" << endl;
        inorder_traversal(&tree, tree.root);
    } else if (operation == "TDELETE" && tokens.size() >= 2) {
        TreeNode* node = search(&tree, tokens[1]);
        if (node != tree.nil) {
            tree_delete(&tree, node);
            cout << "<< " << tokens[1] << endl;
        } else {
            cout << "'" << tokens[1] << "' not found in tree" << endl;
        }
    } else {
        cout << "Error: Invalid tree operation or missing parameters" << endl;
        return;
    }
    
    saveToFile(&tree, filename);
}

int main(int argc, char* argv[]) {
    string filename, query;
    parseArguments(argc, argv, filename, query);
    
    if (filename.empty() || query.empty()) {
        cout << "Error: Both --file and --query arguments are required" << endl;
        return 1;
    }
    
    vector<string> tokens = parseQuery(query);
    
    if (tokens.empty()) {
        cout << "Error: Empty query" << endl;
        return 1;
    }
    
    string structureType = tokens[0];
    
    try {
        if (structureType.find("A") == 0) { // Array operations
            handleArrayOperation(tokens, filename);
        } else if (structureType.find("DLL") == 0) { // Doubly linked list operations
            handleDLLOperation(tokens, filename);
        } else if (structureType.find("FL") == 0) { // Forward list operations
            handleFLOperation(tokens, filename);
        } else if (structureType.find("Q") == 0) { // Queue operations
            handleQueueOperation(tokens, filename);
        } else if (structureType.find("S") == 0) { // Stack operations
            handleStackOperation(tokens, filename);
        } else if (structureType.find("T") == 0) { // Tree operations
            handleTreeOperation(tokens, filename);
        } else {
            cout << "Error: Unknown structure type '" << structureType << "'" << endl;
            return 1;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}