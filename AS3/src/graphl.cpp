// Jeffrey Murray
// CSS 343 - AS3
// Last Modified: 5/2
#include<iostream>
#include<fstream>
#include<string>
#include "graphl.h"
using namespace std;

GraphNode::GraphNode(NodeData* d){ data = d; }

GraphL::GraphL(){
    for(int i = 0; i <= 100; i++){
        E[i] = NULL;
        D[i] = NULL;
    }
}

GraphL::~GraphL(){
    for(int i = 1; i <= size; i++){
        // delete E[i] content
        deleteEdge(E[i]);
        E[i] = NULL;

        // delete D[i] content
        if(D[i] != NULL){
            delete D[i]->data;
            D[i]->edgeHead = NULL;
            delete D[i];
            D[i] = NULL;
        }
    }
}

/* buildGraph: builds up graph node information
    and adjacency matrix of edges between each node reading from a data file. */
void GraphL::buildGraph(ifstream& infile) {
    // number of locations input as string
    string s;
    // blank file or eof
    infile >> s;
    if(s == "") return;
    if (infile.eof()) return;             // no more lines of data

    // how many locations there are (first line:int)
    int l = stoi(s);
    size = l;
    getline(infile, s);

    // iterate and add locations to *EdgeNode array
    for(int i = 1; i <= l; i++){
        getline(infile, s);
        // using substring to remove "\r" from end of string
        //  & assign data[i] to new ptr
        NodeData *d = new NodeData(s.substr(0, s.size()-1));
        D[i] = new GraphNode(d);
    }
    string src, adj;
    int f, t;
    for (;;) {
        // input as strings
        infile >> src >> adj;
        if (src == "0") break;            // at end of one line
        if (infile.eof()) break;             // no more lines of data

        // use src and adj as int
        f = stoi(src);
        t = stoi(adj);

        // insert edge nodes
        insertEdge(f,t);
    }
    for(int i = 1; i <= l; i++)
        D[i]->edgeHead = E[i];

}

void GraphL::insertEdge(int from, int to) {
    // initialize new EdgeNode
    EdgeNode* toAdd = new EdgeNode();
    toAdd->adjGraphNode = to;
    //toAdd->nextEdge = NULL;

    // O(1) insertion
    toAdd->nextEdge = E[from];
    E[from] = toAdd;
}

void GraphL::deleteEdge(EdgeNode *edge) {
    while(edge != NULL && edge->nextEdge != 0){
        edge->adjGraphNode = 0;
        if(edge->nextEdge != NULL)
            deleteEdge(edge->nextEdge);
        edge->nextEdge = NULL;
    }
    delete edge;
    edge = NULL;
}

void GraphL::depthFirstSearch() {
     // mark all not visited
     cout << endl << "Depth-first ordering: ";
     for (int v = 1; v <= size; v++) {
         if (!D[v]->visited)
             dfs(v, D[v]->edgeHead);
     }
     cout << endl;
}

void GraphL::dfs(int base, EdgeNode* cur){
    // mark v visited & print value
    D[base]->visited = true;
    cout << base << " ";
    // check for adj
    if(D[base]->edgeHead != NULL){
        cur = D[base]->edgeHead;
        // for each W adj to V
        if(cur != NULL){
            int adj = cur->adjGraphNode;

            // if ( w not visited)
            if(!D[adj]->visited)
                dfs(adj, cur->nextEdge);
        }
    }
}

void GraphL::displayGraph() {
    cout << endl << "Graph:" << endl;
    for(int v = 1; v <= size; v++){
        cout << "Node " << v << " \t\t " << *D[v]->data << endl;
        EdgeNode* ptr = E[v];
        while(ptr){
            cout << "  edge " << v << " " << ptr->adjGraphNode << endl;
            ptr = ptr->nextEdge;
        }
    }
}