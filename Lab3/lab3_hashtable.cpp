/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a hash table
It will be used to store a set of Name and Phone Number pairs.
The hash table demonstrates basic operations like insert, delete, and search key.
*/

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct hashNode{
    string key = "";
    string value = "";
    hashNode* next = nullptr;

    hashNode(string k, string v){
        key = k;
        value = v;
    }

    ~hashNode(){
        delete next;
    }
};

struct hashTable{
    hashNode** table;
    int size;
    int numElements = 0;

    ~hashTable(){
        for(int i=0; i<size; i++){
            hashNode* current = table[i];
            while(current != nullptr){
                hashNode* del = current;
                current = current->next;
                delete del;
            }
        }
        delete[] table;
    }
};

//initialize hashtable
hashTable* createTable(int size){
    hashTable* newTable = new hashTable;
    newTable->table = new hashNode*[size];
    newTable->size = size;
    for(int i=0; i<size; i++){
        newTable->table[i] = nullptr;
    }
    return newTable;
}

//Converts the key to some index
int hashFunction(string& key, int tableSize){
    int hash = 0;
    for(int i=0; i<key.length(); i++){
        hash+=key.at(i) * i;
    }
    return hash % tableSize;
}

//resize table if too many pairs are added
void resizeTable(hashTable* table) {
    int newSize = table->size * 2;
    hashNode** newTable = new hashNode*[newSize];
    for (int i = 0; i < newSize; ++i) {
        newTable[i] = nullptr;
    }

    // Rehash all existing nodes
    for (int i = 0; i < table->size; ++i) {
        hashNode* current = table->table[i];
        while (current != nullptr) {
            hashNode* next = current->next;
            int newIndex = hashFunction(current->key, newSize);
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = next;
        }
    }

    delete[] table->table;
    table->table = newTable;
    table->size = newSize;
}

void insert(hashTable* table, string key, string value){
    int index = hashFunction(key, table->size);
    table->numElements++;
    if(table->numElements > table->size){
        resizeTable(table);
    }
    hashNode* newNode = new hashNode(key, value);
    if(table->table[index] == nullptr){
        table->table[index] = newNode;
    }else{
        hashNode* current = table->table[index];
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
}

string search(hashTable* table, string key){
    int index = hashFunction(key, table->size);
    hashNode* current = table->table[index];
    while(current != nullptr){
        if(current->key == key){
            return current->value;
        }
        current = current->next;
    }
    return "Key " + key + " not found \n";
}

void remove(hashTable* table, string key){
    int index = hashFunction(key, table->size);
    hashNode* current = table->table[index];
    hashNode* prev = nullptr;
    if(current == nullptr){     //key not found
        cout << "Key " << key << " not found" << endl;
        return;
    }   
    while(current != nullptr){
        if(current->key == key){    //key found
            table->numElements--;
            if(prev == nullptr){    //node to be deleted is first in the linked list
                table->table[index] = current->next;
                delete current;
                current = table->table[index];
            }else{                      //node to be deleted is NOT first in the linked list
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }else{                      //progress to next node
            prev = current;
            current = current->next;
        }
        
    }
    cout << "Key " << key << " was deleted" << endl;
}

void printTable(hashTable* table){
    for(int i=0; i<table->size; i++){
        hashNode* current = table->table[i];
        if(current == nullptr){continue;}
        cout << "Bucket " << i << ": ";
        
        while(current != nullptr){
            cout << "(" << current->key << ", " << current->value << ") -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
    cout << endl;
}

int main(){

     //import csv
    ifstream file("Lab3_Problem2_DSC++.csv");

    //make sure file opened properly
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    int size;
    cout << "Size of dataset? "; 
    cin >> size;

    hashTable* table = createTable(size);

    string name, number, line;
    char delimiter = ',';

    while(getline(file, line, '(')){ //find the start of the name
        
        getline(file, line, ')'); //find the end of the phone
        stringstream ss(line);      //put input into a stringstream
        
        getline(ss, name, delimiter);
        getline(ss, number, delimiter);
        //get rid of the quotes (first and last character)
        name = name.substr(1, name.size()-2);
        number = number.substr(2, number.size()-3);

        if(name == ""){continue;}

        //insert into hash table
        insert(table, name, number);
    }

    printTable(table);

    // search for Liam
    cout << "List of Liams" << endl;
    string nameSearch = "Liam";
    for(int i=0; i<table->size; i++){
        hashNode* node = table->table[i];
        while (node != nullptr){
            stringstream ss(node->key);
            string firstName;
            ss >> firstName;
            if(firstName == nameSearch){
                cout << "(" << node->key << ", " << node->value << ") "; 
            }
            node = node->next;
        }
    }
    cout << endl << endl;   //formatting

    remove(table, "Isabella Anderson");
    printTable(table);

    cout << search(table, "Shaibal Chakrabarty");
    cout << search(table, "Lucas Li");

    insert(table, "Shaibal Chakrabarty", "214-768-2000");
    insert(table, "Lucas Li", "469-555-1212");
    printTable(table);

    //close the file
    file.close();

    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/
Microsoft Copilot: https://copilot.microsoft.com
*/
