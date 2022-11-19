#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

bool isPrime(long n)
{
    // Check if n=1 or n=0
    if (n <= 1)
        return false;

    // Check if n=2 or n=3
    if (n == 2 || n == 3)
        return true;

    // Check whether n is divisible by 2 or 3
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    // Check from 5 to square root of n
    // Iterate i by (i+6)
    for (long i = 5; i <= std::sqrt(n); i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

long L, R;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> L;
    std::cin >> R;

    long before = -1;

    long count = 1;
    if (L > 3)
    {
        count++;
    }

    long lookdir = 1;

    for (long i = (L % 2 == 0) ? (L + 1) : L; i < R; i += 2)
    {
        if (isPrime(i))
        {
            before = i;
            count++;
            break;
        }
    }

    if (before != -1)
    {
        if ((before - 1) % 6 == 0)
        {
            lookdir = -1;
        }
        if (before == 3)
        {
            before = 5;
        }
        for (long i = before; i < R; i += 6)
        {
            if (isPrime(i))
            {
                count++;
            }
            if (isPrime(i + 2 * lookdir))
            {
                count++;
            }
        }
    }

    std::cout << count << '\n';
}