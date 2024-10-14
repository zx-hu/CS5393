/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: 
The objective of this code is to implement the basic functions of single, double, and circular linked lists.
The different linked lists will store characters in their respective manner and be used to demonstrate their unique properties.
Each linked list has basic operations like inserting, deleting, and displaying elements.
*/

#include <iostream>
using namespace std;

//node with a pointer to the next node. used for SingleLinkedList and CircularLinkedList
struct SingleLinkNode{
    //default values
    char data = ' ';
    SingleLinkNode* next = nullptr;

    //constructor
    SingleLinkNode(char value){
        data = value;
        next = nullptr;
    }
};

class SingleLinkedList{
    public:
        SingleLinkNode* head;
        SingleLinkNode* nextNodeRef;

        //constructor
        SingleLinkedList(){
            head = nullptr;
        }


        //insert node as nextNodeRef (end)
        void insertAtEnd(char value){
            SingleLinkNode* newNode = new SingleLinkNode(value);
            if(head == nullptr){    //if list is empty
                head = newNode;
                nextNodeRef = newNode;
            }else{
                nextNodeRef->next = newNode;
                nextNodeRef = newNode;
            }
            
        }

        bool deleteNode(char value){  
            SingleLinkNode* current = head;
            //if linked list is empty, return nothing
            if(head == nullptr){
                return false;
            }else if(head->data == value){  //if head is the node to be removed
                SingleLinkNode* del = head;
                head = current->next;
                delete del;
                return true;
            }else{
                current = current->next;   
                SingleLinkNode* prev = head;
                while(current != nullptr){
                    if(current->data == value){
                        prev->next = current->next;
                        delete current;
                        return true;
                    }
                    current = current->next;
                    prev = prev->next;
                }
            }      
            return false;           //went through the whole function without deleting anything
        }

        //prints all the nodes in order
        void display(){
            SingleLinkNode* print = head;
            while(print != nullptr){
                cout << print->data;
                print = print->next;
            }

            cout << endl;
        }
};

//node with a pointer to the next and previous node. used for DoubleLinkedList
struct DoubleLinkNode{
    //default values
    char data = ' ';
    DoubleLinkNode* next = nullptr;
    DoubleLinkNode* prev = nullptr;
    
    //constructor
    DoubleLinkNode(char value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoubleLinkedList{
    public:
        DoubleLinkNode* head;
        DoubleLinkNode* tail;

        //constructor
        DoubleLinkedList(){
            head = nullptr;
            tail = nullptr;
        }

        //insert new node as tail value
        void insertAtEnd(char value){
            DoubleLinkNode* newNode = new DoubleLinkNode(value);
            DoubleLinkNode* temp = tail;

            if(tail == nullptr){    //if list is empty
                tail = newNode;
                head = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
                tail->prev = temp;
            }   
        }

        //insert new node as head value
        void insertAtBeginning(char value){
            DoubleLinkNode* newNode = new DoubleLinkNode(value);
            DoubleLinkNode* temp = head;
            
            if(head == nullptr){    //if list is empty
                head = newNode;
                tail = newNode;
            }else{
                head->prev = newNode;
                head = newNode;
                head->next= temp;
            }
        }

        bool deleteNode(char value){
            DoubleLinkNode* current = head;
            //if linked list is empty, return nothing
            if(head == nullptr){
                return false;
            }else if(head->data == value){  //if head is the node to be removed
                DoubleLinkNode* del = head;
                head = current->next;
                delete del;
                head->prev = nullptr;
                return true;
            }else{
                current = current->next;
                DoubleLinkNode* prevNode = head;
                while(current != tail){
                    if(current->data == value){
                        DoubleLinkNode* temp = current->next;
                        prevNode->next = temp;
                        temp->prev = prevNode;
                        delete current;
                        return true;
                    }
                    current = current->next;
                    prevNode = prevNode->next;
                }
                if(tail->data == value){        //if tail is the node to be removed
                    DoubleLinkNode* del = tail;
                    tail = tail->prev;
                    tail->next = nullptr;
                    delete del;
                    return true;
                }

            }
            return false;           //went through the whole function without deleting anything
        }

        //print nodes head to tail then tail to head
        void display(){
            DoubleLinkNode* print = head;
            while(print != nullptr){    //print head to tail
                cout << print->data;
                print = print->next;
            }

            print = tail;
            while(print != nullptr){    //print tail to head
                cout << print->data;
                print = print->prev;
            }

            cout << endl;
        }
};

class CircularLinkedList{
    public:
        SingleLinkNode* head;
        SingleLinkNode* tail;

        //constructor
        CircularLinkedList(){
            head = nullptr;
            tail = nullptr;
        }

        //insert node as tail
        void insertAtEnd(char value){
            SingleLinkNode* newNode = new SingleLinkNode(value);

            if(head == nullptr){    //if list is empty
                head = newNode;
                tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
                tail->next = head;
            }
        }

        bool deleteNode(char value){
            //if linked list is empty, return nothing
            if(head == nullptr){
                return false;
            }else if(head->data == value){      //if head is the node to be deleted
                SingleLinkNode* del = head;
                head = head->next;
                tail->next = head;
                delete del;
                return true;
            }else{
                SingleLinkNode* current = head->next;
                SingleLinkNode* prev = head;
                while(current != tail){        //if node to be deleted is in the middle
                    if(current->data == value){
                        prev->next = current->next;
                        delete current;
                        return true;             //exit out if element found
                    }
                    current = current->next;
                    prev = prev->next;
                }

                if(current->data == value){         //if tail is the node to be deleted
                    tail = prev;
                    tail->next=head;
                    delete current;
                    return true;
                }
            }
            return false;           //went through the whole function without deleting anything
        }

        //prints head to tail twice
        void display(){
            SingleLinkNode* print = head;     
            for(int i = 0; i<2; i++){   //prints twice  
                while(print != tail){   //stops at tail to not print forever
                    cout << print->data;
                    print = print->next;
                }
                cout << print->data;    //print the tail
                print = print->next;    //point from tail to head
            }

            cout << endl;
        }

};

int main(){
    //get input for linked lists
    string input;
    cout << "Input text for a linked list: ";
    getline(cin,input);

    //initialize linked lists
    SingleLinkedList single;
    DoubleLinkedList doubleList;
    CircularLinkedList circular;

    for(char c : input){
        //insert into the linked lists
        single.insertAtEnd(c);
        doubleList.insertAtEnd(c);
        circular.insertAtEnd(c);
    } 

    //new line for better formatting in output
    cout << endl;

    //display text
    cout << "Single Linked List: ";
    single.display();
    cout << "Double Linked List: ";
    doubleList.display();
    cout << "Circular Linked List: ";
    circular.display();
     
    //new line for better formatting in output
    cout << endl;

    //delete nodes
    cout << "Delete characters from lists. Type 0 to exit. ";
    char toDelete;
    while(true){
        toDelete = char(cin.get());  //this way also allows spaces to get deleted
        cin.clear(); // clear the newline character left in the buffer
        cin.clear();
        if(toDelete == '0') {       //ends if 0 is inputed
            cout << "0 entered." << endl;
            break;
        }
        if(single.deleteNode(toDelete)){    //if true, tell user character was deleted. also deletes from the single linked list
            cout << toDelete << " was deleted" << endl;
        }
        doubleList.deleteNode(toDelete);
        circular.deleteNode(toDelete);
    }

    //display text
    cout << "Single Linked List: ";
    single.display();
    cout << "Double Linked List: ";
    doubleList.display();
    cout << "Circular Linked List: ";
    circular.display();

    return 0;
}

/*
References: 
GeeksforGeeks: https://www.geeksforgeeks.org/linked-list-data-structure/ 
Microsoft Copilot: https://copilot.microsoft.com
Stack Overflow: https://stackoverflow.com/questions/18696531/cant-get-char-from-cin-get
*/
