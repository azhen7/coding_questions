#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

typedef unsigned long long ULL;
ULL numberOfOperationalMicrowaves;
ULL numberOfPeople;
ULL howMuchTimeToMicrowave;

//.first is when the person joins the line
//.second is for how long they microwave their food
std::vector<std::pair<ULL, ULL>> peopleStats;

ULL minTimeToWait();

int main()
{
    std::cin >> numberOfOperationalMicrowaves >> numberOfPeople >> howMuchTimeToMicrowave;

    for (ULL i = 0; i < numberOfPeople; i++)
    {
        ULL a, b;
        std::cin >> a >> b;
        peopleStats.push_back(std::make_pair(a, b));
    }

    std::cout << minTimeToWait() << '\n';
}

ULL minTimeToWait()
{
    ULL time = 0ULL;
    

    return time;
}