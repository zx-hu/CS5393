#include "AVLTree.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/writer.h"

#include <iostream>
#include <algorithm>
#include <fstream>

// Node constructor
Node::Node(std::string k, rapidjson::Document* docu) : key(k), height(1), left(nullptr), right(nullptr) {
    value.push_back({docu, 1});
}

Node::~Node() {
    for (auto& pair : value) {
        delete pair.first;  // Delete the dynamically allocated Document
    }
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

Node* insert(Node* node, std::string key, rapidjson::Document* docu) {
    if (node == nullptr) {
        rapidjson::Document* docuCopy = new rapidjson::Document();
        docuCopy->CopyFrom(*docu, docuCopy->GetAllocator());  // Create a deep copy
        return new Node(key, docuCopy);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, docu);
    } else if (key > node->key) {
        node->right = insert(node->right, key, docu);
    } else {    
        bool docuFound = false;
        for(auto& pair : node->value){
            if(pair.first == docu){         //if document is already in set
                pair.second += 1;
                docuFound = true;
                break;
            }
        }

        if(!docuFound){
            rapidjson::Document* docuCopy = new rapidjson::Document();
            docuCopy->CopyFrom(*docu, docuCopy->GetAllocator());  // Create a deep copy
            node->value.push_back({docuCopy, 1});
        }

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

void inOrderTraversal(Node* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left);
    std::cout << node->key << " ";
    inOrderTraversal(node->right);
}

void saveTree(Node* node, std::ofstream& outFile) {
    if (node == nullptr) {
        return;
    }
    saveTree(node->left, outFile);

    outFile << node->key << ": " << std::endl;
    for(auto& pair : node->value){ 
        /*rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        pair.first->Accept(writer);  // Serialize the document into the string buffer
        outFile << "(" << buffer.GetString() << ", " << pair.second << "), ";*/
        rapidjson::Document docu = *pair.first;
        outFile << 
        
    }
    outFile << std::endl;

    saveTree(node->right, outFile);
}

Node* loadTree(Node* node, std::ifstream& inFile){
    //can't write this until i decide how to save the trees
    return node;
}

std::vector<std::pair<rapidjson::Document*, int> >* find(Node* root, const std::string key){
    if(root == nullptr){
        return nullptr;     //key not found
    }

    if(key < root->key){
        return find(root->left, key);
    }else if(key > root->key){
        return find(root->right, key);
    }else{
        return &(root->value);
    }
}