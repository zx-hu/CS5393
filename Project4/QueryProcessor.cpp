#include "QueryProcessor.h"
#include "porter2_stemmer-master/porter2_stemmer.h"
#include <iostream>
#include <unordered_set>
#include <sstream>

QueryProcessor::QueryProcessor(){
}

// Comparator to sort pairs by value in descending order
bool compareByValue(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second; // Greater to less
}

//outer join maps
void mergeMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    for(const auto& pair : map2){
        map1[pair.first] += pair.second;  
    }
}

//remove map2 from map1
void mergeAndRemoveMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    for(const auto& pair : map2){
        map1.erase(pair.first);
    }
}

//inner join maps
void mergeAndSumMaps(std::unordered_map<std::string, int>& map1, std::unordered_map<std::string, int>& map2){
    std::unordered_set<std::string> keys2;
    for(const auto& pair : map2){
        keys2.insert(pair.first);
        
        const std::string& key = pair.first;
        auto it = map2.find(key);
        if(it != map1.end()){
            map1[key] += pair.second;
        }
    }

    // Remove keys from map1 that are not in map2
    for (auto it = map1.begin(); it != map1.end();) {
        if (keys2.find(it->first) == keys2.end()) {
            it = map1.erase(it);  // Erase and move to the next item
        } else {
            it++;
        }
    }
}


std::vector<std::pair<std::string,int> > QueryProcessor::search(std::string input, Node* wordMap, Node* personMap, Node* orgMap){
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
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            if(word.length()<3){
                continue;
            }
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
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            if(word.length()<3){
                continue;
            }
            single_result = find(wordMap, word);
        }
        if(results.empty()){    //for first word
            mergeMaps(results, single_result);
        }else{                  //for every other iteration
            mergeAndSumMaps(results, single_result);
        }
    }
    //remove search results with the -
    mergeAndRemoveMaps(results, removeResults);
    //put into vector for sorting
    std::vector<std::pair<std::string,int> >ret(results.begin(), results.end());
    //sort
    std::sort(ret.begin(), ret.end(), compareByValue);

    return ret;

}
