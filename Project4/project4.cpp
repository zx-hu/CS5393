#include "DocumentParser.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h" 
#include "AVLTree.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidjson;

int main(){

    DocumentParser parser;
    //find a way to parse all the folders. or move it into 1 big folder
    parser.process_folder("archive/2018_01_112b52537b67659ad3609a234388c50a/");

    parser.saveAVLTrees("wordMap.txt", "personMap.txt", "orgMap.txt");
    
    std::cout << "Search: ";
    std::string input, word;
    std::cin >> input;

    std::stringstream ss(input);
    while(getline(ss, word, ' ')){
        if(word.find("ORG:")!= std::string::npos){      //if ORG:
            //docu has to contain this org
        }if(word.find("PERSON")!= std::string::npos){  //if PERSON:
            //docu has to contain this person
        }if(word.at(0) == '-'){                         //if - to exclude word
            //docu CANNOT contain this word
        }
    }

}
// me when coding kekw
