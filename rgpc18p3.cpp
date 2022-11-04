#include <iostream>
#include <vector>

typedef long long LL;

LL numberOfFillOps;
LL numberOfCups;
LL maxBound;

std::vector<LL> cups;
std::vector<LL> diff;

bool windowWorks(LL amount)
{
    LL elemSum = 0;
    for (LL i = 0; i < amount; i++)
    {
        elemSum += cups[i];
    }
    if (elemSum <= maxBound)
    {
        return true;
    }

    for (LL i = 1; i < numberOfCups - amount + 1; i++)
    {
        elemSum -= cups[i - 1];
        elemSum += cups[i + amount - 1];
        if (elemSum <= maxBound)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::cin >> numberOfCups >> numberOfFillOps;
    cups.assign(numberOfCups, 0);
    diff.assign(numberOfCups + 1, 0);

    for (LL i = 0; i < numberOfFillOps; i++)
    {
        LL start, end, amount;
        std::cin >> start >> end >> amount;
        
        diff[start - 1] += amount;
        diff[end] -= amount;
    }

    cups[0] = diff[0];
    for (LL i = 1; i < numberOfCups; i++)
    {
        cups[i] = diff[i] + cups[i - 1];
    }

    std::cin >> maxBound;

    LL maxWindow = 1;

    while (windowWorks(maxWindow))
    {
        maxWindow++;
    }

    std::cout << maxWindow - 1 << '\n';
}