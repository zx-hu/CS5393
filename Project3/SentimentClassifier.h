#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"

#include <unordered_map>

class SentimentClassifier{
    private:
        std::unordered_map<DSString, size_t> positiveWords;
        std::unordered_map<DSString, size_t> negativeWords;

        DSString processWord(DSString w);

    public:
        SentimentClassifier();
        void train(DSString& text, DSString& sentiment);
        int predict(DSString& text);
    
};

#endif
