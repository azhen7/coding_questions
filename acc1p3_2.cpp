#include <iostream>
#include <climits>
#include <vector>
#include <utility>

typedef long long LL;

LL N, T;
std::vector<std::pair<LL, LL>> poutines;
LL mod = 998244353;

LL moneySpent(LL amount);

int main()
{
    std::cin >> N >> T;

    for (LL i = 0; i < N; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        poutines.push_back(std::make_pair(a, b));
    }

    LL left = 0LL;
    LL right = LLONG_MAX;
    LL leftOver = 0LL;

    while (left < right)
    {
        LL middle = (left + right) / 2;
        LL amount = moneySpent(middle);

        if (amount > T)
        {
            left = middle + 1;
        }
        else
        {
            right = middle;
            leftOver = (T - amount) % mod;
        }
    }
    LL happiness = 0LL;
    for (LL i = 0; i < N; i++)
    {
        if (poutines[i].first >= right)
        {
            LL n = (poutines[i].first - right) / poutines[i].second;
            happiness += std::max(0LL, (poutines[i].first * (n + 1) - (n * (n + 1) / 2) * n * poutines[i].second) % mod);
        }
    }
    if (leftOver > 0)
    {
        happiness = (happiness + leftOver * ((right - 1) % mod)) % mod;
    }
    std::cout << happiness << '\n';
}

LL moneySpent(LL amount)
{
    LL amountSpent = 0LL;
    for (LL i = 0; i < N; i++)
    {
        if (poutines[i].first >= amount)
        {
            amountSpent += ((poutines[i].first - amount) / poutines[i].second) + 1;
        }

        if (amountSpent > T)
        {
            return T + 1;
        }
    }
    return amountSpent;
}