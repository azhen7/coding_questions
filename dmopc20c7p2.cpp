#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>

typedef long long LL;

LL numberOfTiles;
std::vector<std::pair<LL, LL>> vertices;

std::multiset<std::pair<LL, LL>> getVertices();

int main()
{
    std::cin >> numberOfTiles;

    for (LL i = 0; i < numberOfTiles; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        vertices.push_back(std::make_pair(a, b));
    }

    auto ret = getVertices();

    std::cout << ret.size() << '\n';
    for (auto e : ret)
    {
        std::cout << e.first << ' ' << e.second << '\n';
    }
}

void removeAllElementsWithDuplicates(std::multiset<std::pair<LL, LL>>& a)
{
    for (auto it = a.begin(); it != a.end(); )
    {
        auto res = it;

        bool hasIncremented = false;
        ++it;
        while (it != a.end() && *it == *res)
        {
            ++it;
            hasIncremented = true;
        }

        if (hasIncremented)
        {
            it = a.erase(res, it);
        }
    }
}

std::multiset<std::pair<LL, LL>> getVertices()
{
    std::multiset<std::pair<LL, LL>> ret;
    for (LL i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
        {
            //octagon
            ret.insert(std::make_pair(vertices[i].first, vertices[i].second - 1));
            ret.insert(std::make_pair(vertices[i].first - 1, vertices[i].second));
            ret.insert(std::make_pair(vertices[i].first - 1, vertices[i].second + 1));
            ret.insert(std::make_pair(vertices[i].first, vertices[i].second + 2));
            ret.insert(std::make_pair(vertices[i].first + 1, vertices[i].second + 2));
            ret.insert(std::make_pair(vertices[i].first + 2, vertices[i].second + 1));
            ret.insert(std::make_pair(vertices[i].first + 2, vertices[i].second));
            ret.insert(std::make_pair(vertices[i].first + 1, vertices[i].second - 1));
        }
        else
        {
            ret.insert(vertices[i]);
            ret.insert(std::make_pair(vertices[i].first, vertices[i].second + 1));
            ret.insert(std::make_pair(vertices[i].first + 1, vertices[i].second + 1));
            ret.insert(std::make_pair(vertices[i].first + 1, vertices[i].second));
        }
    }

    removeAllElementsWithDuplicates(ret);

    // std::vector<std::pair<LL, LL>> clockWise;
    // clockWise.push_back(*(ret.begin()));

    // for (LL i = 1; i < vertices.size(); i++)
    // {

    // }

    return ret;
}