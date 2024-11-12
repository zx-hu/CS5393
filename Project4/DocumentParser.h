#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include "AVLTree.h"

class DocumentParser{
    private:
        Node* wordMap;
        Node* personMap;
        Node* orgMap;
        
        std::string processWord(std::string word);
    public:
        DocumentParser();
        void parseJsonFile(std::string file_path);
        void process_folder(std::string folder_path);
        void saveAVLTrees(std::string wordMap_file, std::string personMap_file, std::string orgMap_file);
};

#endif
