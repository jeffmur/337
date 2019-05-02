#include <iostream>
#include <fstream>
#include "graphM.h"
using namespace std;

int main() {
    ifstream infile1("/home/jeffmur/UWB/AS3/src/data31.txt");
    GraphM Test;
    Test.buildGraph(infile1);
    return 0;
}