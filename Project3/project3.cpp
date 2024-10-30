/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to classify tweets to determine their sentiment.
This code has its own string class and trains its own model to label tweets.
It also processes training and testing input data, and outputs testing and accuracy data.
*/

#include "SentimentClassifier.h"
#include "DSString.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

int main(){
    SentimentClassifier classifier;

    //train the classifer
    string line;
    ifstream trainingData("train_dataset_20k.csv");

    if (!trainingData.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    getline(trainingData, line);    //toss the header line

    string sentiment, id, date, query, user, tweet;
    while(getline(trainingData,line)){
        stringstream ss (line);
        
        //separate data by ,
        getline(ss, sentiment, ',');
        DSString DSsentiment(sentiment.c_str());    //turn into DSString
        getline(ss, id, ',');
        DSString DSid(id.c_str());
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);
        DSString DStweet(tweet.c_str());

        classifier.train(DStweet, DSsentiment);
    }  

    trainingData.close();

    //run classifier on test data
    ofstream outFile("results.csv");
    ifstream testingData("test_dataset_10k.csv");

    if (!testingData.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    vector<pair<DSString, int> > predictions;

    getline(testingData, line);    //toss the header line
    while(getline(testingData, line)){
        stringstream ss (line);

        getline(ss, id, ',');
        DSString DSid(id.c_str());
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);
        DSString DStweet(tweet.c_str());

        //make prediction, add it to output file
        int prediction = classifier.predict(DStweet);
        outFile << prediction << ", " << DSid << endl;
        predictions.push_back(make_pair(DSid, prediction));
        
    }  
    outFile.close();
    testingData.close();

    //compare results to find accuracy
    ifstream answerFile("test_dataset_sentiment_10k.csv");
    if (!answerFile.is_open()) {
        cerr << "Error opening answer file" << endl;
        return -1;
    }
    ofstream statsFile("accuracy.txt");
    vector<pair<pair<DSString, int>, int> > answers;    //id, prediction, sentiment

    getline(answerFile, line);  //toss the header line

    double correct_predictions = 0;
    int total_predictions = 0;
    for(const auto &p : predictions){
        getline(answerFile, line); 
        stringstream ss(line);
        getline(ss, sentiment, ',');
        getline(ss, id);
        DSString DSid(id.c_str());
        
        int sent = stoi(sentiment);
        total_predictions++;
        if (p.first == DSid && p.second == sent) {
            correct_predictions++;
        } else if (p.first == DSid && p.second != sent) {
            answers.push_back(make_pair(p, sent));  //save the ones that predicted wrong
        }  
    }
    //del later
    cout << fixed << setprecision(3) << "Rating: " << correct_predictions/total_predictions;
    
    //write accuracy to file
    statsFile << fixed << setprecision(3) << correct_predictions/total_predictions << endl;
    for(const auto &a : answers){   //prediction, sentiment, id
        statsFile << a.first.second << ", " << a.second << ", " << a.first.first << endl;
    }

    outFile.close();
    statsFile.close();
    return 0;
}
