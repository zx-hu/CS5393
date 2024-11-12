#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include "AVLTree.h"

class QueryProcessor{
    private:
        Node* wordMap;
        Node* personMap;
        Node* orgMap;
    public:
        QueryProcessor();
        void loadAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file);
        std::vector<std::pair<std::string,int> > search(std::string);

};

#endif
