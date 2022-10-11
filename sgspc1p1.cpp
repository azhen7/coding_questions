#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>
#include <deque>

typedef unsigned long UL;

constexpr UL BIT_SIZE = 32;

//std::vector<std::bitset<BIT_SIZE>> binaryRepresentations;

std::vector<UL> vset;

UL N;

UL determineXORVal();

int main()
{
    std::cin >> N;
    //binaryRepresentations.reserve(N);
    
    for (UL i = 0; i < N; i++)
    {
        UL a;
        std::cin >> a;
        //binaryRepresentations[i] = std::bitset<BIT_SIZE>(a);
        vset.push_back(a);
    }

    std::cout << determineXORVal() << '\n';
}

UL determineXORVal()
{
    //std::deque<char> strBit;
    UL ret = 0;
    for (UL i = 0; i < BIT_SIZE; i++)
    {
        UL count = 0;
        UL checkbit = 1 << i;
        for (UL j = 0; j < N; j++)
        {
            if (vset[j] & checkbit)
            {
                count++;
            }
            //count += binaryRepresentations[j].test(i);
        }
        if ((2 * count) <= N)
        {
            //strBit.push_front('0');
        }
        else
        {
            ret |= checkbit;
            //strBit.push_front('1');
        }
    }
    return ret;

    //return std::bitset<BIT_SIZE>(std::string(strBit.begin(), strBit.end())).to_ulong();
}