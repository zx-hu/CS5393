/*
Name: Gloria Hu
Class: 5393-002 Data Structures in C++ 
Collaborators: none

Design Documentation

Objective: The objective of this code is to implement a social network analysis tool that makse judgements based on a person's connections.
It will use an adjaceny list graph to make friend suggestions, identify degrees of separation, and recognize the top influential users.
We will also learn to create and use our own dataset.
*/

#include <iostream>
#include <queue>    //for degree of separation
#include <vector>   //for influential users
#include <random>   //for generating dataset
using namespace std;

//node
struct User{
    int ID;
    string name;
    User* next = nullptr;

    User(int i, string n){
        ID = i;
        name = n;
    }
};

//graph
class FriendList{
    int numUsers;
    User** adj_list;
    public:
        FriendList(int size){
            numUsers = size;
            adj_list = new User*[numUsers];
            for(int i = 0; i<numUsers; i++){
                adj_list[i] = nullptr;
            }
        }
        
        ~FriendList(){
            for(int i=0; i<numUsers; i++){
                User* current = adj_list[i];
                while(current != nullptr){
                    User* del = current;
                    current = current->next;
                    delete del;
                }
            }
            delete[] adj_list;
        }

        void addUser(int ID, string name){
            User* newUser = new User(ID, name);
            adj_list[ID] = newUser;
        }

        void addFriend(int userID, int friendID){
            User* newFriend = new User(*adj_list[friendID]);
            newFriend->next = adj_list[userID]->next;
            adj_list[userID]->next = newFriend;
        }

        void printFriends(int userID){
            User* user = adj_list[userID];
            cout << user->name << "'s friends: ";
            User* print = user->next;
            while(print != nullptr){
                cout << print->name << " ";
                print = print->next;
            }
            cout << endl;
        }

        void suggestFriends(int userID){
            User* user = adj_list[userID];

            int* mutualCount = new int[numUsers]();

            //traverse through user's friends
            User* temp = user->next;
            while(temp != nullptr){
                //traverse through friend's friends
                User* mutual = adj_list[temp->ID]->next;
                while(mutual != nullptr){
                    mutualCount[mutual->ID]++;
                    mutual = mutual->next;
                }
                temp = temp->next;
            }

            //sort to find top 5
            int topCounts[5] = {0};
            int topIDs[5] = {0};

            // Find the top 5 mutual friends
            for (int i = 0; i < numUsers; i++) {
                if (mutualCount[i] > topCounts[4]) {
                    topCounts[4] = mutualCount[i];
                    topIDs[4] = i;
                    // Sort the top 5 arrays
                    for (int j = 4; j > 0 && topCounts[j] > topCounts[j-1]; j--) {
                        std::swap(topCounts[j], topCounts[j-1]);
                        std::swap(topIDs[j], topIDs[j-1]);
                    }
                }
            }

            cout << "Friend suggestions for " << user->name << ": " << endl;
            for(int i=0;i<5 && topCounts[i] > 0; i++){
                cout << adj_list[topIDs[i]]->name << " (" << topCounts[i] << " mutual friends)" << endl;
            }
            cout << endl;

            delete[] mutualCount;
        }

        int degreeOfSeparation(int user1, int user2){
            if(user1 == user2){return 0;} //if users are the same

            queue<int> q;
            int* distance = new int[numUsers];
            for(int i=0; i<numUsers; i++){
                distance[i] = numUsers+1; //set dist to greater than network. basically infinity
            }
            distance[user1] = 0;
            q.push(user1);

            while(!q.empty()){
                int current = q.front();
                q.pop();

                User* temp = adj_list[current]->next;
                while(temp != nullptr){
                    if(distance[temp->ID] == numUsers+1){
                        distance[temp->ID] = distance[current] + 1;
                        q.push(temp->ID);

                        if (temp->ID == user2) {
                        int result = distance[temp->ID];
                        delete[] distance;
                        return result;

                        }
                    }
                    temp = temp->next;
                }
            }

            delete[] distance;
            return -1;  //no connection
        }

        void SCC(){
            //discovery times of visited vertices
            //lowest discovery time reachable from the vertex
        }

        void influentialUsers(){
            vector< pair<int,int> > userConnections;

            for(int i=0;i<numUsers;i++){
                int connections = 0;
                User* current = adj_list[i]->next;
                while(current != nullptr){
                    connections++;
                    current = current->next;
                }

                userConnections.push_back(make_pair(connections, i));
            }

            sort(userConnections.begin(), userConnections.end(), greater<pair<int, int> >());

            cout << "Top 10 Influential Users (Most Connections): " << endl;
            for(int i=0;i<10;i++){
                cout << adj_list[userConnections[i].second]->name << " with " << userConnections[i].first << " connections" << endl;
            }
            cout << endl;
        }

        int getNumUsers(){
            return numUsers;
        }

        double getAvgConnections(){
            double totalConnections = 0;
            
            for(int i=0; i<numUsers; i++){
                User* current = adj_list[i]->next;
                while(current != nullptr){
                    totalConnections++;
                    current = current->next;
                }
            }
            return totalConnections/numUsers;
        }
};

void generateDataset(FriendList& list, int numUsers=250){
    srand(time(0));
    for(int i=0; i<numUsers;i++){
        list.addUser(i, "user" + to_string(i));
    }
    default_random_engine generator;
    normal_distribution<double> distribution(25, 8);
    for(int i=0; i<numUsers;i++){
        int connections = distribution(generator);   // Each user has 1 to 50 connections. normal distribtion
        
        for(int j=0; j<connections; j++){
            int friendID = rand() % numUsers;
            if(friendID != i){  //edit this to not repeat friends
                list.addFriend(i, friendID);
            }
        }
    }
}

int main(){

    FriendList list(250);

    cout << "Number of users: " << list.getNumUsers() << endl;

    generateDataset(list);

    int userID;
    cout << "User ID to show friends list: ";
    cin >> userID;
    list.printFriends(userID);

    cout << "User ID to suggest friends for: ";
    cin >> userID;
    list.suggestFriends(userID);

    int friendID;
    cout << "2 User IDs to find degree of separation: ";
    cin >> userID;
    cin >> friendID;
    cout << "Degrees of separation between " << userID << " and " << friendID << " : " <<list.degreeOfSeparation(userID, friendID) << endl;

    list.influentialUsers();

    cout << "Average Connections: " << list.getAvgConnections() << endl;
    return 0;
}

/*
References:
Cplusplus: https://cplusplus.com/reference/random/normal_distribution/ 
Microsoft Copilot: https://copilot.microsoft.com 
*/
