/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: 
The objective of this code is to demonstrate the use and differences of static and dynamic arrays.
Both arrays can perform basic functions of inserting, deleting, searching for a specific element, and displaying elements.
While the arrays perform similar functions, the have their differences in implmenetations and backend.
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

//fixed size of the static array
#define SIZE 10

//static array methods

//insert an element into a static array
void insertStatic(int arr[], int element, int& size){
    if(size < SIZE){
        arr[size++] = element;
    }else{
        cout << "Static array is full" << endl;
    }
}

//delete an element from a static array
void deleteStatic(int arr[], int element, int& size){
    int index = -1;
    for(int i=0; i<size; i++){  //search the array
        if(arr[i] == element){  
            index = i;          //remember the index of the element to be deleted
            break;
        }
    }
    if(index != -1){            //if an element was found
        for(int i=index; i<size-1; i++){
            arr[i] = arr[i + 1];
        }
        size--;
    } else {
        cout << "Element not found in static array" << endl;
    }
}

//search for an element in a static array
int searchStatic(int arr[], int element, int size){
    for(int i=0; i<size; i++){
        if(arr[i] == element){
            return i;
        }
    }

    return -1;                      //element not found
}

//display the elements of a static array
void displayStatic(int arr[], int size){
    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//dynamic array functions

//insert an element into a dynamic array
void insertDynamic(int*& arr, int element, int& size){
    arr[size++] = element;
}

//delete an element from a dynamic array
void deleteDynamic(int*& arr, int element, int& size){
    int index = -1;
    for(int i=0; i<size; i++){
        if(arr[i] == element){
            index = i;
            break;
        }
    }
    if(index != -1){            //if an element is found
        for(int i=index; i<size-1; i++){
            arr[i] = arr[i + 1];
        }
        size--;
    } else {
        cout << "Element not found in dynamic array" << endl;
    }
}

//search for an element in a dynamic array
int searchDynamic(int*& arr, int element, int size){
    for(int i=0; i<size; i++){
        if(arr[i] == element){
            return i;
        }
    }

    return -1;          //element not found
}

//display the elements of dynamic array
void displayDynamic(int*& arr, int size){
    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){

    //static array created with fixed size
    int staticArr[SIZE]; 
    //variable to keep track of how many values in the array have been used             
    int staticSize = 0;

    //size of the dynamic array
    int dynamicSize = 0;
    //variable to keep track of how many values in the array have been used             
    int dynamicPosition = 0;
    cout << "Enter the size of the dynamic array: ";
    cin >> dynamicSize;                    //get user input for dynamic array size
    int* dynamicArr = new int[dynamicSize];  //dynamic array created

    //adding elements to the static array
    cout << "Add elements to the static array. Enter a non number to quit: ";
    int value;
    while(true){
        cin >> value;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        insertStatic(staticArr, value, staticSize);
    }

    //clearing cin to take in more input later
    cin.clear();
    cin.ignore();

    //adding elements to the dynamic array
    cout << "Add elements to the dynamic array. Enter a non number to quit: ";
    while(true){
        cin >> value;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        insertDynamic(dynamicArr, value, dynamicPosition);
    }

    //clearing cin to take in more input later
    cin.clear();
    cin.ignore();

    //display arrays
    cout << "Static array: ";
    displayStatic(staticArr, staticSize);
    cout << "Dynamic array: ";
    displayDynamic(dynamicArr, dynamicPosition);

    //searching in the static array
    cout << "Search for elements in the static array. Enter a non number to quit: ";
    int elementSearch;
    while(true){
        cin >> elementSearch;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        cout << elementSearch << " found at index " << searchStatic(staticArr, elementSearch, staticSize) << endl;
    }

    //clearing cin to take in more input later
    cin.clear();
    cin.ignore();

    //searching in the dynamic array
    cout << "Search for elements in the dynamic array. Enter a non number to quit: ";
    while(true){
        cin >> elementSearch;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        cout << elementSearch << " found at index " << searchDynamic(dynamicArr, elementSearch, dynamicPosition) << endl;
    }

    //clearing cin to take in more input later
    cin.clear();
    cin.ignore(); 

    //deleting elements in the static array
    cout << "Delete elements in the dynamic array. Enter a non number to quit: ";
    int elementDelete;
    while(true){
        cin >> elementDelete;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        deleteStatic(staticArr, elementDelete, staticSize);
    }

    //clearing cin to take in more input later
    cin.clear();
    cin.ignore();

    //deleting elements in the dynamic array
    cout << "Delete elements in the dynamic array. Enter a non number to quit: ";
    while(true){
        cin >> elementDelete;
        if(cin.fail()){
            cout << "Non-number entered." << endl;
            break;
        }
        deleteDynamic(dynamicArr, elementDelete, dynamicPosition);
    }

    //display arrays
    cout << "Static array: ";
    displayStatic(staticArr, staticSize);
    cout << "Dynamic array: ";
    displayDynamic(dynamicArr, dynamicPosition);

    //delete dynamic array to deallocate memory
    delete[] dynamicArr;

    return 0;
}

/*
References:
Microsoft Copilot: https://copilot.microsoft.com
University of Washington: https://courses.washington.edu/css342/zander/css332/array.html
*/
