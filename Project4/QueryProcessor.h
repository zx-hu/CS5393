#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include "AVLTree.h"

class QueryProcessor{
    private:
    public:
        QueryProcessor();
        std::vector<std::pair<std::string,int> > search(std::string, Node* wordMap, Node* personMap, Node* orgMap);

};

#endif
