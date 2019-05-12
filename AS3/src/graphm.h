// Jeffrey Murray
// CSS 343 - AS3
// Last Modified: 5/12

#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
using namespace std;

const int MAXNODES = 100;                 // "each {graph} having at most 100 nodes" (Page 1)

class GraphM {
    struct TableType {                    // Constructor for GraphM
        bool visited = false;             //  whether node has been visited
        int dist = -1;                    //  shortest distance from source known so far (-1 = infinity)
        int path[MAXNODES] = {0};         //  previous node in path of min dist

    };

private:
    NodeData* data[MAXNODES];             // data for graph nodes
    int C[MAXNODES][MAXNODES];            // cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
    // helper methods
    int minDistance(int from, int to, int min); //   ADD
    void getPath(int from, int to);             // Comments

public:
    ~GraphM();
    void buildGraph(ifstream& infile);
    void insertEdge(int from, int to, int weight);
    void deleteEdge(int from, int to);
    void findShortestPath();
    void displayAll();
    void display(int from, int to);

};

#endif  /* GRAPHM_H */