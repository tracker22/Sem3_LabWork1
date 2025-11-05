#include <iostream>
#include <string>
#include <fstream>
#include "redBlackTree.h"

using namespace std;

TreeNode *createNode(const string &key){
    return new TreeNode{key};
}

void left_rotate(RBTree *tree, TreeNode *x){
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left != tree->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil){
        tree->root = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(RBTree *tree, TreeNode *y){
    TreeNode *x = y->left;
    y->left = x->right;
    if (x->right != tree->nil){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil){
        tree->root = x;
    }
    else if (y == y->parent->right){
        y->parent->right = x;
    }
    else{
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void insert_fixup(RBTree *tree, TreeNode *current){
    while (current->parent->color == RED){
        if (current->parent == current->parent->parent->left){
            TreeNode *y = current->parent->parent->right;
            if (y->color == RED){
                current->parent->color = BLACK;
                y->color = BLACK;
                current->parent->parent->color = RED;
                current = current->parent->parent;
            }
            else{
                if (current == current->parent->right){
                    current = current->parent;
                    left_rotate(tree, current);
                }
                current->parent->color = BLACK;
                current->parent->parent->color = RED;
                right_rotate(tree, current->parent->parent);
            }
        } else{
            TreeNode *y = current->parent->parent->left;
            if (y->color == RED){
                current->parent->color = BLACK;
                y->color = BLACK;
                current->parent->parent->color = RED;
                current = current->parent->parent;
            }
            else{
                if (current == current->parent->left){
                    current = current->parent;
                    right_rotate(tree, current);
                }
                current->parent->color = BLACK;
                current->parent->parent->color = RED;
                left_rotate(tree, current->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RBTree *tree, const string& key){
    TreeNode *newNode = new TreeNode{key};
    TreeNode *y = tree->nil;
    TreeNode *x = tree->root;
    while (x != tree->nil){
        y = x;
        if (newNode->val < x->val){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y == tree->nil){
        tree->root = newNode;
    }
    else if (newNode->val < y->val){
        y->left = newNode;
    }
    else{
        y->right = newNode;
    }
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->color = RED;
    insert_fixup(tree, newNode);
}

TreeNode* tree_minimum(RBTree *tree, TreeNode *current){
    while (current->left != tree->nil){
        current = current->left;
    }
    return current;
}    

TreeNode* tree_successor(RBTree *tree, TreeNode *current){
    if (current->right != tree->nil){
        return tree_minimum(tree, current->right);
    }
    TreeNode *y = current->parent;
    while (y != tree->nil and current == y->right){
        current = y;
        y = y->parent;
    }
    return y;
}

void transplant(RBTree *tree, TreeNode *u, TreeNode *v){
    if (u->parent == tree->nil){
        tree->root = v;
    } else if ( u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void tree_delete_fixup(RBTree *tree, TreeNode *x){
    while (x != tree->root and x->color == BLACK){
        if (x == x->parent->left){
            TreeNode *w = x->parent->right;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK and w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else{ 
                if ( w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color= RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            TreeNode *w = x->parent->left;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK and w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else{ 
                if ( w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color= RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void tree_delete(RBTree *tree, TreeNode *nodeToDel){
    if (nodeToDel == tree->nil) return;
    
    TreeNode *y = nodeToDel;
    Color yOriginalColor = y->color;
    TreeNode *x = nullptr;
    
    if (nodeToDel->left == tree->nil){
        x = nodeToDel->right;
        transplant(tree, nodeToDel, nodeToDel->right);
    } else if ( nodeToDel->right == tree->nil){
        x = nodeToDel->left;
        transplant(tree, nodeToDel, nodeToDel->left);
    } else {
        y = tree_minimum(tree, nodeToDel->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == nodeToDel){
            x->parent = y;
        } else {
            transplant(tree, y, y->right);
            y->right = nodeToDel->right;
            y->right->parent = y;
        }
        transplant(tree, nodeToDel, y);
        y->left = nodeToDel->left;
        y->left->parent = y;
        y->color = nodeToDel->color;
    }
    
    if (yOriginalColor == BLACK){
        tree_delete_fixup(tree, x);
    }
    delete nodeToDel;
}

TreeNode* search(RBTree *tree, const string& key){
    TreeNode *current = tree->root;
    while (current != tree->nil and current->val != key){
        if (key < current->val){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

void inorder_traversal(RBTree *tree, TreeNode *node) {
    if (node != tree->nil) {
        inorder_traversal(tree, node->left);
        cout << node->val << " (" << (node->color == RED ? "RED" : "BLACK") << ")" << endl;
        inorder_traversal(tree, node->right);
    }
}

void saveToFile(RBTree *tree, TreeNode *node, ofstream &file) {
    if (node != tree->nil) {
        saveToFile(tree, node->left, file);
        file << node->val << endl;
        saveToFile(tree, node->right, file);
    }
}

void saveToFile(RBTree *tree, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    saveToFile(tree, tree->root, file);
    file.close();
}

void loadFromFile(RBTree *tree, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    clear(tree);
    string line;
    while (getline(file, line)) {
        insert(tree, line);
    }
    
    file.close();
}

void clear(RBTree *tree) {
    while (tree->root != tree->nil) {
        tree_delete(tree, tree->root);
    }
}