#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>

typedef long long LL;

bool searchNeighbors(LL& hillIndex, LL difficulty);

LL numberOfHills;
LL numberOfPandas;

std::vector<std::vector<std::pair<LL, LL>>> ski;
std::vector<LL> counts;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> numberOfHills >> numberOfPandas;
    ski.resize(numberOfHills);
    counts.resize(numberOfHills);
    counts[0] = numberOfPandas;

    for (LL i = 0; i < numberOfHills - 1; i++)
    {
        LL start, end, difficulty;
        std::cin >> start >> end >> difficulty;
        ski[start - 1].push_back({end - 1, difficulty});
    }
    
        std::string a;
        std::getline(std::cin, a);
        std::getline(std::cin, a);
        std::stringstream ss(a);
        LL skill;
        while (ss >> skill)
        {
            LL index = 0;
            while (searchNeighbors(index, skill))
            {
                counts[index]++;
            }
        }

    for (LL i = 0; i < numberOfHills; i++)
    {
        std::cout << counts[i];
        if (i < numberOfHills - 1)
        {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

bool searchNeighbors(LL& hillIndex, LL difficulty)
{
    if (ski[hillIndex].size() == 0)
    {
        return false;
    }

    LL amount = std::numeric_limits<LL>::max();
    LL subhillIndex = std::numeric_limits<LL>::max();
    for (LL i = 0; i < ski[hillIndex].size(); i++)
    {
        if (std::abs(ski[hillIndex][i].second - difficulty) < amount)
        {
            amount = std::abs(ski[hillIndex][i].second - difficulty);
            subhillIndex = ski[hillIndex][i].first;
        }
    }
    hillIndex = subhillIndex;
    return true;
}