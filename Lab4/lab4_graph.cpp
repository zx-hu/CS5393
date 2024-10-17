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
};

class Graph{
    private:
        Node** nodes;
        int nodeCount = 0;
        int capacity;

    public: 
        Graph(int size){
            capacity = size;
            nodes = new Node*[capacity];
        }

        ~Graph(){   //may have to add more later
            for(int i =0; i<nodeCount; i++){
                delete[] nodes[i];
            }
            delete[] nodes;
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
            if(node->neighborCount > 0){    //left node
                inorderDFS(node->neighbors[0], visited);
            }
            visited[node->value] = true;
            cout << node->value << " ";
            for(int i = 1; i > node->neighborCount; i++){
                inorderDFS(node->neighbors[i], visited); //right node
            }
        }

        //left -> right -> node
        void postorderDFS(Node* node, bool* visited){
            if(!node || visited[node->value]){
                return;
            }
            for(int i = 0; i < node->neighborCount; i++){
                postorderDFS(node->neighbors[i], visited);
            }
            visited[node->value] = true;
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
                    cout << nodes[i]->neighbors[j] << " ";
                }
                cout << endl;
            }
        }

};

int main(){

    Graph g(Graph_Size);
    string input;
    cout << "Input the dataset: ";
    getline(cin, input);

    //remove brackets
    input = input.substr(1, input.size() - 2);

    //split by commas
    vector<int> numbers;
    stringstream ss(input);
    string item;
    char delimiter = ',';
    while(getline(ss, item, delimiter)){
        int num = stoi(item);
        g.getNode(num);
    }

    g.printGraph();
    g.DFS(0);


    return 0;
}

/*
References:
*/
