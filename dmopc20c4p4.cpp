#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

typedef unsigned long long ULL;

std::vector<ULL> befores;

ULL least(ULL numberOfThrows);

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    ULL N;
    std::cin >> N;

    befores.reserve(N);
    for (ULL i = 0; i < N; i++)
    {
        std::cin >> befores[i];
    }

    for (ULL i = 1; i <= N; i++)
    {
        std::cout << least(i);
        if (i < N)
        {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

ULL least(ULL numberOfThrows)
{
    if (numberOfThrows == 1)
    {
        return 0ULL;
    }

    ULL ret = 0ULL;
    
    if (std::all_of(befores.begin(), befores.begin() + numberOfThrows, [](ULL i){ return i == 0ULL; }))
    {
        return 0ULL;
    }
    
    if (befores[numberOfThrows - 1] == numberOfThrows - 1)
    {
        for (ULL i = 0; i < numberOfThrows; i++)
        {
            ret += i - befores[i];
        }
        return ret;
    }
 
    ULL numberOfHolesCreated = 0ULL;

    std::stack<ULL> mostRecentOption1s;

    for (ULL i = 0; i < numberOfThrows; i++)
    {
        ULL insert = befores[i];

        if (i > 0)
        {
            //if we are inserting throw between holes
            if (numberOfHolesCreated > befores[i])
            {
                if (i < numberOfThrows - 1)
                {
                    if (befores[i + 1] > numberOfHolesCreated)
                    {
                        numberOfHolesCreated++;
                    }
                    else
                    {
                        mostRecentOption1s.push(i);
                    }
                }
                ret += numberOfHolesCreated - 1 - insert;
                continue;
            }
            //if we need more holes, retroactively change throws that landed in previous holes to ones that make new holes
            else if (numberOfHolesCreated < befores[i])
            {
                while (numberOfHolesCreated < befores[i])
                {
                    ret += i - mostRecentOption1s.top();
                    numberOfHolesCreated++;
                    mostRecentOption1s.pop();
                }
                numberOfHolesCreated++;
                continue;
            }
            //otherwise, we are inserting a hole at the end
        }

        //will only need to increment number of holes since there will be no holes in front of the hole
        //we are inserting a hole at the end, after all
        numberOfHolesCreated++;
    }

    return ret;
}