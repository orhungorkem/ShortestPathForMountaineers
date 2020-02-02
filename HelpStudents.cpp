/*
Student Name:
Student Number:
Project Number: 4
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include <queue>
#include "HelpStudents.h"

using namespace std;

HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {  //n nodes m edges k summit

    this->ways=ways;
    adjList.resize(N+1);
    for(int i=0;i<ways.size();i++){   //fill adjlist[i] with pair(j,d)   i-j has distance d also j-i
        int elem1=ways[i].first.first;
        int elem2=ways[i].first.second;
        int dist=ways[i].second;
        pair<long long int,long long int>p;
        p.first=elem2;
        p.second=dist;
        adjList[elem1].push_back(p);
        p.first=elem1;
        adjList[elem2].push_back(p);
    }
    summit=K;
    numVertices=N;


}

long long int parentBacktrack(long long int node,vector<pair<long long int,long long int>>&parents){
    if(parents[node].first==0){
        return 0;
    }
    return max(parents[node].second,parentBacktrack(parents[node].first,parents));
}

void HelpStudents::pqforEdges(priority_queue<pair<long long int,pair<long long int,long long int>>, vector<pair<long long int,pair<long long int,long long int>>>, greater<pair<long long int,pair<long long int,long long int>>>>&pq){
    for (int i = 0; i < ways.size(); ++i) {
        pair<long long int,pair<long long int,long long int>> p;
        p.first=ways[i].second;
        p.second=ways[i].first;
        pq.push(p);
    }

}

long long int getRoot(long long int node,vector<long long int>&parents){
    if(parents[node]<0){
        return node;
    }
    return getRoot(parents[node],parents);
}

void HelpStudents::minAdjList(vector<vector<pair<long long int,long long int>>>&adjListNew,priority_queue<pair<long long int,pair<long long int,long long int>>, vector<pair<long long int,pair<long long int,long long int>>>, greater<pair<long long int,pair<long long int,long long int>>>>&pq){

    vector<long long int>parents(numVertices+1,-1);   //at first, they are all roots
    while(!pq.empty()){

        long long int dist=pq.top().first;
        long long int node1=pq.top().second.first;
        long long int node2=pq.top().second.second;
        pq.pop();
        long long int root1=getRoot(node1,parents);
        long long int root2=getRoot(node2,parents);
        if(root1==root2){
            continue;
        }

        pair<long long int,long long int>p;
        p.first=node2;
        p.second=dist;

        adjListNew[node1].push_back(p);
        p.first=node1;

        adjListNew[node2].push_back(p);
        if(parents[root1]<parents[root2]){
            parents[root1]=parents[root1]+parents[root2];
            parents[root2]=root1;
        }
        else{
            parents[root2]=parents[root1]+parents[root2];
            parents[root1]=root2;
        }
        if(parents[root1]==-1*numVertices||parents[root2]==-1*numVertices){
            return;
        }

    }

}

long long int HelpStudents::firstStudent() {   //DIJKSTRA



    vector<long long int>distances(numVertices+1,INT64_MAX);
    distances[1]=0;
    vector<bool>visited(numVertices+1, false);
    set<pair<long long int,long long int>>s;  //first distance second adjacent
    pair<long long int,long long int>p;
    p.first=0;
    p.second=1;
    s.insert(p);
    while(!s.empty()){
        p=*s.begin();
        long long int cur=p.second;
        s.erase(*s.begin());
        visited[cur]=1;
        if(cur==summit){
            return distances[cur];
        }

        for (int i = 0; i <adjList[cur].size() ; i++) {
            long long int recent=adjList[cur][i].first;
            long long int dist=adjList[cur][i].second;
            if(!visited[recent]){
                if(distances[recent]>(distances[cur]+dist)){
                    long long int temp=distances[recent];
                    distances[recent]=distances[cur]+dist;
                    p.first=temp;  p.second=recent;
                    s.erase(p);
                    p.first=distances[recent];
                    s.insert(p);
}
            }

        }
    }


}




long long int HelpStudents::secondStudent() {
    priority_queue<pair<long long int,pair<long long int,long long int>>, vector<pair<long long int,pair<long long int,long long int>>>, greater<pair<long long int,pair<long long int,long long int>>>>pq;
    pqforEdges(pq);  //fill pq from ways

    vector<vector<pair<long long int,long long int>>>adjListNew(numVertices+1);
    minAdjList(adjListNew,pq);  //fill new adjlist with min edges

    stack<long long int>s;
    s.push(1);
    vector<bool>visited(numVertices, false);
    vector<pair<long long int,long long int>>parents(numVertices+1);
    pair<long long int,long long int>p;  //keeps parents and their distances to backtrack
    p.first=0;
    p.second=0;
    parents[1]=p;
    while(!s.empty()){
        long long int cur=s.top();
        s.pop();
        visited[cur]= true;
        for(int i=0;i<adjListNew[cur].size();i++){
            long long int recent=adjListNew[cur][i].first;
            long long int dist=adjListNew[cur][i].second;
            if(!visited[recent]){
                s.push(recent);
                p.first=cur;
                p.second=dist;
                parents[recent]=p;
            }
            if(recent==summit){
                return parentBacktrack(recent,parents);
            }
        }
    }

}


long long int HelpStudents::thirdStudent() {   //BFS

    vector<bool>visited(numVertices,false);  //or can make a distamces array, initiate with -1
    vector<long long int>distances(numVertices);
    distances[source]=0;
    queue<long long int>q;
    q.push(source);
    visited[source]=1;
    while(!q.empty()){
        long long int cur=q.front();
        q.pop();
        for(int i=0;i<adjList[cur].size();i++){
            long long int recent=adjList[cur][i].first;
            if(recent==summit){
                return distances[cur]+1;
            }
            if(visited[recent]!=1){
                q.push(recent);
                visited[recent]=1;
                distances[recent]=distances[cur]+1;
            }
        }
    }



}


long long int HelpStudents::fourthStudent() {  //burdaki caseler tamam

    queue<long long int>q;
    q.push(1);
    long long int time=0;
    while(!q.empty()){
        long long int cur=q.front();
        q.pop();
        long long int mindist=INT64_MAX;
        int mindex=0;  //min distant vertex
        int adjindex=0; //that vertex's index in adjlist
        for (int i = 0; i <adjList[cur].size() ; ++i) {
            long long int recent=adjList[cur][i].first;
                if(adjList[cur][i].second<mindist){
                    mindist=adjList[cur][i].second;
                    mindex=recent;
                    adjindex=i;
                }
                else if(adjList[cur][i].second==mindist){
                    if(mindex>recent){
                        mindex=recent;
                        adjindex=i;
                    }
                }
            }

        if(mindex==summit){
            return time+mindist;
        }
        if(mindex!=0){
            adjList[cur][adjindex].second=INT64_MAX;
            for(int i=0;i<adjList[mindex].size();i++){
                if(adjList[mindex][i].first==cur){
                    adjList[mindex][i].second=INT64_MAX;
                    break;
                }
            }
            q.push(mindex);
            time+=mindist;
        }
    }
    return -1;

}




long long int HelpStudents::fifthStudent() {

    vector<bool>visited(numVertices+1, false);
    vector<long long int>distances1(numVertices+1,INT64_MAX);
    vector<long long int>distances2(numVertices+1,INT64_MAX);
    vector<long long int>distances0(numVertices+1,INT64_MAX);
    vector<int>charges(numVertices+1,0);
    set<tuple<long long int,long long int,int>>s;  //first dist second node third charge
    tuple<long long int,long long int,int>t;
    get<0>(t)=0;
    get<1>(t)=1;
    get<2>(t)=0;
    s.insert(t);
    distances0[1]=0;
    while(!s.empty()){
        t=*s.begin();
        long long int distanceforthis=get<0>(t);
        long long int cur=get<1>(t);
        int charge=get<2>(t);
        s.erase(t);
        visited[cur]=1;


        long long int minadj = INT64_MAX;  //distance of closest edge
        for (int i = 0; i < adjList[cur].size(); i++) {
            if (adjList[cur][i].second < minadj) {
                minadj = adjList[cur][i].second;
            }
        }
        if(charge==0) {

            //aynı node a 1 ile gel!  1 le gelinen başka varsa kıyasla kısayı tut
            if(distances1[cur]>distanceforthis+3*minadj){
                long long int temp=distances1[cur];
                distances1[cur]=distanceforthis+3*minadj;
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=1;
                if(temp!=INT64_MAX) {
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+3*minadj;
                s.insert(t);
            }


            //aynı node a 2 ile gel
            if(distances2[cur]>distanceforthis+2*minadj){
                long long int temp=distances2[cur];
                distances2[cur]=distanceforthis+2*minadj;
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=2;
                if(temp!=INT64_MAX) {
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+2*minadj;
                s.insert(t);
            }


            //veya 1 ilerle
            for(int i=0;i<adjList[cur].size();i++){
                long long int recent=adjList[cur][i].first;
                long long int dist=adjList[cur][i].second;
                   if(distances1[recent]>distanceforthis+dist) {
                       long long int temp=distances1[recent];
                       distances1[recent] = distanceforthis + dist;
                       get<0>(t) = temp;
                       get<1>(t)=recent;   //düz ilerle
                       get<2>(t)=1;
                       if(temp!=INT64_MAX){
                           s.erase(t);
                       }
                       get<0>(t)=distanceforthis+dist;
                       s.insert(t);
                   }

            }
        }



        else if(charge==1) {
            //aynı node a 0 la gel
            if(distances0[cur]>distanceforthis+minadj){
                long long int temp=distances0[cur];
                distances0[cur]=distanceforthis+minadj;
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=0;
                if(temp!=INT64_MAX){
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+minadj;
                s.insert(t);
            }

            if(distances2[cur]>distanceforthis+3*minadj){
                //aynı node a 2 ile gel
                long long int temp=distances2[cur];
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=2;
                if(temp!=INT64_MAX){
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+3*minadj;
                s.insert(t);
            }


            for (int i = 0; i < adjList[cur].size(); i++) {
                long long int recent = adjList[cur][i].first;
                long long int dist = adjList[cur][i].second;

                if(distances2[recent]>distanceforthis+dist) {
                    long long int temp=distances2[recent];
                    distances2[recent] = distanceforthis + dist;
                    get<0>(t)=temp;
                    get<1>(t)=recent;
                    get<2>(t)=2;
                    if(temp!=INT64_MAX){
                        s.erase(t);
                    }
                    get<0>(t)=distanceforthis+dist;
                    s.insert(t);
                }

            }

        }

        else{//charge = 2 ready to teleport

            //aynı yere 1 le gel
            if(distances1[cur]>distanceforthis+minadj){
                long long int temp=distances1[cur];
                distances1[cur]=distanceforthis+minadj;
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=1;
                if(temp!=INT64_MAX){
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+minadj;
                s.insert(t);
            }

            if(distances0[cur]>distanceforthis+2*minadj){
                //aynı node a 0 ile gel
                long long int temp=distances0[cur];
                get<0>(t)=temp;
                get<1>(t)=cur;
                get<2>(t)=0;
                if(temp!=INT64_MAX){
                    s.erase(t);
                }
                get<0>(t)=distanceforthis+2*minadj;
                s.insert(t);
            }




            for (int i = 0; i < adjList[cur].size(); i++) {
                long long int recent = adjList[cur][i].first;
                long long int dist = adjList[cur][i].second;
                    if(distances0[recent]>distanceforthis) {
                        distances0[recent] = distanceforthis;
                    }
                    get<0>(t) = distanceforthis;
                    get<1>(t) = recent;
                    get<2>(t) = 0;
                    s.insert(t);
                    }

        }
    }

    return min(distances0[summit],min(distances1[summit],distances2[summit]));

}








// YOU CAN ADD YOUR HELPER FUNCTIONS


HelpStudents::~HelpStudents(){
    //delete []vertices;
}











