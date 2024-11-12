#include "QueryProcessor.h"
#include <iostream>
#include <sstream>

QueryProcessor::QueryProcessor(){
    wordMap = nullptr;
    personMap = nullptr;
    orgMap = nullptr;
}

// Comparator to sort pairs by value in descending order
bool compareByValue(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second; // Greater to less
}

void mergeMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    for(const auto& pair : map2){
        map1[pair.first] += pair.second;  
    }
}

void mergeAndRemoveMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    for(const auto& pair : map2){
        map1.erase(pair.first);
    }
}

void mergeAndSumMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    for(const auto& pair : map2){
        const std::string& key = pair.first;

        auto it = map1.find(key);
        if(it != map1.end()){
            map1[key] += pair.second;
        }
    }
}


void QueryProcessor::loadAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file){
    std::ifstream wordMapFile(wordMap_file);
    if(wordMapFile.is_open()){
        wordMap = loadTree(wordMap, wordMapFile);
        wordMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    std::ifstream personMapFile(personMap_file);
    if(personMapFile.is_open()){
        personMap = loadTree(personMap, personMapFile);
        personMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }

    std::ifstream orgMapFile(orgMap_file);
    if(orgMapFile.is_open()){
        orgMap = loadTree(orgMap, orgMapFile);
        orgMapFile.close();
    }else{
        std::cerr << "Failed to open file";
    }
} 

std::vector<std::pair<std::string,int> > QueryProcessor::search(std::string input){
    std::stringstream ss(input);
    std::string word;
    std::unordered_map<std::string, int> results;
    std::unordered_map<std::string, int> removeResults;
    while(getline(ss, word, ' ')){
        std::unordered_map<std::string, int> single_result;
        if(word.at(0) == '-'){                         //if - to exclude word
            //can a search have -ORG: ???
            //docu CANNOT contain this word
            word = word.substr(1); //cut off -
            single_result = find(wordMap, word);
            mergeMaps(removeResults, single_result);
            continue;
        }else if(word.find("ORG:")!= std::string::npos){      //if ORG:
            //docu has to contain this org
            word = word.substr(4); //cut off ORG:
            single_result = find(orgMap, word);
            
        }else if(word.find("PERSON:")!= std::string::npos){  //if PERSON:
            //docu has to contain this person
            word = word.substr(7); //cut off PERSON:
            single_result = find(personMap, word);

        }else{
            //PROCESSWORD!!!
            single_result = find(wordMap, word);
        }
        mergeAndSumMaps(results, single_result);
    }
    mergeAndRemoveMaps(results, removeResults);
    //put into vector for sorting
    std::vector<std::pair<std::string,int> >ret(results.begin(), results.end());

    std::sort(ret.begin(), ret.end(), compareByValue);

    return ret;

}