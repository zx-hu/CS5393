/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: 
The objective of this code is to simulate a basic spreadsheet using a 2D array.
The spreadsheet can take in data, calculate the sum and average of individual rows and columns, and the minimum and maximum of the whole array.
The spreadsheet can also search for the position, given a specific element.
*/

#include <iostream>
using namespace std;

//input data into every cell
void inputData(int** arr, int row, int col){
    cout << "Enter values for the spreadsheet: ";
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cin >> arr[i][j];
        }
    }
}

//find the total value in the row of the user's choice
int sumRow(int** arr, int row, int col){
    int sum = 0;
    for(int i=0; i<col; i++){
        sum+= arr[row-1][i];
    }
    return sum;
}

//find the average value in the row of the user's choice
double avgRow(int** arr, int row, int col){
    double sum = 0;
    for(int i=0; i<col; i++){
        sum+= arr[row-1][i];
    }
    return sum/col;
}

//find the total value in the column of the user's choice
int sumCol(int** arr, int row, int col){
    int sum = 0;
    for(int i=0; i<row; i++){
        sum+= arr[i][col-1];
    }
    return sum;
}

//find the average value in the column of the user's choice
double avgCol(int** arr, int row, int col){
    double sum = 0;
    for(int i=0; i<row; i++){
        sum+= arr[i][col-1];
    }
    return sum/row;
}

//find the maximum value in the array
int findMax(int** arr, int row, int col){
    int max = arr[0][0];
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(arr[i][j] > max){
                max = arr[i][j];
            }
        }
    }
    return max;
}

//find the minimum value in the array
int findMin(int** arr, int row, int col){
    int min = arr[0][0];
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(arr[i][j] < min){
                min = arr[i][j];
            }
        }
    }
    return min;
}

//search for the position of a given element
void search(int** arr, int row, int col, int element){
    bool found = false;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(arr[i][j] == element){
                cout << "Element found in row " << i+1 << " column " << j+1 << endl;
                found = true;
            }
        }
    }
    if(!found){
        cout << "Element not found" << endl;   //element not found
    }
}

//print out the 2d array
void printSheet(int** arr, int row, int col){
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    
    //ask user for size of 2d array
    int row, col;
    cout << "How many rows? ";
    cin >> row;
    cout << "How many cols? ";
    cin >> col;

    //create the 2d array
    int** spreadsheet = new int*[row];
    for(int i=0; i<row; i++){
        spreadsheet[i] = new int[col]; 
    }

    //input data into the 2d array
    inputData(spreadsheet, row, col);

    //display 2d array
    printSheet(spreadsheet, row, col);

    //finding the max and min of the array
    cout << "Max of your array: " << findMax(spreadsheet, row, col) << endl;
    cout << "Min of your array: " << findMin(spreadsheet, row, col) << endl;

    //get the sum and average of a row
    int userRow;
    //make sure the value is within bounds
    cout << "Pick a row to get the sum and average of: ";
    cin >> userRow;
    while (userRow > row){
        cout << "Invalid row" << endl;
        cout << "Pick a row to get the sum and average of: ";
        cin >> userRow;
    }
    cout << "Sum of " << userRow << " : " << sumRow(spreadsheet, userRow, col) << endl;
    cout << "Average of " << userRow << " : " << avgRow(spreadsheet, userRow, col) << endl;

    ////get the sum and average of a col
    int userCol;
    //make sure the value is within bounds
    cout << "Pick a col to get the sum and average of: ";
    cin >> userCol;
    while (userCol > col){
        cout << "Invalid column" << endl;
        cout << "Pick a col to get the sum and average of: ";
        cin >> userCol;
    }
    cout << "Sum of " << userCol << " : " << sumCol(spreadsheet, row, userCol) << endl;
    cout << "Average of " << userCol << " : " << avgCol(spreadsheet, row, userCol) << endl;

    //search for an element in the array
    int element;
    cout << "Pick an element to search for: ";
    cin >> element;
    search(spreadsheet, row, col, element);

    //clean up memory
    for(int i=0; i<row; i++){
        delete[] spreadsheet[i];
    }
    delete[] spreadsheet;

    return 0;
}

/*
References:
Microsoft Copilot: https://copilot.microsoft.com
Stack Overflow: https://stackoverflow.com/questions/24165572/casting-int-to-the-pointer-to-a-two-dimensional-array-of-integers-with-fixed
*/
