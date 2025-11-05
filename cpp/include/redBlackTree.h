#ifndef TREE_H
#define TREE_H

#include <string>

enum Color {
    RED,
    BLACK
};

struct TreeNode {
    Color color;
    TreeNode *parent;
    TreeNode *right;
    TreeNode *left;
    std::string val;
    TreeNode(const std::string &key){
        val = key; 
        color = RED;
        parent = nullptr;
        right = nullptr;
        left = nullptr;
    }
    TreeNode(){
        color = RED;
        val = "";
        parent = nullptr;
        right = nullptr;
        left = nullptr;
    }
};

struct RBTree {
    TreeNode *root;
    TreeNode *nil;
    RBTree(){
        nil = new TreeNode;
        nil->color = BLACK;
        nil->right = nil;
        nil->left = nil;
        nil->parent = nil;
        root = nil;
    }
};

TreeNode *createNode(const std::string &key);
void left_rotate(RBTree *tree, TreeNode *x);
void right_rotate(RBTree *tree, TreeNode *y);
void insert_fixup(RBTree *tree, TreeNode *current);
void insert(RBTree *tree, const std::string& key);
TreeNode* tree_minimum(RBTree *tree, TreeNode *current);
TreeNode* tree_successor(RBTree *tree, TreeNode *current);
void transplant(RBTree *tree, TreeNode *u, TreeNode *v);
void tree_delete_fixup(RBTree *tree, TreeNode *x);
void tree_delete(RBTree *tree, TreeNode *nodeToDel);
TreeNode* search(RBTree *tree, const std::string& key);
void inorder_traversal(RBTree *tree, TreeNode *node);
void saveToFile(RBTree *tree, const std::string &filename);
void loadFromFile(RBTree *tree, const std::string &filename);
void clear(RBTree *tree);

#endif