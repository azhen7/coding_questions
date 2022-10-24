#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

typedef long long LL;

struct edge
{
    LL src;
    LL dest;
};

struct forest
{
    LL numberOfNodes;
    LL numberOfEdges;
    edge* edges;    //array of edges
    
    std::vector<LL> parent;
    std::vector<LL> setSize;

    forest(LL a, LL b)
    {
        numberOfNodes = a;
        numberOfEdges = b;

        edges = new edge[numberOfEdges];
    }

    LL findSet(LL i)
    {
        if (parent[i] == i)
            return i;
        parent[i] = findSet(parent[i]);
        return parent[i];
    }

    LL unionSet(LL i, LL j)
    {
        LL x = findSet(i);
        LL y = findSet(j);

        if (x == y)
        {
            return 1;
        }

        //there is a link from i to j -> parent of j is i
        parent[x] = y;
        setSize[y] += setSize[x];
        return 0;
    }
};

LL initialize(forest& f)
{
    f.parent.assign(f.numberOfNodes, 0);
    f.setSize.assign(f.numberOfNodes, 1);
    
    //default values for parents of nodes
    for (LL i = 0; i < f.numberOfNodes; i++)
    {
        f.parent[i] = i;
    }

    LL countDuplicates = 0;
    for (LL i = 0; i < f.numberOfEdges; i++)
    {
        countDuplicates += f.unionSet(f.edges[i].src, f.edges[i].dest);
    }

    return countDuplicates;
}

LL numberOfNodes;
LL numberOfEdges;

int main()
{
    std::cin >> numberOfNodes >> numberOfEdges;

    forest f(numberOfNodes, numberOfEdges);

    for (LL i = 0; i < numberOfEdges; i++)
    {
        LL a, b;
        std::cin >> a >> b;

        f.edges[i].src = a - 1;
        f.edges[i].dest = b - 1;
    }

    LL ret = initialize(f);

    if (ret <= 1)
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
}