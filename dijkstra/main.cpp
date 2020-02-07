#include <iostream>
#include <string>
#include <ctime>

#include "graph.h"

using namespace std;

int main(){
    string inName, outName, start = "";
    clock_t time;

    cout << "Enter name of graph file: ";
    cin >> inName;

    //make the graph
    graph mygraph(50000);
    mygraph.insert(inName);


    while(!mygraph.goodstart(start)){
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> start;
    }

    //do dijkstra
    //measure time
    time = clock();
    mygraph.dijkstra(start);
    time = clock() - time;
    double time_real = ((double)time)/CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_real << endl;

    cout << "Enter name of output file: ";
    cin >> outName;

    //result
    mygraph.result(outName, start);

    exit(0);
}