//NOT DONE

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long LL;
LL N;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N;

    if (N <= 6)
    {
        std::vector<LL> indices;
        indices.reserve(3);

        for (LL i = 0; i < 3; i++)
        {
            std::cout << "$ " << N << ' ';
            for (LL i = 0; i < N; i++)
            {
                std::cout << i << ' ';
            }
            std::cout << (1 << i) << '\n' << std::flush;

            std::cin >> indices[i];
        }

        std::cout << "! ";
        for (LL i = 0; i < 3; i++)
        {
            std::cout << indices[i];
            if (i < 2)
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';

        return 0;
    }
}