/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: 
The objective of this code is to implement a queue with error handling. 
The queue demonstrates basic operations such as enqueue, dequeue, peek/front, isEmpty, isFull, and size.
The queue also has proper error handling implemented to handle dequeue and peek operations on an empty queue, and enqueue operations on a full queue.
*/

#include <iostream>
using namespace std;

#define SIZE 1000

//error for if the queue is empty and dequeue or peek is called
class EmptyQueueException : public runtime_error {
public:
    EmptyQueueException() : runtime_error("Error: Queue is empty") {}
};

//error for if the queue is full and enqueue is called
class QueueOverflowException : public runtime_error {
public:
    QueueOverflowException() : runtime_error("Error: Queue is full") {}
};


class Queue{
    public:

        int front, rear, count, capacity;
        int* arr;

        //constructor
        Queue(int size){
            arr = new int[size];
            capacity = size;
            front = 0;
            rear = 0;
            count = 0;

        }

        //add an element to the back of the queue
        void enqueue(int value){
            if(isFull()){
                throw QueueOverflowException();
            }
            count++;
            arr[rear] = value;
            rear = rear + 1 % capacity;
        }

        //remove and return the front element of the queue
        int dequeue(){
            if(isEmpty()){
                throw EmptyQueueException();
            }
            int ret = arr[front];
            count--;
            front = front + 1 % capacity;
            return ret;
        }

        //return the front element without removing it
        int peek(){
            if(isEmpty()){
                throw EmptyQueueException();
            }
            return arr[front];
        }

        //check if the queue is empty
        bool isEmpty(){
            return count == 0;
        }

        //check if the queue is full
        bool isFull(){
            return count == capacity;
        }

        //return the number of elements in the queue
        int size(){
            return count;
        }

};

int main(){

    //creating the queue
    Queue q(SIZE);

    try{
        
        //adding elements to the queue
        cout << "Add elements to the queue. Enter a non number to quit: ";
        int value;
        while(true){
            cin >> value;
            if(cin.fail()){
                cout << "Non-number entered." << endl;
                break;
            }
            q.enqueue(value);
        }

        //clearing cin to take in more input later
        cin.clear();
        cin.ignore();

        //showing the current size of the queue
        cout << "Current size: " << q.size() << endl;

        //removing elements
        cout << "How many elements would you like to dequeue? ";
        int loop;
        cin >> loop;
        for(int i=0; i<loop; i++){
            cout << q.dequeue()<< " ";
        }

        //new line for better formatting in output
        cout << endl;

        //showing the current size of the queue
        cout << "Current size: " << q.size() << endl;

        //displaying the new top element
        cout << "Peeking into the queue: " << q.peek() << endl; 

    }catch(const EmptyQueueException& e) {          //will handle error if queue is underfilled or overflowed
        cout << e.what() << endl;
    }catch(const QueueOverflowException& e) {
        cout << e.what() << endl;
    }

    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/introduction-and-array-implementation-of-queue/
Kenyon College: https://cs.kenyon.edu/index.php/scmp-218-00-data-structures/queue-implementation-in-c/ 
Microsoft Copilot: https://copilot.microsoft.com
*/
