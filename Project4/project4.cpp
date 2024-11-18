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
    //parser.process_folder("archive/2018_01_112b52537b67659ad3609a234388c50a/");

    //parser.saveAVLTrees("wordMap.txt", "personMap.txt", "orgMap.txt");
    //processor.loadAVLTrees("wordMap.txt", "personMap.txt", "orgMap.txt");

    bool searching = true;
    while(searching){
        std::cout << "Options:" << std::endl;
        std::cout << "1. Read from file path" << std::endl;
        std::cout << "2. Read from file" << std::endl;
        std::cout << "3. Write to file" << std::endl;
        std::cout << "4. Query" << std::endl;
        std::cout << "5. Quit" << std::endl;
        int option, i;
        try{
            std::cin >> option;
            if(std::cin.fail()){
                throw std::invalid_argument("Invalid input: Expected an integer."); 
            }
        }catch(const std::invalid_argument& e){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
        std::string input, wordName, personName, orgName;
        std::vector<std::pair<std::string,int> > results;
        
        switch(option){
            case 1:
                std::cout << "File path to read from: ";
                std::cin >> input;
                parser.process_folder(input);
                break;
            case 2:
                std::cout << "File name to read from" << std::endl;
                std::cout << "Word Map name: ";
                std::cin >> wordName;
                std::cout << "Person Map name: ";
                std::cin >> personName;
                std::cout << "Org Map name: ";
                std::cin >> orgName;

                processor.loadAVLTrees(wordName, personName, orgName);

                break;
            case 3:
                std::cout << "File name to write to" << std::endl;
                std::cout << "Word Map name: ";
                std::cin >> wordName;
                std::cout << "Person Map name: ";
                std::cin >> personName;
                std::cout << "Org Map name: ";
                std::cin >> orgName;

                parser.saveAVLTrees(wordName, personName, orgName);

                break;
            case 4: 
                std::cout << "Search: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                results = processor.search(input);
                //get top 15 results
                while(i < 15 && i<results.size()){
                    std::cout << i << ": " << results[i].first << " @ " << results[i].second << std::endl;
                    i++;
                } 
                break;  
            case 5:
                searching = false;
                break;
            default:
                std::cout << "Not a valid option" << std::endl;
                std::cin.ignore();
                std::cin.clear();
                continue;
        }
        
    }

    return 0;
}
// me when coding kekw
