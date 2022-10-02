#include <iostream>
#include <cmath>
#include <deque>
#include <algorithm>
#include <vector>

typedef long long LL;

bool isSteinsNumber(LL a);
LL numberOfSteinsNumbersInRange(LL a, LL b);

LL Q;
std::vector<LL> queries;
std::deque<LL> exponentsConsumed;

int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    std::cin >> Q;

    for (LL i = 0; i < Q; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        queries.push_back(numberOfSteinsNumbersInRange(a, b));
    }
    for (const LL& e : queries)
    {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

LL numberOfSteinsNumbersInRange(LL a, LL b)
{
    LL amount = 0LL;
    for (LL i = a; i <= b; i++)
    {
        amount += isSteinsNumber(i);
        exponentsConsumed.clear();
    }
    return amount;
}

bool isSteinsNumber(LL a)
{
    if (a < 0)
    {
        return false;
    }
    if (a == 0)
    {
        return true;
    }
    LL exponent = std::floor(std::log10(a) / std::log10(3));
    if (!std::binary_search(exponentsConsumed.begin(), exponentsConsumed.end(), exponent))
    {
        exponentsConsumed.push_front(exponent);
    }
    else
    {
        return false;
    }
    return isSteinsNumber(a - std::pow(3, std::floor(std::log10(a) / std::log10(3))));
}