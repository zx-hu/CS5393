/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a priority queue using a heap structure.
It will be used to store a set of numbers, prioritized by greatest value.
The queue demonstrates basic operations like push, pop, print, top, and heapify.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
using namespace std;

class PriorityQ{
    private:
        vector<int> heap;
        int parent(int i) {return (i-1)/2;}     //returns index 
        int leftChild(int i) {return 2 * i + 1;}
        int rightChild(int i) {return 2 * i + 2;}

        //shift the node up to maintain heap property
        void heapifyUp(int i){
            while(i>0 && heap[parent(i)] < heap[i]){
                swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }

        //shift the node down to maintain heap property
        void heapifyDown(int i){
            int left = leftChild(i);
            int right = rightChild(i);
            int largest = i;
            if (left < heap.size() && heap[left] > heap[largest])
            largest = left;

            if (right < heap.size() && heap[right] > heap[largest])
                largest = right;

            if (largest != i) {
                swap(heap[i], heap[largest]);
                heapifyDown(largest);
        
            }
        }
    public:
        bool empty() {return heap.empty();}
        int size() {return heap.size();}

        int top(){
            if(empty()) throw runtime_error("PriorityQ is empty");
            return heap.front();
        }
        void push(int element){
            heap.push_back(element);
            heapifyUp(heap.size()-1);
            cout << element << " inserted. " << endl;
        }

        int pop(){
            if(empty()) throw runtime_error("PriorityQ is empty");
            int ret = heap.front();
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);

            return ret;
        }

        void print(){
            PriorityQ tempPQ = *this; // Copy of the current heap
            
            while (!tempPQ.empty()) {
                cout << tempPQ.pop() << " ";
            }
            cout << endl;
        }

};

int main(){
    PriorityQ pq;
    string input;
    cout << "Input the dataset: "; 
    getline(cin, input);

    cout << "Original Dataset: " << input << endl;

    //remove curly braces
    input = input.substr(1, input.size() - 2);

    //split by commas
    vector<int> numbers;
    stringstream ss(input);
    string item;
    char delimiter = ',';
    while(getline(ss, item, delimiter)){
        int num = stoi(item);
        pq.push(num);
    }

    cout << "Priority Q: ";
    pq.print();

    cout << "Size: " << pq.size() << endl;

    while(!pq.empty()){ //empty the queue
        cout << pq.pop() << " popped" << endl;
        cout << "Priority Q: ";
        pq.print();
    }
   
    try {
        pq.pop(); // This should trigger the exception handler
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}

/*
References:
GeeksForGeeks: https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
Microsoft Copilot: https://copilot.microsoft.com
*/
