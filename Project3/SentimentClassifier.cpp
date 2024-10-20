#include "SentimentClassifier.h"
#include "DSString.h"

#include <iostream>
#include <unordered_map>


SentimentClassifier::SentimentClassifier(){
    positiveWords = std::unordered_map<DSString, int>();
    negativeWords = std::unordered_map<DSString, int>();
}

void SentimentClassifier::train(DSString& text, DSString& sentiment){
    char delimiter = ' ';
    DSString* words = text.split(delimiter);
    if(sentiment == "4"){   //if positive
        for(size_t i = 0; words[i].length() > 0; i++){
            positiveWords[words[i]]++;
        }
    }else if(sentiment == "0"){ //if negative
        for(size_t i = 0; words[i].length() > 0; i++){
            negativeWords[words[i]]++;
        }
    }
    delete[] words;
}

int SentimentClassifier::predict(DSString& text){
    int positive = 0;
    int negative = 0;
    char delimiter = ' ';
    DSString* words = text.split(delimiter);
    for(size_t i = 0; words[i].length() > 0; i++){
        auto posIt = positiveWords.find(words[i]);
        if(posIt != positiveWords.end()){
            positive += posIt->second;
        }
       auto negIt = negativeWords.find(words[i]);
        if(negIt != negativeWords.end()){
            negative += negIt->second;
        }
    }
    delete[] words;

    if(positive>negative){  //positive
        return 4;
    }           
    return 0;           
}

void SentimentClassifier::evaluatePredictions(){    //need to add args

}
