#ifndef graphType_h
#define graphType_h
#include <list>


class graphType
{
public:
    bool isEmpty() const;
    //Function to determine whether the graph is empty. //Postcondition: Returns true if the graph is empty; // otherwise, returns false.
    void clearGraph();
    //Function to clear graph.
    //Postcondition: The memory occupied by each vertex // is deallocated.
    void printGraph() const;
    //Function to print graph. //Postcondition: The graph is printed.
    void addEdge(int u, int v);
    //Function to add edge to undirected graph
    int getgSize() const;

    //Add function to print Euler Walk as a series of nodes

    graphType(int size = 0);
    //Constructor
    //Postcondition: gSize = 0; maxSize = size;
    // graph is an array of pointers to linked lists.
    ~graphType();
    //Destructor
    //The storage occupied by the vertices is deallocated.
protected:
    int maxSize; //maximum number of vertices
    int gSize; //current number of vertices
    std::list<int> *graph;
private:
    //utility functions: check for vertices of odd degree
    //test if edge is a bridge
};

#endif /* Graph_h */
