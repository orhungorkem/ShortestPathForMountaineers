#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <set>
#include <tuple>

using namespace std;





class HelpStudents{

public:



    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways);
    ~HelpStudents();
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();
    vector<vector<pair<long long int,long long int>>>adjList;   //first=the element second=distance index=element
    long long int summit=0;
    long long int numVertices=0;
    long long int source=1;
    vector < pair< pair <int,int> , int > > ways;
    void pqforEdges(priority_queue<pair<long long int,pair<long long int,long long int>>, vector<pair<long long int,pair<long long int,long long int>>>, greater<pair<long long int,pair<long long int,long long int>>>>&pq);
    void minAdjList(vector<vector<pair<long long int,long long int>>>&adjList,priority_queue<pair<long long int,pair<long long int,long long int>>, vector<pair<long long int,pair<long long int,long long int>>>, greater<pair<long long int,pair<long long int,long long int>>>>&pq);

    //USE THAT IN METHOD
    // YOU CAN ADD YOUR HELPER FUNCTIONS AND MEMBER FIELDS

};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
