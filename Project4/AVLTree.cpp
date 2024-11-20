#include "AVLTree.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

// Node constructor
Node::Node(std::string k, std::string file) : key(k), height(1), left(nullptr), right(nullptr) {
    value[file] = 1;
}

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

Node* insert(Node* node, std::string key, std::string file_path, int quantity) {
    if (node == nullptr) {
        return new Node(key, file_path);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, file_path, quantity);
    } else if (key > node->key) {
        node->right = insert(node->right, key, file_path, quantity);
    } else {    //found
        node->value[file_path]+= quantity;
        return node;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void saveTree(Node* node, std::ofstream& outFile) {
    if (node == nullptr) {                  //saves in preorder traversal order
        return;
    }
                                                    //save format:
    outFile << node->key << std::endl;              //node
    for(auto& pair : node->value){                  //path,quantity;path,quantity 
        outFile << pair.first << "," << pair.second << ";";
        
    }
    outFile << std::endl;
    saveTree(node->left, outFile);
    saveTree(node->right, outFile);
}

Node* loadTree(Node* node, std::ifstream& inFile){
    std::string line;
    while(inFile.good()){
        std::string key, path, quantityString;
        std::getline(inFile, key); //key
        std::getline(inFile, line);    //path,quantity;
        std::stringstream ss(line);
        while(std::getline(ss, path, ',')){
            std::getline(ss, quantityString, ';');    //quantity
            int quantity = stoi(quantityString);
            node = insert(node, key, path, quantity);
        }
        
    }
    return node;
}

std::unordered_map<std::string, int> find(Node* root, const std::string key){
    if(root == nullptr){
        return {};     //key not found
    }

    if(key < root->key){
        return find(root->left, key);
    }else if(key > root->key){
        return find(root->right, key);
    }else{
        return root->value;
    }
}
