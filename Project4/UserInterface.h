#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "AVLTree.h"

class UserInterface{
    private:
        Node* wordMap;
        Node* personMap;
        Node* orgMap;
    public:
        UserInterface();
        DocumentParser parser;
        QueryProcessor processor;
        void interface();
        void saveAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file);
        void loadAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file);
        void displayArticle(std::string file_path);
        void printArticleText(std::string file_path);


};

#endif
