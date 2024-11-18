#include "DocumentParser.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h" 
#include "include/rapidjson/istreamwrapper.h"
#include "AVLTree.h"
#include "porter2_stemmer-master/porter2_stemmer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <sstream>

//constructor
DocumentParser::DocumentParser(){
    wordMap = nullptr;
    personMap = nullptr;
    orgMap = nullptr;
}

std::string processWord(std::string word){
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    return word;
}

void DocumentParser::parseJsonFile(std::string file_path){
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

    if(document.HasMember("entities")){
        const rapidjson::Value& entity = document["entities"];

        //organizations
        if(entity.HasMember("organizations")){
            const rapidjson::Value& organizations = entity["organizations"];
            for (const auto& org : organizations.GetArray()) { 
                if (org.HasMember("name")) {
                    std::string name = org["name"].GetString();
                    //split name by space, insert each individual name
                    std::stringstream ss(name);
                    std::string word;
                    while(std::getline(ss, word, ' ')){
                    orgMap = insert(orgMap, name, file_path); 
                    }
                } 
            }
        }

        //persons
        if(entity.HasMember("persons")){
            const rapidjson::Value& persons = entity["persons"];
            for(const auto& person : persons.GetArray()){
                if(person.HasMember("name")){
                    std::string name = person["name"].GetString();
                    //split name by space, insert each individual name
                    std::stringstream ss(name);
                    std::string word;
                    while(std::getline(ss, word, ' ')){
                    personMap = insert(personMap, name, file_path); 
                    }
                }
            }
        }
    } 

    //text
    if(document.HasMember("text")){             //this is SO MUCH data to store
        std::string text = document["text"].GetString();
        //split string by space
        std::stringstream ss(text);
        std::string word;
        while(std::getline(ss, word, ' ')){
            word = processWord(word);
            //don't include the word if it's too short
            if(word.length() < 3){
                continue;
            }
            wordMap = insert(wordMap, word, file_path);
        }

    }
      
}

void DocumentParser::process_folder(std::string folder_path){
    for(const auto& file : std::filesystem::directory_iterator(folder_path)){
        if(file.path().extension() == ".json"){
            parseJsonFile(file.path().string());
        }
    }
}

void DocumentParser::saveAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file){
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
