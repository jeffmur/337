// Jeffrey Murray
// CSS 343 - AS3
// Last Modified: 5/12

#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
using namespace std;

const int MAXNODES = 100;   // "There may be several graphs, each having at most 100 nodes." (Page 4)

struct EdgeNode;            // forward reference for the compiler

struct GraphNode {          // structs used for simplicity, use classes if desired
    EdgeNode* edgeHead;     // head of the list of edges
    NodeData* data;         // data information about each node
    bool visited = false;
    GraphNode(NodeData*);
};

struct EdgeNode {
    int adjGraphNode;       // subscript of the adjacent graph node
    EdgeNode* nextEdge = NULL;     // points to nextEdge in list
};

class GraphL {
public:
    GraphL();                           // Constructor
    ~GraphL();                          // Destructor
     void buildGraph(ifstream& infile); // Builds up graph node information and adjacency list
     void depthFirstSearch();           // Displays each node information and edge in the graph
private:
    EdgeNode* E[MAXNODES];       // Array of pointers to GraphNodes (*EdgeNode, NodeData, bool)
    GraphNode* D[MAXNODES];      // Array of pointers to EdgeNodes  (int, *EdgeNode)
    void insertEdge(int from, int to);
    void dfs(int source);
    //void deleteEdge(EdgeNode* edge);
    int size;
};

#endif  /* GRAPHL_H */
