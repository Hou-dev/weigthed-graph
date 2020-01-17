#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <list>
#include <climits>
#include <algorithm>
#include "graphType.h"

using namespace std;


class Graph
{
    int V;    // No. of vertices

    // Pointer to an array containing adjacency lists
    list<int> *adj;
    list<int> d;

    // A function used by DFS
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);
    void connectedComponents();
};



class weightedGraphType : public graphType
{
	public:
		void createWeightedGraph(istream &input);
		//Function to create the graph and the weight matrix.
		//Postcondition: The graph using adjacency lists and
		// its weight matrix is created.
        void printWeights();

        void minimumSpanning(int sVertex);
        //Function to create a minimum spanning tree with
        //root as sVertex.
        // Postcondition: A minimum spanning tree is created.
        // The weight of the edges is also saved in the array
        // edgeWeights.
        void printTreeAndWeight();
        void numofclusts();
        void printlist();
        weightedGraphType(int size = 0);
		//Constructor
		//Postcondition: gSize = 0; maxSize = size;
		// graph is an array of pointers to linked lists.
		// weights is a two-dimensional array to store the weights
		// of the edges.
		// smallestWeight is an array to store the smallest weight
		// from source to vertices.
		~weightedGraphType();
		//Destructor
		//The storage occupied by the vertices and the arrays
		//weights and smallestWeight is deallocated.
	protected:
		int **weights; //pointer to create weight matrix
		int *smallestWeight; //pointer to create the array to store
		int source;
		int *edges;
		int *edgeWeights;
};

struct List
{
    int src;
    int dest;
    int weight;
};


void weightedGraphType::createWeightedGraph(istream &input)
{
    string line;
    string line2;
    int i = 0;
    int k =0;
    while(getline(input,line)){
            if(line.empty()){
                break;
            }
            istringstream ss(line);
            int num;
            while(ss>>num){
                addEdge(i,num);
            }
            i++;
    }
    while(getline(input,line2)){
        istringstream jj(line2);
        int num2;
        int l = 0;
        while(jj>>num2){
            weights[k][l]=num2;
            l++;
        }
        k++;
    }
}

void weightedGraphType::minimumSpanning(int sVertex)
{
    int startVertex, endVertex, minWeight;
    source = sVertex;
    bool *mstv;
    mstv = new bool[gSize];

    for (int j=0; j< gSize;j++)
    {
        mstv[j] = false;
        edges[j] = source;
        edgeWeights[j] = weights[source][j];
    }
    mstv[source] = true;
    edgeWeights[source] = 0;
    for ( int i =0; i < gSize -1;i++)
    {
        minWeight = INT_MAX;

        for(int j=0; j< gSize;j++)
        {
            if(mstv[j])
            {
                for(int k =0;k< gSize;k++)
                {
                    if(!mstv[k] && weights[j][k]<minWeight)
                    {
                        if(weights[j][k] != -999)
                        {
                            endVertex = k;
                            startVertex = j;
                            minWeight = weights[j][k];
                        }
                    }
                }

            }
        }
        mstv[endVertex]=true;
        edges[endVertex]= startVertex;
        edgeWeights[endVertex]= minWeight;
    }

}


void weightedGraphType::printWeights()
{
    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            if (weights[i][j] == INT_MAX) {
                cout << "-\t";
            } else {
                cout << weights[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool compare(const List& first, const List& second)
{
  if (first.weight < second.weight)
    return true;
  else
    return false;
}

bool compare2(const int& first, const int& second)
{
  if (first < second)
    return true;
  else
    return false;
}




list<List> links;
void weightedGraphType::printTreeAndWeight()
{
	double treeWeight = 0;
	int k = 0;
	cout << "Source Vertex: " << source << endl;
	cout << "Edges Weight" << endl;
		for (int j = 0; j < gSize; j++)
		{


			if (edges[j] != j)
			{
				treeWeight = treeWeight + edgeWeights[j];
				cout << "(" << edges[j] << ", " << j << ") "<< edgeWeights[j] << endl;
				links.push_back({edges[j],j,edgeWeights[j]});
			}
		}

        links.sort(compare);

		cout<<endl;
	cout << "Minimum spanning Tree Weight: "
		<< treeWeight << endl;
} //end printTreeAndWeight

void weightedGraphType::numofclusts()
{
    int a = 0;
    a=3;
    for(int t = 0;t<3-1;t++)
        {
            links.pop_back();
        }

}


void weightedGraphType::printlist()
{

    Graph g(gSize);
    cout<<endl;

    for (std::list<List>::iterator it = links.begin(); it != links.end(); ++it)
    {
        int a = it->dest;
        int n = it->src;
        int w = it->weight;
        g.addEdge(a,n);
        cout<<n<< " " <<a << " " << w<< " " <<endl;
    }
    cout<<endl;
    g.connectedComponents();

}


weightedGraphType::weightedGraphType(int size) : graphType(size)
{
	weights = new int*[size];
	for (int i = 0; i < size; i++)
		weights[i] = new int[size];
	smallestWeight = new int[size];
	edges = new int [size];
	edgeWeights = new int [size];
}

weightedGraphType::~weightedGraphType()
{
	for (int i = 0; i < gSize; i++)
		delete [] weights[i];
	delete [] weights;
	delete smallestWeight;
}



// Method to print connected components in an
// undirected graph
void Graph::connectedComponents()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int v = 0; v < V; v++)
        visited[v] = false;

    for (int v=0; v<V; v++)
    {
        if (visited[v] == false)
        {
            // print all reachable vertices
            // from v
            DFSUtil(v, visited);
            cout << "\n";
            for (std::list<int>::iterator it=d.begin(); it!=d.end(); ++it)
                std::cout << *it<< " ";
            d.clear();
        }
    }
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    //cout << v << " ";
    d.push_front(v);
    d.sort(compare2);




    // Recur for all the vertices
    // adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// method to add an undirected edge
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
