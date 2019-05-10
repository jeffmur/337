// Jeffrey Murray
// CSS 343 - AS3
// Last Modified: 5/2
#include<iostream>
#include<fstream>
#include<string>
#include "graphM.h"
using namespace std;


/* constructor: among others that need to be initialized,
        the data member T is initialized to sets all dist to infinity,
        sets all visited to false,
        and sets all path to 0. */
GraphM::~GraphM(){
}

/* buildGraph: builds up graph node information
    and adjacency matrix of edges between each node reading from a data file. */
void GraphM::buildGraph(ifstream& infile) {
    // number of locations input as string
    string s;
    // utilized as int
    infile >> s;

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
        data[i] = *name;
    }
    string f, t, w;
    int from, to, weight;
    cout << "Adding values to Adjacency Matrix..." << endl;
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
        cout << "From: " << from << "\t To: " << to << " \t Weight: " << weight << endl;
    }
}

/* insertEdge (int from, int to, int weight): insert an edge into graph between two given nodes */
void GraphM::insertEdge(int from, int to, int weight) {
    // error handling??
    C[from][to] = weight;
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
                        T[v][w].dist = (T[1][v].dist + C[v][w]);
                        T[v][w].visited = true;
                        T[v][w].path = v;
                        // found shorter path - updates source vector
                        if(T[source][w].dist > T[v][w].dist){
                            T[source][w].dist = T[v][w].dist;
                            T[source][w].path = v;
                            // set all adjacent paths to false
                            for(int i = 1; i <= size; i++){
                                T[w][i].visited = false;
                            }
                            // restart path
                            //findShortestPath();
                        }
                    }
                }
            }
        }
    }
}

int GraphM::minDistance(int fromIndex, int toIndex) {
    int min = INT8_MAX;
    if(fromIndex != 1){
        min = C[fromIndex][toIndex];
    }
    if(T[fromIndex][toIndex].dist > 0 && min > T[fromIndex][toIndex].dist)
        min = T[fromIndex][toIndex].dist;
    else{
        for(int i = 1; i <=size; i++) {
            if (min > T[i][toIndex].dist && T[i][toIndex].dist > 0)
                min = T[i][toIndex].dist;
        }
    }
    if(min <= 0 || min == INT8_MAX){
        return -1;
    }
    return min;
}

/* displayAll: uses couts to demonstrate that the algorithm works properly.
    For the data in Figure 1, it will produce the sample output below (similar to, use the general format,
    but blanks do not need not be exact): */

/* display: uses couts to display the shortest distance with path info between the fromNode to toNode.
    For the data in Figure 1, a call of G.display(1,4)
    is going to produce the following output (similar to):
    1       4      50          1 3 2 4
    Aurora and 85th
    Woodland Park Zoo
    Green Lake Starbucks
    Troll under Aurora bridge */

/* Add utility functions as needed
    * initArray(); - Constructor */

int GraphM::getNodeSize(int costArray[100]){
    int nodeSize = 0;
    for(int i = 1; i <= 100; i++){
        if(costArray[i] != 0)
            nodeSize++;
    }
    return nodeSize;
}
    // initArray(); - Constructor
