#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
#include <fstream>

struct Node {
    std::string key;
    std::unordered_map<std::string, int> value;
    int height;
    Node* left;
    Node* right;
    Node(std::string k, std::string file);
};

int getHeight(Node* node);
int getBalanceFactor(Node* node);
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);
Node* insert(Node* node, std::string key, std::string file_path, int quantity=1);
void saveTree(Node* node, std::ofstream& outFile);
Node* loadTree(Node* node, std::ifstream& inFile);
std::unordered_map<std::string, int> find(Node* root, const std::string key);



#endif
