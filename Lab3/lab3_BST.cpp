/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a binary search tree.
It will be used to store a set of numbers.
The binary search tree demoonstrates basic operations like insert, delete, and search.
*/

#include <iostream>
#include <sstream>
using namespace std;

//Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

};

//Function to create a new Node
Node* createNode(int data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to do inorder traversal of BST
void inorderTraversal(Node* root)
{
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// Function to insert a node in the BST
Node* insertNode(Node* root, int data)
{
    if (root == nullptr) { // If the tree is empty, return a new node 
        cout << "Node " << data << " inserted" << endl;
        return createNode(data);
    }

    // Otherwise, recur down the tree
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertNode(root->right, data); 
    }
    // return the (unchanged) node pointer
    return root;
}

// Function to search a given key in a given BST
Node* searchNode(Node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == nullptr) {
        cout << "Node " << key << " not found." << endl;
        return root;
    }
    if (root->data == key){
        cout << "Node " << key << " found." << endl;
        return root;
    }

    // Key is greater than root's key
    if (root->data < key) {
        return searchNode(root->right, key);
    }
    // Key is smaller than root's key
    return searchNode(root->left, key);
}

// Function to delete a node
Node* deleteNode(Node* root, int data)
{   
    if (root == nullptr){
        cout << "Node " << data << " not found to delete." << endl;
        return root;
    }
    // If the data to be deleted is smaller than the root's data
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    // If the data to be deleted is greater than the root's data
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    // data is same as root's data, this is the node to be deleted
    else {
        Node* temp;
        // node with only one child or no child
        if (root->left == nullptr) {
            temp = root->right;
            delete root;
            cout << "Node deleted." << endl;
            return temp;
        }
        else if (root->right == nullptr) {
            temp = root->left;
            delete root;
            cout << "Node deleted." << endl;
            return temp;
        }

        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        // loop down to find the leftmost leaf
        temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main(){
    Node* root = nullptr;
    //input string
    string input;
    cout << "Input the dataset: ";
    getline(cin, input);
    
    //remove curly braces
    input = input.substr(1, input.size() - 2);

    //split by commas
    vector<int> numbers;
    stringstream ss(input);
    string item;
    char delimiter = ',';
    while (getline(ss, item, delimiter)) {
        // Remove any leading or trailing whitespace
        item.erase(0, item.find_first_not_of(' '));
        item.erase(item.find_last_not_of(' ') + 1);
        //Convert the string numbers to integers
        int num = stoi(item);
        root = insertNode(root, num);
    }

    // Print inorder traversal 
    cout << "Inorder traversal of the Binary Search Tree: ";
    inorderTraversal(root);
    cout << endl; //formatting

    //search for nodes 60 & 100
    Node* search = searchNode(root, 60);
    search = searchNode(root, 100);

    //search for nodes 25 & 96.3
    search = searchNode(root, 25);
    search = searchNode(root, 96.3);

    //delete nodes 50 & 100
    deleteNode(root, 50);
    deleteNode(root, 100);

    // Print inorder traversal 
    cout << "Inorder traversal of the Binary Search Tree: ";
    inorderTraversal(root);
    cout << endl; //formatting

    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/cpp-binary-search-tree/
Microsoft Copilot: https://copilot.microsoft.com
*/
 