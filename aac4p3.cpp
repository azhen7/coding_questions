#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>

typedef long long LL;
typedef unsigned long long ULL;

std::map<LL, LL> endpoints;

struct pair_equal
{
    constexpr bool operator()(const std::pair<LL, LL>& a, const std::pair<LL, LL>& b) const
    {
        return a.first * b.second < a.second * b.first;
    }
};

std::set<std::pair<LL, LL>, pair_equal> slopes;
ULL N, M;

ULL countNumberOfPreferedSlopes();

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N >> M;

    for (ULL i = 0; i < N; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        endpoints.insert(std::make_pair(a, b));
    }

    for (ULL i = 0; i < M; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        slopes.insert(std::make_pair(a, b));
    }

    std::cout << countNumberOfPreferedSlopes() << '\n';
}

ULL factorial(ULL a)
{
    ULL ret = 1;
    for (ULL i = 1; i <= a; i++)
    {
        ret *= i;
    }
    return ret;
}

ULL combination(ULL a)
{
    if (a < 2)
    {
        return 0ULL;
    }
    return factorial(a) / (2 * factorial(a - 2));
}

ULL countNumberOfPreferedSlopes()
{
    ULL amount = 0ULL;
    //for each slope
    for (auto slope = slopes.begin(); slope != slopes.end(); slope++)
    {
        std::unordered_map<LL, ULL> numberOfEachSlope;
        std::unordered_set<LL> eachSlope;
        ULL index = 0ULL;
        //for each point, find its equation with slope
        for (auto point = endpoints.begin(); point != endpoints.end(); point++)
        {
            LL toInsert;
            if (slope->first > slope->second)
            {
                toInsert = point->first * slope->first - point->second * slope->second;
            }
            else
            {
                toInsert = point->second * slope->second - slope->first * point->first;
            }
            auto ret = eachSlope.insert(toInsert);
            if (!ret.second)
            {
                numberOfEachSlope[toInsert]++;
                amount += numberOfEachSlope[toInsert];
            }
        }
    }
    // for (auto it = numberOfEachSlope.begin(); it != numberOfEachSlope.end(); it++)
    // {
    //     amount += combination(it->second + 1);
    // }
    return amount;
}
