#include "SentimentClassifier.h"
#include "DSString.h"

#include <iostream>
#include <unordered_map>
#include <vector>

//constructor
SentimentClassifier::SentimentClassifier(){
    positiveWords = std::unordered_map<DSString, size_t>();
    negativeWords = std::unordered_map<DSString, size_t>();
}

//preprocesses the word to make it easier on the classifer
DSString SentimentClassifier::processWord(DSString w){
    w=w.toLower();

    //skip if word is too short
    if(w.length() < 3){
        return "";
    }

    //remove loose quotes
    if(w.substring(0, 1) == "\"" && w.substring(w.length()-2, 1) == "\""){
        w = w.substring(1, w.length()-2);
    }

    //stem for ed and ing
    if(w.substring(w.length()-2, 2) == "ed"){
        w = w.substring(0, w.length() - 2);
        
    }else if(w.substring(w.length()-3, 3) == "ing"){
        w = w.substring(0, w.length() - 3);
    }

    return w;
}

//trains the model by adding to the maps of positive and negative words
void SentimentClassifier::train(DSString& text, DSString& sentiment){
    char delimiter = ' ';
    std::vector<DSString> words = text.split(delimiter); 
    for(auto w : words){
        try{
            w = processWord(w);
            
            if(w.length() < 3) {
                continue;
            }
            if(sentiment == "4"){
                positiveWords[w]++;
            }else if(sentiment == "0"){
                negativeWords[w]++;
            }
        }catch(const std::exception& e){
            //std::cerr << "Error processing word: " << w << " - " << e.what() << "\n";
            continue;
        }
    }
}

//predicts the sentiment of a text based on the existing positive and negative word sets
int SentimentClassifier::predict(DSString& text){
    size_t positive = 0;
    size_t negative = 0;
    char delimiter = ' ';
    std::vector<DSString> words = text.split(delimiter);

    for(auto w : words){
        try{       
            w = processWord(w);

            if(w.length() < 3) {
                continue;
            }
            positive += positiveWords[w];  // This will add 0 if not found
            negative += negativeWords[w]; 

        }catch(const std::exception& e){
            //std::cerr << "Error processing word: " << w << " - " << e.what() << "\n";
            continue;
        }
    }

    if(positive>negative){  //positive
        return 4;
    }           
    return 0;           
}
