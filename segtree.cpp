#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <string>
#include <algorithm>
#include <sstream>

typedef unsigned long long ULL;

ULL numberOfElems;
ULL numberOfQueries;

ULL BLOCK_LEN;

std::vector<ULL> elems;
std::vector<ULL> minOfEachBlock;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> numberOfElems >> numberOfQueries;
    BLOCK_LEN = (ULL) std::sqrt(numberOfElems);
    elems.assign(numberOfElems, 0);

    ULL indexInBlock = 0;
    ULL currentMin = -1;

    for (ULL i = 0; i < numberOfElems; i++)
    {
        std::cin >> elems[i];

        //square root decomposition
        //if we are still iterating through a block, keep going
        if (indexInBlock < BLOCK_LEN)
        {
            currentMin = std::min(currentMin, elems[i]);
            indexInBlock++;
        }
        //if we have finished iterating over a block, add that block's minimum to @var minOfEachBlock
        else
        {
            minOfEachBlock.push_back(currentMin);
            currentMin = elems[i];
            indexInBlock = 1;
        }
    }

    minOfEachBlock.push_back(currentMin);

    char queryType;
    ULL queryParam1, queryParam2;

    std::stringstream res;

    for (ULL i = 0; i < numberOfQueries; i++)
    {
        std::cin >> queryType >> queryParam1 >> queryParam2;

        switch (queryType)
        {
            //find min query
            case 'Q':
            {
                ULL startOfBlock1 = queryParam1 / BLOCK_LEN;
                ULL startOfBlock2 = queryParam2 / BLOCK_LEN;

                ULL m = -1;

                //if upper and lower bounds are located in same block, manually calculate min value
                if (startOfBlock1 == startOfBlock2)
                {
                    for (ULL i = queryParam1; i <= queryParam2; i++)
                    {
                        m = std::min(m, elems[i]);
                    }
                }
                else
                {
                    for (ULL i = queryParam1; i < (startOfBlock1 + 1) * BLOCK_LEN; i++)
                    {
                        m = std::min(m, elems[i]);
                    }
                    for (ULL i = startOfBlock1 + 1; i < startOfBlock2; i++)
                    {
                        m = std::min(m, minOfEachBlock[i]);
                    }
                    for (ULL i = startOfBlock2 * BLOCK_LEN; i <= queryParam2; i++)
                    {
                        m = std::min(m, elems[i]);
                    }
                }

                res << m << '\n';

                break;
            }
            //update element query
            case 'M':
            {
                elems[queryParam1] = queryParam2;
                ULL startOfBlockBefore = queryParam1 / BLOCK_LEN;
                minOfEachBlock[startOfBlockBefore] = *std::min_element(elems.begin() + startOfBlockBefore * BLOCK_LEN, elems.begin() + (startOfBlockBefore + 1) * BLOCK_LEN);
                break;
            }
            default:
            {
                return 1;
            }
        }
    }
    std::cout << res.str();
    return 0;
}