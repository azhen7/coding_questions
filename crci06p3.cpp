#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

typedef long long LL;

LL N, H;

std::vector<LL> stalagmites;
std::vector<LL> stalactites;

int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    std::cin >> N >> H;

    std::vector<LL> numberOfObstacles(H, 0LL);

    for (LL i = 0; i < N; i++)
    {
        LL a;
        std::cin >> a;
        if (i % 2 == 0)
        {
            stalagmites.push_back(a);
        }
        else
        {
            stalactites.push_back(a);
        }
    }
    std::sort(stalagmites.begin(), stalagmites.end());
    std::sort(stalactites.begin(),  stalactites.end());

    for (LL i = 1; i <= H; i++)
    {
        auto it = std::lower_bound(stalagmites.begin(), stalagmites.end(), i);
        auto it2 = std::lower_bound(stalactites.begin(), stalactites.end(), H - i + 1);
        numberOfObstacles[i - 1] += std::distance(it, stalagmites.end()) + std::distance(it2, stalactites.end());
    }

    LL min = *std::min_element(numberOfObstacles.begin(), numberOfObstacles.end());
    LL count = std::count(numberOfObstacles.begin(), numberOfObstacles.end(), min);

    std::cout << min << ' ' << count << '\n';
}