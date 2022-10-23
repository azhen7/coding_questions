#include <iostream>
#include <sstream>
#include <vector>
#include <string>


std::string races;

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

void UnionSet(Graph* g, int i, int j)
{
    int x = findSet(i);
    int y = findSet(j);
    
    if(races[x] != races[y])
        return;

    parent[x] = y;
}

void init(Graph* g)
{
    parent.assign(g->V, 0);
    for(int i = 0; i < g->V; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < g->E; ++i) {
        UnionSet(g, g->edge[i].src, g->edge[i].dest);
    }
    return;
}

int N, M, K;


int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    std::cin >> N >> M >> K;
    Graph* g =  createGraph(N, M); //vetices, edges


    std::cin >> races;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        std::cin >> a >> b;

        g->edge[i].src = a-1;
        g->edge[i].dest = b-1;
    }
    init(g);

    int count = 0;
    for (int i = 0; i < K; i++)
    {
        int x, y;
        std::cin >> x >> y;
         
        int x_path = findSet(x-1);
        int y_path = findSet(y-1);

        if(x_path == y_path)
        {
            count++;
        }

    }
    std::cout << count << std::endl;

    return 0;

}



