#include "UserInterface.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/document.h"
#include <iostream>

UserInterface::UserInterface(){
    wordMap = nullptr;
    personMap = nullptr;
    orgMap = nullptr;
}

void UserInterface::interface(){
    while(true){
        std::cout << "Options:" << std::endl;
        std::cout << "1. Read from file path" << std::endl;
        std::cout << "2. Read from file" << std::endl;
        std::cout << "3. Write to file" << std::endl;
        std::cout << "4. Query" << std::endl;
        std::cout << "5. Quit" << std::endl;
        int option;
        int i = 0;
        try{
            std::cin >> option;
            if(std::cin.fail()){
                throw std::invalid_argument("Invalid input: Expected an integer."); 
            }
        }catch(const std::invalid_argument& e){
            //clear error flags and bad output
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
        std::string input, wordName, personName, orgName;
        std::vector<std::pair<std::string,int> > results;
        
        switch(option){
            case 1: //read from file path
                std::cout << "File path to read from: ";
                std::cin >> input;
                parser.process_folder(input, wordMap, personMap, orgMap);
                break;
            case 2: //read from file
                std::cout << "File name to read from" << std::endl;
                std::cout << "Word Map name: ";
                std::cin >> wordName;
                std::cout << "Person Map name: ";
                std::cin >> personName;
                std::cout << "Org Map name: ";
                std::cin >> orgName;

                loadAVLTrees(wordName, personName, orgName);

                break;
            case 3: //write to file
                std::cout << "File name to write to" << std::endl;
                std::cout << "Word Map name: ";
                std::cin >> wordName;
                std::cout << "Person Map name: ";
                std::cin >> personName;
                std::cout << "Org Map name: ";
                std::cin >> orgName;

                saveAVLTrees(wordName, personName, orgName);

                break;
            case 4: //query
                std::cout << "Search: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                results = processor.search(input, wordMap, personMap, orgMap);
                //get top 15 results
                while(i < 15 && i<results.size()){
                    std::cout << i+1 << ": ";
                    displayArticle(results[i].first);
                    i++;
                } 
                std::cout << "Select an article number to read: ";
                try{
                    std::cin >> option;
                    if(std::cin.fail()){
                        throw std::invalid_argument("Invalid input: Expected an integer."); 
                    }
                    if (option < 1 || option > 15 || option > results.size()) {
                        throw std::out_of_range("Index out of bounds.");
                    }
                    printArticleText(results[option-1].first);
                }catch(const std::invalid_argument& e){
                    //clear error flags and bad output
                    std::cin.clear();
                    std::cin.ignore();
                    std::cerr << "Error: " << e.what() << std::endl;
                    continue;
                }catch(const std::out_of_range& e){
                    //clear error flags and bad output
                    std::cin.clear();
                    std::cin.ignore();
                    std::cerr << "Error: " << e.what() << std::endl;
                    continue;
                }
                break;
            case 5: //quit
                break;
            default:
                //inputted a number but not one of the options
                std::cout << "Not a valid option" << std::endl;
                std::cin.ignore();
                std::cin.clear();
                continue;
        }
        
    }
}

void UserInterface::saveAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file){
    //save text
    std::ofstream wordMapFile(wordMap_file);
    if(wordMapFile.is_open()){
        saveTree(wordMap, wordMapFile); //save to file
        wordMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    //save persons
    std::ofstream personMapFile(personMap_file);
    if(personMapFile.is_open()){
        saveTree(personMap, personMapFile); //save to file
        personMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    //save orgs
    std::ofstream orgMapFile(orgMap_file);
    if(orgMapFile.is_open()){
        saveTree(orgMap, orgMapFile); //save to file
        orgMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }
    
}

void UserInterface::loadAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file){
    //load text
    std::ifstream wordMapFile(wordMap_file);
    if(wordMapFile.is_open()){
        wordMap = loadTree(wordMap, wordMapFile);
        wordMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    //load persons
    std::ifstream personMapFile(personMap_file);
    if(personMapFile.is_open()){
        personMap = loadTree(personMap, personMapFile);
        personMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    //load orgs
    std::ifstream orgMapFile(orgMap_file);
    if(orgMapFile.is_open()){
        orgMap = loadTree(orgMap, orgMapFile);
        orgMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }
} 

void UserInterface::displayArticle(std::string file_path){
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "Error opening file";
        return;
    }

    rapidjson::Document document;
    rapidjson::IStreamWrapper isw(file);  // Wrap the file stream
    document.ParseStream(isw); // Parse directly from the stream
    
    if (document.HasParseError()) { 
        std::cerr << "Error parsing JSON file: " << file_path << std::endl; 
        return; 
    }

    if (document.IsNull()) {
        std::cerr << "Document is null after parsing: " << file_path << std::endl;
        return;
    }
        
    //title
    if(document.HasMember("title")){
        std::string title = document["title"].GetString();  
        std::cout << "Title: " << title << std::endl;     
    }

    //publication???
    if(document.HasMember("publication")){
        std::string publication = document["publication"].GetString();
        std::cout << "Publication: " << publication << std::endl;     
    } 

    //date published
    if(document.HasMember("published")){         
        std::string date = document["published"].GetString();
        std::cout << "Date Published: " << date.substr(0,9) << std::endl;
    }

    std::cout << file_path << std::endl;

    std::cout << std::endl;
}

void UserInterface::printArticleText(std::string file_path){
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "Error opening file";
        return;
    }

    rapidjson::Document document;
    rapidjson::IStreamWrapper isw(file);  // Wrap the file stream
    document.ParseStream(isw); // Parse directly from the stream
    
    if (document.HasParseError()) { 
        std::cerr << "Error parsing JSON file: " << file_path << std::endl; 
        return; 
    }

    if (document.IsNull()) {
        std::cerr << "Document is null after parsing: " << file_path << std::endl;
        return;
    }

    //print text
    if(document.HasMember("text")){
        std::string text = document["text"].GetString();
        std::cout << text << std::endl;
    }
}