#include <iostream>
#include <fstream>
#include "graphl.h"
using namespace std;

int main() {
    ifstream infile1("/home/jeffmur/UWB/AS3/src/data32.txt");
    GraphL Test;
    Test.buildGraph(infile1);
    Test.depthFirstSearch();
    return 0;
}