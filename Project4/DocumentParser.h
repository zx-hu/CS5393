#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include "AVLTree.h"

class DocumentParser{
    private:
    public:
        DocumentParser();
        void parseJsonFile(std::string file_path, Node*& wordMap, Node*& personMap, Node*& orgMap);
        void process_folder(std::string folder_path, Node*& wordMap, Node*& personMap, Node*& orgMap);

};

#endif
