#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

typedef unsigned long long ULL;

ULL numberOfElems;
ULL numberOfOps;

std::vector<ULL> elems;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> numberOfElems >> numberOfOps;

    elems.reserve(numberOfElems);

    for (ULL i = 0; i < numberOfElems; i++)
    {
        std::cin >> elems[i];
    }

    std::stringstream result;

    for (ULL i = 0; i < numberOfOps; i++)
    {
        char c;
        std::cin >> c;
        if (c == '1')
        {
            ULL l, r, mod;
            std::cin >> l >> r >> mod;
            l--;
            r--;

            ULL count = 0;
            for (ULL j = l; j <= r; j++)
            {
                if (elems[j] % mod == 0)
                {
                    count++;
                }
            }
            result << count << '\n';
        }
        else
        {
            ULL index;
            ULL update;
            std::cin >> index >> update;

            elems[index - 1] = update;
        }
    }

    std::cout << result.str();
}