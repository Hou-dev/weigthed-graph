#include <istream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "graphType.h"

using namespace std;


template <typename T>
static inline bool contains(std::list<T> &l, const T &v) {
    return std::find(l.begin(), l.end(), v) != l.end();
}

graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    graph = new list<int>[size];
}


graphType::~graphType()
{
    delete [] graph;
}


int graphType::getgSize() const
{
    return gSize;
}


bool graphType::isEmpty() const
{
    return gSize == 0;
}


void graphType::clearGraph()
{
    for (int index = 0; index < gSize; index++)
        graph[index].clear();
    gSize = 0;
} //end clearGraph


void graphType::addEdge(int u, int v)
{
    if(graph[u].empty())
        gSize++;
    if(graph[v].empty())
        gSize++;

    if (!contains(graph[u], v))
        graph[u].push_back(v);
    if (!contains(graph[v], u))
        graph[v].push_back(u);
}


void graphType::printGraph() const
{
    for (int index = 0; index < gSize; index++)
    {
        cout << "[" << index << "] ";
        for (auto v : graph[index])
            cout << v << " ";
        cout << endl;
    }
    cout << endl;
} //end printGraph



