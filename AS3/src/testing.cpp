#include <iostream>
#include <fstream>
#include "graphM.h"
using namespace std;

int main() {
    ifstream infile1("/home/jeffmur/UWB/AS3/src/data31.txt");
    GraphM Test;
    Test.buildGraph(infile1);
    Test.findShortestPath();
    for(int i = 1; i <= 5; i++){
        for(int j=1; j<=5; j++)
            cout << "minDistance(" << i << "," << j << "): " << Test.minDistance(i,j) << endl;
    }
    return 0;
}