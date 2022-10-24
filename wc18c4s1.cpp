#include <utility>
#include <vector>
#include <iostream>
#include <string>

typedef unsigned long long ULL;

std::string races;

struct edge
{
    ULL src;
    ULL dest;
};

struct forest
{
    ULL numberOfNodes;
    ULL numberOfEdges;
    edge* edges;
    
    std::vector<ULL> parent;

    forest(ULL a, ULL b)
    {
        numberOfNodes = a;
        numberOfEdges = b;

        edges = new edge[numberOfEdges];
    }

    ULL findSet(ULL i)
    {
        if (parent[i] == i)
            return i;
        parent[i] = findSet(parent[i]);
        return parent[i];
    }

    void unionSet(ULL i, ULL j)
    {
        ULL x = findSet(i);
        ULL y = findSet(j);

        if (races[x] != races[y])
        {
            return;
        }

        parent[x] = y;
    }
};

void initialize(forest& f)
{
    f.parent.assign(f.numberOfNodes, 0);
    
    for (ULL i = 0; i < f.numberOfNodes; i++)
    {
        f.parent[i] = i;
    }

    for (ULL i = 0; i < f.numberOfEdges; i++)
    {
        f.unionSet(f.edges[i].src, f.edges[i].dest);
    }
}

ULL numberOfPlanets;
ULL numberOfSpaceRoutes;
ULL numberOfFriends;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> numberOfPlanets >> numberOfSpaceRoutes >> numberOfFriends;
    std::cin >> races;

    forest f(numberOfPlanets, numberOfSpaceRoutes);

    for (ULL i = 0; i < numberOfSpaceRoutes; i++)
    {
        ULL x, y;
        std::cin >> x >> y;

        f.edges[i].src = x - 1;
        f.edges[i].dest = y - 1;
    }

    initialize(f);

    ULL numberOfFriendsThatCanReachDest = 0;
    for (ULL i = 0; i < numberOfFriends; i++)
    {
        ULL friendSrc;
        ULL friendDest;

        std::cin >> friendSrc >> friendDest;

        ULL test1 = f.findSet(friendSrc - 1);
        ULL test2 = f.findSet(friendDest - 1);

        if (test1 == test2)
        {
            numberOfFriendsThatCanReachDest++;
        }
    }

    std::cout << numberOfFriendsThatCanReachDest << '\n';
}