/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is implement a trie using an unordered map.
It will be used to store words in character segments.
The trie demonstrates basic operations like insert, search, and finding specific categories of words.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;

struct TrieNode{
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode(){
        isEndOfWord = false;
    }

};

class Trie{
    private:
        TrieNode* root;

        //helper function
        void deleteNode(TrieNode* node){
            for(auto child : node->children){
                deleteNode(child.second);
            }
            delete node;
        }

    public:
        Trie(){
            root = new TrieNode();
        }

        ~Trie(){
            deleteNode(root);
        }

        void insert(string& word){
            TrieNode* current = root;
            for(char c : word){
                if (current->children.find(c) == current->children.end()){
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            current->isEndOfWord = true;
            cout << word << " successfully inserted" << endl;
        }

        bool search(string word){
            TrieNode* current = root;
            for(char c : word){
                if(current->children.find(c) == current->children.end()){
                    cout << word << " not found" << endl;
                    return false;
                }
                current = current->children[c];
            }
            
            if(current->isEndOfWord){
                cout << word << " found" << endl;
                return true;
            }
            cout << word << " not found as complete word" << endl;
            return false;
        }

        vector<string> startsWith(string prefix){
            TrieNode* current = root;
            for(char c : prefix){
                if(current->children.find(c) == current->children.end()){
                    return {}; //return empty if prefix not found
                }
                current = current->children[c];
            }
            //what makes this different than findwordswithprefix??

            return {}; //placeholder
        }

        vector<string> findWordsWithPrefix(string prefix){
            vector<string> ret;
            TrieNode* current = root;
            for(char c : prefix){
                if(current->children.find(c) == current->children.end()){
                    cout << "No words with prefix " << prefix << " found";
                    return {};  //return empty if prefix not found
                }
                current = current->children[c];
            }
            //go down all nodes and add words ones find end of word
            vector<pair<TrieNode*,string> > stack;
            stack.push_back({current,prefix});
            while(!stack.empty()){
                TrieNode* node = stack.back().first;
                string currentPrefix = stack.back().second;
                stack.pop_back();
                if(node->isEndOfWord){
                    ret.push_back(currentPrefix);
                }
                for(auto child : node->children){
                    stack.push_back({child.second, currentPrefix + child.first});
                }
            }
            return ret;
        }

        void dfsShort(TrieNode* node, string currWord, vector<string>& ret, int length){
            if(currWord.length() > length){
                return;
            }
            if(node->isEndOfWord){
                ret.push_back(currWord);
            }

            for(auto child : node->children){
                dfsShort(child.second, currWord + child.first, ret, length);
            }
        }

        vector<string> findShortWords(int length){
            vector<string> ret;
            dfsShort(root, "", ret, length);
            return ret;
        }

        void dfsHyphen(TrieNode* node, string currWord, vector<string>& ret){
            if(node->isEndOfWord && currWord.find('-') != string::npos){
                ret.push_back(currWord);
            }
            for(auto& child : node->children){
                dfsHyphen(child.second, currWord + child.first, ret);
            }
        }

        vector<string> findWordsWithHyphen(){
            vector<string> ret;
            dfsHyphen(root, "", ret);
            return ret;

        }

        void dfsNumber(TrieNode* node, string currWord, vector<string>& ret){
            if(node->isEndOfWord && currWord.find_first_of("0123456789") != string::npos){//&& has num
                ret.push_back(currWord);
            }

            for(auto& child : node->children){
                dfsNumber(child.second, currWord + child.first, ret);
            }

        }

        vector<string> findWordsWithNumbers(){
            vector<string> ret;
            dfsNumber(root, "", ret);
            return ret;
        }

        bool hasMixedCase(string word){
            bool hasLower = false;
            bool hasUpper = false;
            for(char c : word){
                if(islower(c)){
                    hasLower = true;
                }if(isupper(c)){
                    hasUpper = true;
                }if(hasUpper && hasLower){
                    return true;
                }
            }
            return false;
        }

        void dfsMixedCase(TrieNode* node, string currWord, vector<string>& ret){
            if(node->isEndOfWord && hasMixedCase(currWord)){
                ret.push_back(currWord);
            }
            for(auto child : node->children){
                dfsMixedCase(child.second, currWord + child.first, ret);
            }
        }

        vector<string> findMixedCases(){
            vector<string> ret;
            dfsMixedCase(root, "", ret);
            return ret;
        }

};

void print(vector<string> data){
    for(string s : data){
        cout << s << " ";
    }
    cout << endl;
};

int main(){

    Trie trie;

    ifstream input("Lab5_dictionary-dataset.txt");

    string line;
    while(getline(input, line)){
        if(line == "" || line.at(0) == '#'){ //skip comment lines
            continue;
        }
        trie.insert(line);
    }

    cout << "Input words to search. Type 0 to quit ";
    string in;
    cin >> in;
    while(in != "0"){
        trie.search(in);
        cin >> in;
    }

    vector<string> data;
    cout << "Input prefixes to search. Type 0 to quit ";
    cin >> in;
    while(in != "0"){
        cout << "Words with prefix " << in << ": ";
        data = trie.findWordsWithPrefix(in);
        print(data);
        cin >> in;
    }

    cout << "Maximum length of short words: ";
    int length;
    while(!(cin >> length) || length <1){
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore();
    }
    cout << "Short words: ";
    data = trie.findShortWords(length);
    print(data);

    cout << "Words with hyphens: ";
    data = trie.findWordsWithHyphen();
    print(data);

    cout << "Words with numbers: ";
    data = trie.findWordsWithNumbers();
    print(data);

    cout << "Mixed case words: ";
    data = trie.findMixedCases();
    print(data);

    return 0;
}

/*
References:
GeeksforGeeks: https://www.geeksforgeeks.org/trie-insert-and-search/
Microsoft Copilot: https://copilot.microsoft.com
*/
