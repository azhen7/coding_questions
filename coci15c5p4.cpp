#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#define SWAP_SOL_USED 1

void determineHeights(std::vector<long long>& e, long long N, long long capacity);
void input();
void testCases();
void _testInputs(long long a, long long b);

int main()
{
    //testCases();
    input();
}

void input()
{
    std::string::size_type N, X;
    std::string inputs;
    std::getline(std::cin, inputs);

    std::string::size_type space = inputs.find(' ');
    N = std::stoull(inputs.substr(0, space));
    X = std::stoull(inputs.substr(space + 1));

    std::vector<long long> columnHeights;

    determineHeights(columnHeights, N, X);

    for (const long long x : columnHeights)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

void determineHeights(std::vector<long long>& e, long long N, long long capacity)
{
    long long currentCapacity = 0;

    // long long isPossible = 0;
    // for (long long i = N - 2; i >= 1; i--)
    // {
    //     isPossible += i;
    // }
    // std::cout << isPossible << '\n';
    // if (isPossible < capacity)
    // {
    //     e.push_back(-1);
    //     return;
    // }
    
    e.push_back(N);

    //If capacity is less than N-1 column, it can be reached with just 1 column
    if (capacity < N - 1)
    {
        e.push_back((N - 1) - capacity);
        e.push_back(N - 1);

        for (long long i = N - 2; i >= 1; i--)
        {
            if (i == (N - 1) - capacity) continue;
            e.push_back(i);
        }
        return;
    }

    long long i;
    //Start pushing columns
    for (i = 1; currentCapacity < capacity && i < N - 1; i++)
    {
        e.push_back(i);
        currentCapacity += N - 1 - i;
    }
    // Cannot add more water (since all columns are used) -> capacity is unreachable
    if (currentCapacity < capacity)
    {
        e.clear();
        e.push_back(-1);
        return;
    }

    e.push_back(N - 1); // N - 1 is "wall"

#if SWAP_SOL_USED

    //Push rest of columns in
    for (long long j = i; j <= N - 2; j++)
    {
        e.push_back(j);
    }
    //If current capacity is already met, reverse-sort last few columns
    if (currentCapacity == capacity) [[unlikely]]
    {
        std::sort(e.begin() + i, e.end(), [](long long a, long long b) {
            return a > b;
        });
        return;
    }
    else [[likely]]
    {
        long long indexOfSecondWall = i;

        //i is index of N-1 column, so decrementing it puts it at the last element before N-1
        while (--i > 0)
        {
            long long* max = &e[indexOfSecondWall + 1]; //starts with first number after N-1 column
            //iterate over elements after N-1 column
            for (long long j = indexOfSecondWall + 1; j < N; j++)
            {
                //get max column height to default-swap with without going over
                if (e[j] > *max && currentCapacity - e[j] >= capacity)
                {
                    max = &e[j];
                }

                //If current column to swap with eliminates all extra water, swap and leave
                if (currentCapacity - (e[j] - e[i]) == capacity)
                {
                    std::swap(e[i], e[j]);
                    currentCapacity = capacity;
                    goto skipOut;
                }

                //if no column height found which completely eliminates extra water
                if (j == N - 1)
                {
                    //Subtract difference between column max and current column
                    currentCapacity -= (*max - e[i]);

                    //Swap
                    long long temp = *max;
                    e.insert(e.begin() + indexOfSecondWall, e[i]); //Insert e[i] after N-1 wall
                    std::remove(e.begin(), e.end(), *max); //Remove element pointed to by max (no ambiguity, since all elements are unique)
                    e[i] = temp;
                }
            }
        }
    
    skipOut:
        if (currentCapacity > capacity)
        {
            e.clear();
            e.push_back(-1);
            return;
        }
        //Reverse-sort all column heights after N-1 column
        std::sort(e.begin() + indexOfSecondWall, e.end(), [](long long a, long long b) {
            return a > b;
        });
        return;
    }

#else

    if (currentCapacity > capacity)
    {
        long long diff = currentCapacity - capacity;
        //Accounts for complete iterations through all the columns
        for (long long copy = i - 1; copy >= 1; copy--)
        {
            long long dividedDiff = (long long) (diff / (i - 1));

            //Divide difference between currentCapacity and capacity by (i - 1), then increase each column by that much
            //More efficient than incrementing by 1, and running over the numbers a lot of times
            e[copy] += dividedDiff;

            //No way to continue reducing currentCapacity - capacity is unreachable
            if (e[copy] >= N - 1)
            {
                e.clear();
                e.push_back(-1);
                return;
            }
            currentCapacity -= dividedDiff;
        }

        //(currentCapacity - capacity) % (i - 1) accounts for incomplete iterations
        for (long long copy = i - 1, j = 1; copy >= 1 && j <= diff % (i - 1); copy--)
        {
            e[copy]++;

            //No way to continue reducing currentCapacity - capacity is unreachable
            if (e[copy] >= N - 1)
            {
                e.clear();
                e.push_back(-1);
                return;
            }

            currentCapacity--;

            j++;
        }

        // Insert rest of columns in descending order
        for (long long j = N - 2; j >= 1; j--)
        {
            if (std::find(e.begin(), e.end(), j) == e.end())
            {
                e.push_back(j);
            }
        }
    }
    else if (currentCapacity == capacity)
    {
        // Insert rest of columns in descending order
        // No further action needed (since capacity has already been met with subset of bars)
        for (long long j = N - 2; j >= i; j--)
        {
            e.push_back(j);
        }
    }

#endif
}











void testCases()
{
    _testInputs(9, 10);
    _testInputs(5, 4);
    _testInputs(90, 4);
    _testInputs(50, 40);
    _testInputs(90, 80);
    _testInputs(73, 15);
    _testInputs(73, 75);
    _testInputs(10, 35);
    _testInputs(100, 304);
    _testInputs(23, 59);
    _testInputs(34, 69);
    _testInputs(69, 420);
    _testInputs(49, 81);
    _testInputs(58, 199);
    _testInputs(43, 54);
    _testInputs(100, 2048);
    _testInputs(50, 100);
    _testInputs(64, 69);
    _testInputs(100, 690);
    _testInputs(100, 98);
    _testInputs(80, 93);
    _testInputs(104, 12);
    _testInputs(199, 398);
    _testInputs(481, 249);
    _testInputs(1, 5);
    _testInputs(4, 9);
}

void _testInputs(long long a, long long b)
{
    std::vector<long long> in;
    determineHeights(in, a, b);

    long long isPossible = 0;
    for (long long i = a - 2; i >= 1; i--)
    {
        isPossible += i;
    }
    if (isPossible < b)
    {
        if (in.size() == 1 && in[0] == -1)
        {
            std::cout << "Valid output\n\n";
        }
        else
        {
            std::cout << "Invalid\n";
        }
        return;
    }

    std::cout << "Output: ";
    for (const long long test : in)
    {
        std::cout << test << ' ';
    }
    std::cout << '\n';

    //Find column of N-1
    auto it = std::find(in.begin(), in.end(), a - 1);
    long long count = 0;
    
    //Add water (difference between height of water (which is N - 1) and current column)
    for (auto start = in.begin() + 1; start != it; start++)
    {
        count += (a - 1) - *start;
    }

    //If water added is not equal to b (which is water to aim for), the result is invalid
    if (count != b)
    {
        std::cout << "Invalid\n";
        return;
    }

    //Verify columns after N-1 are in descending order
    ++it;
    while (++it != in.end())
    {
        if (*it >= *(it - 1))
        {
            std::cout << "Columns after N-1 not in order\n";
            return;
        }
    }
    std::cout << "Valid output\n\n";
}