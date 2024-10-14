/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a library management system that utilizes various data structures.
The various data structures demonstrates the pros and cons of each data structure and the best situation to use it in.
It also shows a more real world application of the individual data structures we have learned so far.
*/

#include <iostream>
#include <unordered_map>    //hash table for storing books
#include <map>              //BST for storing books
#include <stack>            //stack for tracking recently borrowed books
#include <fstream>          //both for managing csv as input
#include <sstream>
using namespace std;

class Book{
    private:
        int ISBN;
        string title;
        string author;
        double price;
        int quantity;
        int lentOut = 0;
        
    public:
        //default constructor
        Book(){
            ISBN = 0;
            title = "";
            author = "";
            price = 0;
            quantity = 0;
        }

        //constructor
        Book(int bookISBN, string bookTitle, string bookAuthor, double bookPrice, int bookQuantity){
            ISBN = bookISBN;
            title = bookTitle;
            author = bookAuthor;
            price = bookPrice;
            quantity = bookQuantity;
        }

        bool reserveBook(){
            if(lentOut >= quantity){
                cout << "No more copies to reserve" << endl;
                return false;
            }
            lentOut++;
            return true;
        }

        void returnBook(){
            if(lentOut <= 0){
                cout << "This is not our book" << endl;
                return;
            }
            lentOut--;
        }
        
        void print(){
            cout << "ISBN: " << ISBN << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Price: $" << price << endl;
            //cout << "Quantity: " << quantity << endl;
            cout << "Availability: " << quantity-lentOut << "/" << quantity << endl;
        }

};

//node for queue
struct Node {
    Book data;
    Node* next;
    Node(Book book){
        data = book;
        next = nullptr;
    }
};

class Queue{
    private:
        Node* front;
        Node* rear;
        int size;

    public:

        //constructor
        Queue(){
            front = nullptr;
            rear = nullptr;
            size = 0;
        }

        //add an element to the back of the queue
        bool enqueue(Book& book){
            if(!book.reserveBook()){
                return false;
            }
            Node* newNode = new Node(book);
            if (front == nullptr) {
                front = rear = newNode;
                size++;
                return true;
            }  
            rear->next = newNode;
            rear = newNode;  
            rear->next = nullptr;
            size++;
            return true;
        }

        //remove and return the front element of the queue
        Book dequeue(){
            if(front == nullptr){
                throw out_of_range("Queue is empty");
            }
            size--;
            Book ret = front->data;
            Node* del = front;
            front = front->next;

            //if there was only one element
            if (front == nullptr) {
                rear = nullptr;
            }

            ret.returnBook();

            delete del;
            return ret;
        }

        //return the front element without removing it
        Book peek(){
            if(front == nullptr){
                throw out_of_range("Queue is empty");
            }
            return front->data;
        }

        //check if the queue is empty
        bool isEmpty(){
            return front == nullptr;
        }
        
        void print(){
            Node* print = front;
            while(print != nullptr){
                print->data.print();
                cout << endl;
                print = print->next;
            }
            delete print;
            return;
        }

        //return the number of elements in the queue
        int getSize(){
            return size;
        } 

        //destuctor
        ~Queue(){
            while (front != nullptr) {
                Node* temp = front;
                front = front->next;
                delete temp;
            }
            rear = nullptr;
        }

};

int main(){

    //import csv
    ifstream bookFile("Book Dataset.csv");

    //make sure file opened properly
    if (!bookFile.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    
    unordered_map<int, Book> bookTable;     //hash table to store books by ISBN
    map<string, Book> bookBST;              //BST to store books by title 
    Queue bookQueue;                        //queue to reserve books
    stack<Book> bookStack;                  //stack to track recently borrowed books

    //variables to take data from csv
    int ISBN, quantity;
    string title, author;
    double price;

    string line;
    
    //clear top line with header
    getline(bookFile, line);

    //while there is still data
    while(getline(bookFile, line)){
        stringstream ss(line);      //put string into a stringstream
        
        //temp variables for casting
        string tempISBN, tempPrice, tempQuantity;
        
        //putting data into variables
        getline(ss, tempISBN, ',');
        stringstream(tempISBN) >> ISBN;

        getline(ss, title, ',');
        getline(ss, author, ',');

        getline(ss, tempPrice, ',');
        stringstream(tempPrice) >> price;

        getline(ss, tempQuantity, ',');
        stringstream(tempQuantity) >> quantity;

        //create book with given variables
        Book book(ISBN, title, author, price, quantity);

        bookTable[ISBN] = book; //insert book into hash table
        bookBST[title] = book;  //insert book into BST
    }
    
    //randomly reserve half the books
    srand (time(NULL));
    int random;
    int count = 0;

    cout << "Reserving 10 random books" << endl;
    
    while(count < 10){
        for (auto& pair: bookBST){
            random = rand() % 2 + 1;
            if(random % 2 == 0){
                if(bookQueue.enqueue(pair.second)){
                    bookStack.push(pair.second);
                    count++;
                }
            }
            if(count >=10){
                break;
            }
        }
    }
    
    //display books
    cout << "Books in the queue" << endl;
    bookQueue.print();
    
    //randomly reserve 2 of the same book
    cout << "Reserving 2 of the same book" << endl;
    
    int randomIndex = rand() % bookTable.size();    //generating a random index

    auto it = bookBST.begin();        
    advance(it, randomIndex);               //iterate to the random index

    //reserve book twice
    bookQueue.enqueue(it->second);
    bookQueue.enqueue(it->second);
    bookStack.push(it->second);
    bookStack.push(it->second);

    //display availability
    it->second.print();

    cout << endl;           //formatting
    
    //return book and lend it out again
    bookStack.pop();        
    bookStack.push(it->second);     //this realisitically does nothing.
    
    //search for book
    string bookTitle;
    cout << "Search for a book based on its title: ";
    getline(cin, bookTitle);

    auto iterator = bookBST.find(bookTitle);        //.find uses a binary search
    if(iterator != bookBST.end()) {
        iterator->second.print();
    }else{
        cout << "Book not found" << endl;
    }

    //close the file
    bookFile.close();

    return 0;
}

/*
References:
Cplusplus: https://cplusplus.com/forum/beginner/182904/
GeeksforGeeks: https://www.geeksforgeeks.org/stack-in-cpp-stl/
               https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
Microsoft Copilot: https://copilot.microsoft.com
*/
