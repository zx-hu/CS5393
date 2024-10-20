/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a graph as an adjacency list and matrix.
It allows the user to create their own nodes and edges.
The graph can be traversed in preorder, inorder, and postorder.
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

const int Graph_Size = 6;

struct Node{
    int value;
    Node** neighbors;
    int neighborCount = 0;

    Node(int val){
        value = val;
        neighbors = new Node*[Graph_Size];
    }

    void addNeighbor(Node* neighbor){
        neighbors[neighborCount++] = neighbor;
    }

    ~Node(){
        delete[] neighbors;
    }
};

class Graph{
    private:
        Node** nodes;
        int nodeCount = 0;
        int capacity;
        int** matrix;

    public: 
        Graph(int size){
            capacity = size;
            nodes = new Node*[capacity];
            matrix = new int*[capacity];
            for(int i=0; i<capacity; i++){
                matrix[i] = new int[capacity];
            }
        }

        ~Graph(){   //may have to add more later
            for(int i =0; i<nodeCount; i++){
                delete[] nodes[i];
                delete[] matrix[i];
            }
            delete[] nodes;
            delete[] matrix;
        }

        Node* getNode(int val){
            for(int i=0; i<nodeCount; i++){
                if(nodes[i]->value == val){
                    return nodes[i];
                }
            }
            nodes[nodeCount] = new Node(val);   //make new node if node doesn't exist
            nodes[nodeCount++];

            return nodes[nodeCount-1];
        }


        void addEdge(int src, int dest){
            Node* srcNode = getNode(src);
            Node* destNode = getNode(dest);
            srcNode->addNeighbor(destNode);
            destNode->addNeighbor(srcNode); //undirected
            matrix[src][dest] = 1;
            matrix[dest][src] = 1;          //undirected
        }

        //node -> left -> right
        void preorderDFS(Node* node, bool* visited){
            if(!node || visited[node->value]){
                return;
            }
            visited[node->value] = true;
            cout << node->value << " ";

            for(int i = 0; i< node->neighborCount; i++){
                preorderDFS(node->neighbors[i], visited);
            }
        }

        //left -> node -> right
        void inorderDFS(Node* node, bool* visited){
            if(!node || visited[node->value]){
                return;
            }
            visited[node->value] = true;

            if(node->neighborCount > 0){    //left node
                inorderDFS(node->neighbors[0], visited);
            }
            cout << node->value << " ";

            for(int i = 1; i < node->neighborCount; i++){
                inorderDFS(node->neighbors[i], visited); //right node
            }
        }

        //left -> right -> node
        void postorderDFS(Node* node, bool* visited){
            if(!node || visited[node->value]){
                return;
            }

            visited[node->value] = true;

            for(int i = 0; i < node->neighborCount; i++){
                postorderDFS(node->neighbors[i], visited);
            }
            cout << node->value << " ";
        }

        void DFS(int startVal, string order = "preorder"){
            bool* visited = new bool[capacity];
            for(int i = 0; i<capacity; i++){
                visited[i] = false;
            }

            Node* startNode = getNode(startVal);
            if(order == "preorder"){
                preorderDFS(startNode, visited);
            }else if(order == "inorder"){
                inorderDFS(startNode, visited);
            }else if(order == "postorder"){
                postorderDFS(startNode, visited);
            }

            delete[] visited;
        }

        void printGraph(){
            for(int i = 0; i<nodeCount; i++){
                cout << nodes[i]->value << ": ";
                for(int j=0; j<nodes[i]->neighborCount; j++){
                    cout << nodes[i]->neighbors[j]->value << " ";
                }
                cout << endl;
            }
        }

        void printMatrix(){
            cout << "  ";
            for(int i = 0; i<nodeCount; i++){
                cout << i << " ";
            }
            cout << endl;
            for(int i =0; i<nodeCount; i++){
                cout << i <<  " ";
                for(int j = 0; j<nodeCount; j++){
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

};

int main(){

    int size;
    cout << "Input the size of the graph: ";
    cin >> size;
    Graph g(size);

    for (int i = 0; i < size; i++){
        g.getNode(i);   //fill nodes with 0 through size-1
    }

    int src, dest;
    cout << "enter 2 numbers at a time to add as an edge. enter an invalid value to quit: ";
    while(true){
        cin >> src;
        cin >> dest;
        if(src >= 0 && src < size && dest >= 0 && dest < size){
            g.addEdge(src, dest);
            continue;
        }
        break;
    }

    g.printGraph();
    g.printMatrix();

    string order;
    while(true){
        cout << "what traversal (preorder, inorder, postorder)? enter a non value to quit: ";
        cin >> order;
        if(order != "preorder" && order != "inorder" && order != "postorder"){
            break;
        }
        cout << "what node to start from: ";
        cin >> src;
        g.DFS(src, order);
        cout << endl;
    }
    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
Microsoft Copilot: https://copilot.microsoft.com 
*/
