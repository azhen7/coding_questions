#include <iostream>
#include <sstream>
#include <vector>

class Edge {
public:
    int src, dest;
};

class Graph {
public:
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges
    Edge* edge;
};

std::vector<int> parent, setSize;
int numSets;

Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph();
    graph->V = V;
    graph->E = E;
 
    graph->edge = new Edge[graph->E * sizeof(Edge)];
 
    return graph;
}

int findSet(int i)
{
    if(parent[i] == i)
        return i;
    parent[i] =  findSet(parent[i]);
    return parent[i];    
}


bool isSameSet(int i, int j)
{
    return findSet(i) == findSet(j);
}

int UnionSet(Graph* g, int i, int j)
{
    int x = findSet(i);
    int y = findSet(j);
    
    if(x == y)
        return 1;

    parent[x] = y;
    setSize[y] += setSize[x];
    numSets--;
    return 0;
}

int init(Graph* g)
{
    parent.assign(g->V, 0);
    setSize.assign(g->V, 1);
    for(int i = 0; i < g->V; i++)
    {
        parent[i] = i;
    }
    numSets = g->V;

    int count = 0;
    for (int i = 0; i < g->E; ++i) {
        count += UnionSet(g, g->edge[i].src, g->edge[i].dest);
    }
    return count;
}


int N, M;

int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    std::cin >> N >> M;
    Graph* g =  createGraph(N, M); //vetices, edges

    for (int i = 0; i < M; i++)
    {
        int a, b;
        std::cin >> a >> b;

        g->edge[i].src = a-1;
        g->edge[i].dest = b-1;

    }
    
    int ret = init(g);

    if (ret <= 1)
    {
        std::cout << "YES" << std::endl;
    }
    else{
        std::cout << "NO" << std::endl;
    }
}


