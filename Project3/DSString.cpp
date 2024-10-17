#include "DSString.h"

#include <stdexcept>

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  

//default constructor
DSString::DSString(){
    data = nullptr;
    len = 0;
}

//constructor to convert a string
DSString::DSString(const char* str){
    size_t i =0;
    len = 0;
    while(str[i] != '\0'){
        len++;
        i++;
    }
    data = new char[len+1];
    for(size_t j = 0; j<len; j++){
        data[j] = str[j];
    }
    data[len] = '\0';
}

//copy constructor
DSString::DSString(const DSString& other){
    data = new char[other.len +1];
    len = other.len;
    for(size_t i = 0; i<len; i++){
        data[i] = other.data[i];
    }
    data[len] = '\0';   //add terminator to end?
}

//copy assignment operator
DSString& DSString::operator=(const DSString& other){
    delete[] data;
    len = other.len;
    data = new char[len+1];
    for(size_t i=0; i<len; i++){
        data[i] = other.data[i];
    }
    data[len] = '\0';
    return *this;
}

//destructor
DSString::~DSString(){
    delete[] data;
}

// returns the length of the string
size_t DSString::length() const{
    return len;
}

// returns a reference to the character at the given index
char& DSString::operator[](size_t position){
    if(position > len || position < 0){
        throw std::out_of_range("Index out of bounds");
    }
    return data[position];
}

DSString DSString::operator+(const DSString& other) const{
    DSString ret;
    ret.len = len + other.len;
    ret.data = new char[ret.len+1];

    for(size_t i = 0; i<len; i++){
        ret.data[i] = data[i];   //first string
    }
    for(size_t i = 0; i< other.len; i++){
        ret.data[i+len] = other.data[i];    //second string
    }
    ret.data[ret.len] = '\0';
    return ret;
}

bool DSString::operator==(const DSString& other) const{
    if(len != other.len){return false;} //check length

    for(size_t i=0; i<len; i++){
        if(data[i] != other.data[i]){
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString& other) const{
    size_t length = (len < other.len) ? len : other.len;//whichever one is shorter
    for(size_t i=0; i<length; i++){
        if(data[i] < other.data[i]){
            return true;
        }
        if(data[i] > other.data[i]){
            return false;
        }
    }
    return len < other.len;    //return the shorter string
}

DSString DSString::substring(size_t start, size_t numChars) const{
    if(start + numChars > len){throw std::out_of_range("Index out of bounds");}
    DSString ret;
    ret.len = numChars;
    ret.data = new char[ret.len+1];
    for(size_t i=0; i<numChars; i++){
        ret.data[i] = data[start+i];
    }
    ret.data[ret.len] = '\0';
    return ret;
}

DSString DSString::toLower() const{
    DSString ret(*this);
    for(size_t i=0; i<len; i++){
        if(data[i] > 64 && data[i] < 91){ //if char is an uppercase letter
            ret.data[i] = data[i] + 32;
        } 
    }
    return ret;
}

//idk if this works
const char* DSString::c_str() const{
    return data;
}

std::ostream& operator<<(std::ostream& os, const DSString& str){
    os << str.data;
    return os;
}

