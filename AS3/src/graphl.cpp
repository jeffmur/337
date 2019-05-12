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
        D[i];
    }
}

GraphL::~GraphL(){
    for(int i = 0; i <= 100; i++){
        // delete E[i] content
        // E[i] = NULL

        // delete D[i] content
        // D[i] = NULL
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
        D[i]->edgeHead = E[i];
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
        cout << "From: " << f << " To: " << t << endl;
    }

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

void GraphL::depthFirstSearch() {
     // mark all not visited
     for (int v = 1; v <= size; v++) {
         cout << v << ": ";
         if (!D[v]->visited)
             dfs(v);
         cout << endl;
     }
}

void GraphL::dfs(int base){
    if(base <= size){
        D[base]->visited = true;
        if(E[base] != NULL){
            cout << E[base]->adjGraphNode << " ";
            if(E[base]->nextEdge != NULL)
                dfs(base+=1);
        }
    }
    else return;

}