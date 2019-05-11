// Jeffrey Murray
// CSS 343 - AS3
// Last Modified: 5/2
#include<iostream>
#include<fstream>
#include<string>
#include "graphm.h"
using namespace std;


/* constructor: among others that need to be initialized,
        the data member T is initialized to sets all dist to infinity,
        sets all visited to false,
        and sets all path to 0. */
GraphM::~GraphM(){
    for(int i = 1; i <= size; i++){
        delete data[i];
        data[i] = NULL;
    }

}

/* buildGraph: builds up graph node information
    and adjacency matrix of edges between each node reading from a data file. */
void GraphM::buildGraph(ifstream& infile) {
    // number of locations input as string
    string s;
    // utilized as int
    infile >> s;

    if(s == "") return;
    // how many locations there are (first line:int)
    int l = stoi(s);
    size = l;
    getline(infile, s);

    // iterate and add locations to data array
    for(int i = 1; i <= l; i++){
        getline(infile, s);
        // using substring to remove "\r" from end of string
        NodeData *name = new NodeData(s.substr(0, s.size()-1));
        // assign data[i] to new ptr
        data[i] = name;
    }
    string f, t, w;
    int from, to, weight;
    for (;;) {
        // input as strings
        infile >> f >> t >> w;
        if (f == "0") break;                 // at end of one line
        if (infile.eof()) break;             // no more lines of data

        // set as integers
        from = stoi(f);
        to = stoi(t);
        weight = stoi(w);

        // add to adjacency matrix (all values currently are -1)
        C[from][to] = weight;
    }

}

/* insertEdge (int from, int to, int weight): insert an edge into graph between two given nodes */
void GraphM::insertEdge(int from, int to, int weight) {
    // error handling??
    if(to > size)
        size = to;
    C[from][to] = weight;
    T[from][to].dist = weight;
    T[from][to].visited = false;
}
/* removeEdge (int from, int to): remove an edge between two given nodes */
void GraphM::deleteEdge(int from, int to){
    // error handling??
    C[from][to] = 0;
}

// findShortestPath: find the shortest path between every node to every other node in the graph,
//    i.e., TableType T is updated with shortest path information
//    visited = shortest path found
//    save path along the way
//    implement find v function returns smallest distance for that vector

void GraphM::findShortestPath() {
    for(int source = 1; source <= size; source++){ // check vector 1...n
        // from n to n = 0
        T[source][source].dist = 0;

        // finds the shortest distance from source to all other nodes
        for(int v = 1; v <= size; v++) {
            // find v -- not visited, shortest distance at this point
            // mark v visited
            T[source][v].visited = true;
            // for each w adjacent to v (if C[V][W] != 0) and smallest weight
            for(int w = 1; w <= size; w++){
                // checks if it is adjacent
                if(C[v][w] != 0) {
                    // assign path only if not visited
                    if (!T[v][w].visited) {
                        int minDist = minDistance(v, w, INT8_MAX);
                        if(minDist < C[v][w]){
                            T[v][w].dist = (minDist);
                        }
                        else{
                            T[v][w].dist = (C[v][w]);
                            T[v][w].path[v] = w;
                        }
                        // mark as visited & set path
                        T[v][w].visited = true;
                        if(T[source][w].dist == -1)
                            T[source][w].dist = minDistance(source, w, INT8_MAX);
                    }
                }
            }
        }
    }
}

int GraphM::minDistance(int fromIndex, int toIndex, int min) {
    int nextPath = 0;

    // base case and out of bounds check
    if(fromIndex == toIndex || fromIndex == 0){
        //T[1][toIndex].path[toIndex] = fromIndex;
        return 0;
    }
    // Avoids source vector
    for(int v = 2; v <= size; v++){
        // find shortest weight in vector
        if(C[fromIndex][v] <= min && C[fromIndex][v] > 0){
            min = C[fromIndex][v];
            nextPath = v;
        }
    }
    // infinite loop check
    if(C[fromIndex][toIndex] == C[toIndex][fromIndex] && C[fromIndex][toIndex] != 0)
        return min;
    // min is unchanged then return
    if(min == INT8_MAX)
        return 0;
    // recursive path
    if(nextPath != 0)
        T[fromIndex][toIndex].path[fromIndex] = nextPath;
    // recursive call
    return min + minDistance(nextPath, toIndex, min);
}

/* displayAll: uses couts to demonstrate that the algorithm works properly.
    For the data in Figure 1, it will produce the sample output below (similar to, use the general format,
    but blanks do not need not be exact): */
void GraphM::displayAll() {
    cout << endl << "Description               From node  To node  Dijkstra's  Path    " << endl;
    for(int v = 1; v <= size; v++){
        cout << *data[v] << endl;
        for(int w = 1; w <= size; w++){
            if(w == v) continue;
            if(T[v][w].dist <= 0){
                printf("%31i %10i %8s \n", v, w, "---");
                continue;
            }
            printf("%31i %10i %8i", v, w, T[v][w].dist);
            cout << "       "; getPath(v,w); cout << endl;
        }
    }


}

/* display: uses couts to display the shortest distance with path info between the fromNode to toNode.
    For the data in Figure 1, a call of G.display(1,4)
    is going to produce the following output (similar to):
    1       4      50          1 3 2 4
    Aurora and 85th
    Woodland Park Zoo
    Green Lake Starbucks
    Troll under Aurora bridge */
void GraphM::display(int from, int to) {
    cout << endl << "Description               From node  To node  Dijkstra's  Path    " << endl;
    cout << *data[from] << endl;
    if(T[from][to].dist > 0){
        printf("%31i %10i %8i", from, to, T[from][to].dist);
        cout << "       "; getPath(from,to); cout << endl;
    }
    // else does not exist
    else printf("%31i %10i %8s \n", from, to, "---");




}

void GraphM::getPath(int from, int to) {
    // check if minDist did not find a shorter path
    if(C[from][to] <= T[from][to].dist){
        // that is IN BOUNDS
        if(C[from][to] > 0){
            cout << from << " " << to;
            return;
        }
    }
    // else find shortest path from...to
    int path = 0;
    for (int v = from; v <= to; v++) {
        if (path == to || path == v)
            break;
        // fetch values stored by minDistance()
        if (T[v][to].path[v] != 0) {
            path = T[v][to].path[v];
            cout << v << " " << path << " ";
        }
    }
    // avoid duplicates
    if(path != to)
        cout << to;

}
