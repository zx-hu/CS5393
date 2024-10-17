/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: 
The objective of this code is to implement a stack. 
The stack will be used to check for balanced parenthesis in a given expression, ensuring every open parenthesis has a corresponding close parenthesis in the correct order.
The stack also has basic operations such as push, pop, peek, isEmpty, and isFull.
*/

#include <iostream>
using namespace std;

#define MAX 1000

class Stack{
    private:
        int top;

    public:
        char arr[MAX];    //maximum size of stack

        //constructor
        Stack(){
            top = -1;
        }

        //add an element to the top of the stack
        bool push(char element){
            if(top > MAX){
                cout << "stack overflow";
                return false;
            }
            arr[++top] = element;
            return true;
        }

        //remove and return the top element of the stack
        char pop(){
            if(top < 0){
                cout << "Stack is empty";
                return ' ';
            }
            return arr[top--];
        }

        //return the top element without removing it
        char peek(){
            if(top < 0){
                cout << "Stack is Empty";
                return ' ';
            }
            return arr[top];
        }

        //check if the stack is empty
        bool isEmpty(){
            return top < 0;
        }

        //check is the stack is full
        bool isFull(){
            return top == MAX;
        }

    
};


int main(){


    //initialize stack
    Stack s;

    //take input to insert into stack
    string input;
    cout << "Input an expression: ";
    getline(cin, input);

    //insert input into stack
    for(char c : input){
        //add to stack if character is an open parenthesis
        if(c == 40 || c == 91){
            s.push(c);
        } 
        //compare character with stack if character is a closed paranthesis
        if(c == 41 || c == 93){
            char temp = s.pop();
            if((c == 41 && temp != 40) || (c == 93 && temp != 91)){
                cout << "Mismatched parentheses" << endl;
                return -1;
            }
        }
    }

    //if stack has left over open parenthesis, the parenthesis do not match
    if(!s.isEmpty()) {
        cout << "Mismatched parentheses" << endl;
        return -1;
    }

    cout << "Parentheses are balanced" << endl;
    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/introduction-to-stack-data-structure-and-algorithm-tutorials/
Microsoft Copilot: https://copilot.microsoft.com 
*/
