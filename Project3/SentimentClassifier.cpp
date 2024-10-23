#include "SentimentClassifier.h"
#include "DSString.h"

#include <iostream>
#include <unordered_map>
#include <vector>


SentimentClassifier::SentimentClassifier(){
    positiveWords = std::unordered_map<DSString, size_t>();
    negativeWords = std::unordered_map<DSString, size_t>();
}

void SentimentClassifier::train(DSString& text, DSString& sentiment){
    char delimiter = ' ';
    std::vector<DSString> words = text.split(delimiter);            //fix this
    for(auto w : words){
        try{
            //skip if word is too short
            if(w.length() < 3){
                continue;
            }
            
            //stem for ed and ing
            if(w.toLower().substring(w.length()-2, 2) == "ed"){
                w = w.substring(0, w.length() - 2);
                
            }else if(w.toLower().substring(w.length()-3, 3) == "ing"){
                w = w.substring(0, w.length() - 3);
            }

            if(sentiment == "4"){
                positiveWords[w.toLower()]++;
            }else if(sentiment == "0"){
                negativeWords[w.toLower()]++;
            }
        }catch(const std::exception& e){
            //std::cerr << "Error processing word: " << w << " - " << e.what() << "\n";
            continue;
        }
    }
}

int SentimentClassifier::predict(DSString& text){
    size_t positive = 0;
    size_t negative = 0;
    char delimiter = ' ';
    std::vector<DSString> words = text.split(delimiter);

    for(auto w : words){
        try{
            auto posIt = positiveWords.find(w.toLower());
            if(posIt != positiveWords.end()){
                positive += posIt->second;
            }
            auto negIt = negativeWords.find(w.toLower());
            if(negIt != negativeWords.end()){
                negative += negIt->second;
            }
        }catch(const std::exception& e){
            std::cerr << "Error processing word: " << w << " - " << e.what() << "\n";
            continue;
        }
    }

    if(positive>negative){  //positive
        return 4;
    }           
    return 0;           
}
