#include <iostream>
#include <stack>
#include <vector>

typedef unsigned long long ULL;

std::vector<ULL> people;
ULL numberOfPeople;

ULL determineNumberOfPairs();

int main()
{
    std::cin >> numberOfPeople;

    for (ULL i = 0; i < numberOfPeople; i++)
    {
        ULL a;
        std::cin >> a;
        people.push_back(a);
    }

    std::cout << determineNumberOfPairs() << '\n';
}

ULL determineNumberOfPairs()
{
    //std::stack<ULL> peopleStack;
    ULL numberOfPeopleWhoCanSeeEachOther = 0ULL;

    for (ULL i = 0; i < numberOfPeople - 1; i++)
    {
        if (people[i] < people[i + 1])
        {
            numberOfPeopleWhoCanSeeEachOther++;
            continue;
        }
        ULL tallestPersonBetweenIAndJ = 0ULL;
        for (ULL j = i + 1; j < numberOfPeople; j++)
        {
            if (people[j] >= tallestPersonBetweenIAndJ && people[i] >= tallestPersonBetweenIAndJ)
            {
                tallestPersonBetweenIAndJ = people[j];
                numberOfPeopleWhoCanSeeEachOther++;
            }
        }
    }

    return numberOfPeopleWhoCanSeeEachOther;
}