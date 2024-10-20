#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"

#include <unordered_map>

class SentimentClassifier{
    private:
        std::unordered_map<DSString, int> positiveWords;
        std::unordered_map<DSString, int> negativeWords;

    public:
        SentimentClassifier();
        void train(DSString& text, DSString& sentiment);
        int predict(DSString& text);
        void evaluatePredictions(); //what args?
    
};

#endif