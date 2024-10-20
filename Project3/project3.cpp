#include "SentimentClassifier.h"
#include "DSString.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <tuple>

using namespace std;

int main(){
    
    //string trainingFile, testingFile, answerFile, outputFile, accuracyFile;
    
    SentimentClassifier classifier;

    string line;
    ifstream trainingData("train_dataset_20k.csv");

    if (!trainingData.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    getline(trainingData, line);    //toss the header line
    //vector<tuple<DSString,DSString,DSString> > tweetList;

    for(int i =0; i<25; i++){   //just getting 25 lines for now
        string sentiment, id, date, query, user, tweet;
        //char sentiment[1], id[10], date[28], query[8], user[100], tweet[100];
        getline(trainingData, line);
        stringstream ss (line);
        
        getline(ss, sentiment, ',');
        DSString DSsentiment(sentiment.c_str());    //am i allowed to do this???
        getline(ss, id, ',');
        DSString DSid(id.c_str());
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);
        DSString DStweet(tweet.c_str());

        classifier.train(DStweet, DSsentiment);

        //tweetList.push_back(make_tuple(DSsentiment, DSid, DStweet));
    }  

    //for (const auto& tuple : tweetList) {
    //    cout << "Sentiment: " << get<0>(tuple) << ", User: " << get<1>(tuple) << ", Tweet: " << get<2>(tuple) << endl;
    //}
    trainingData.close();

    //test data
    ofstream outFile;
    outFile.open("results.csv");
    ifstream testingData("test_dataset_10k.csv");

    if (!testingData.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    getline(testingData, line);    //toss the header line
    for(int i =0; i<25; i++){   //just getting 25 lines for now
        string id, date, query, user, tweet;
        //char sentiment[1], id[10], date[28], query[8], user[100], tweet[100];
        getline(testingData, line);
        stringstream ss (line);

        getline(ss, id, ',');
        DSString DSid(id.c_str());
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);
        DSString DStweet(tweet.c_str());

        int prediction = classifier.predict(DStweet);
        outFile << prediction << ", " << DSid;

        cout << id << ": " << prediction << endl;
    }  
    testingData.close();

    //accuracy
    ofstream statsFile;
    statsFile.open("accuracy.txt");


    outFile.close();
    statsFile.close();
    return 0;
}
