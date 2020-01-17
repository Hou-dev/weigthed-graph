#include <istream>
#include <iostream>
#include "weightedGraphType.h"

using namespace std;

int main(int argc, const char * argv[])
{
    ifstream input("input1.txt");
    int size = 0;
    string line;
    while (getline(input, line) && !line.empty()) {
        size++;
    }
    input.clear();
    input.seekg(0);
    weightedGraphType graph(size);
    graph.createWeightedGraph(input);
    input.close();

    //graph.printGraph();
    //graph.printWeights();
    cout << "Number of vertices: " << graph.getgSize() << endl << endl;

    //cout << "Breadth first traversal: ";
    //graph.breadthFirstTraversal();
    cout << endl;
    graph.minimumSpanning(0);
    graph.printTreeAndWeight();
    graph.numofclusts();
    graph.printlist();
    cout<<endl;

    return 0;
}
