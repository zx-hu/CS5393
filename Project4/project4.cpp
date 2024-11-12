#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h" 
#include "AVLTree.h"

#include <iostream>

using namespace rapidjson;

int main(){

    DocumentParser parser;
    QueryProcessor processor;
    //find a way to parse all the folders. or move it into 1 big folder
    parser.process_folder("archive/2018_01_112b52537b67659ad3609a234388c50a/");

    parser.saveAVLTrees("wordMap.txt", "personMap.txt", "orgMap.txt");
    processor.loadAVLTrees("wordMap.txt", "personMap.txt", "orgMap.txt");

    std::cout << "Search: ";
    std::string input;
    std::cin >> input;

    std::vector<std::pair<std::string,int> > results = processor.search(input);
    int i =0;
    while(i < 15 && i<results.size()){
        std::cout << i << ": " << results[i].first << std::endl;
        i++;
    }

    return 0;
}
// me when coding kekw
