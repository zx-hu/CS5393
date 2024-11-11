#ifndef AVLTREE_H
#define AVLTREE_H

#include "include/rapidjson/document.h"

#include <iostream>
#include <algorithm>
#include <fstream>

struct Node {
    std::string key;
    std::vector<std::pair<rapidjson::Document*, int> > value;
    int height;
    Node* left;
    Node* right;
    Node(std::string k, rapidjson::Document* docu);
    ~Node();
};

int getHeight(Node* node);
int getBalanceFactor(Node* node);
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);
Node* insert(Node* node, std::string key, rapidjson::Document* docu);
void inOrderTraversal(Node* node);
void saveTree(Node* node, std::ofstream& outFile);
Node* loadTree(Node* node, std::ifstream& inFile);
std::vector<std::pair<rapidjson::Document*, int> >* find(Node* root, const std::string key);



#endif
