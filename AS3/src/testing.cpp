#include <iostream>
#include <fstream>
#include "graphM.h"
using namespace std;

int main() {
    ifstream infile1("/home/jeffmur/UWB/AS3/src/dataUWB.txt");
    GraphM Test;
    Test.buildGraph(infile1);
    Test.findShortestPath();
    Test.displayAll();
    return 0;
}