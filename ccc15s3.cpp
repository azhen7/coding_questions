#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <unordered_set>
typedef unsigned long long ULL;

ULL numberOfGates;
ULL numberOfPlanes;

std::vector<ULL> planeGates;

ULL determineNumberOfPlanesThatLand();

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> numberOfGates;
    std::cin >> numberOfPlanes;

    for (ULL i = 0; i < numberOfPlanes; i++)
    {
        ULL a;
        std::cin >> a;
        planeGates.push_back(a);
    }

    std::cout << determineNumberOfPlanesThatLand() << '\n';
}

ULL determineNumberOfPlanesThatLand()
{
    ULL amount = 0;
    std::map<ULL, std::vector<ULL>::iterator> gatesConsumed;

    for (ULL i = 0; i < planeGates.size(); i++)
    {
        auto insertElem = std::make_pair(planeGates[i], planeGates.begin() + planeGates[i] - 1);
        if (i == 0)
        {
            gatesConsumed.insert(insertElem);
        }
        else
        {
            auto it = gatesConsumed.find(planeGates[i]);
            if (it == gatesConsumed.end())
            {
                gatesConsumed.insert(insertElem);
            }
            else
            {
                auto fromEnd = it;
                if (fromEnd == gatesConsumed.begin())
                {
                    if (fromEnd->second == planeGates.begin())
                    {
                        return amount;
                    }
                }
                else
                {
                    fromEnd--;
                    while (std::distance(fromEnd->second, std::next(fromEnd)->second) == 1)
                    {
                        if (fromEnd->second == planeGates.begin())
                        {
                            return amount;
                        }
                        fromEnd--;
                    }
                    fromEnd++;
                }

                auto t = std::make_pair(
                    planeGates[i] - ((planeGates.begin() + planeGates[i]) - fromEnd->second),
                    fromEnd->second - 1
                );
                gatesConsumed.insert(t);
            }
        }
        amount++;
    }
    return amount;
}

// ULL determineNumberOfPlanesThatLand()
// {
//     std::sort(planeGates.begin(), planeGates.end(), [](ULL a, ULL b)
//     {
//         return a > b;
//     });

//     std::vector<bool> a(numberOfGates, false);

//     ULL amount = 0;
//     ULL nextIndex = numberOfGates - 1;
//     for (ULL i = 0; i < numberOfPlanes; i++)
//     {
//         if (nextIndex == -1)
//         {
//             return amount;
//         }

//         ULL indexToInsertAt = std::min(nextIndex, planeGates[i]);
//         if (a[indexToInsertAt])
//         {
//             return amount;
//         }

//         a[indexToInsertAt] = true;
//         nextIndex--;
//         amount++;
//     }
//     return amount;
// }

// std::set<ULL> occupied;

// ULL determineNumberOfPlanesThatLand()
// {
//     ULL amount = 0;
//     for (ULL i = 0; i < numberOfPlanes; i++)
//     {
//         ULL max = planeGates[i];
//         while(occupied.find(max) != occupied.end())
//         {
//             max--;
//         }
//         if(max != 0)
//         {
//             amount++;
//             occupied.insert(max);
//         }
//         else
//         {
//             return amount;
//         }

//         // for (ULL j = planeGates[i] - 1; ; j--)
//         // {
//         //     if (!gatesLeft[j])
//         //     {
//         //         gatesLeft[j] = true;
//         //         amount++;
//         //         break;
//         //     }
//         //     if (j == 0)
//         //     {
//         //         return amount;
//         //     }
//         // }

//     }
//     return amount;
// }

// ULL determineNumberOfPlanesThatLand()
// {
//     ULL amount = 0ULL;
//     ULL countFromLeft = 0ULL, maxGate = 0ULL;

//     ULL count = 1;
//     for (ULL i = 0; i < numberOfPlanes; i++)
//     {
//         if (planeGates[i] > maxGate)
//         {
//             maxGate = planeGates[i];
//         }
//         if (countFromLeft == maxGate)
//         {
//             return amount;
//         }
//         //count number of gates occupied from left
        
//     }
// }
