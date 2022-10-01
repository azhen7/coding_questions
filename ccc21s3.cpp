#include <iostream>
#include <vector>
#include <algorithm>

typedef long long LL;

LL numberOfFriends;

struct friendStats
{
    LL initialPos;
    LL walkingSpeed;
    LL hearingDist;

    friendStats()
        : initialPos(0ULL),
        walkingSpeed(0ULL),
        hearingDist(0ULL)
    {
    }

    friendStats(LL a, LL b, LL c)
    {
        initialPos = a;
        walkingSpeed = b;
        hearingDist = c;
    }
};

std::vector<friendStats> friends;

LL determineMinSumOfWalkingTimes();

int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    std::cin >> numberOfFriends;

    for (LL i = 0; i < numberOfFriends; i++)
    {
        LL a, b, c;
        std::cin >> a >> b >> c;

        friends.push_back(friendStats(a, b, c));
    }
    std::cout << determineMinSumOfWalkingTimes() << '\n';
}

LL determineMinSumOfWalkingTimes()
{
    auto it = std::minmax_element(friends.begin(), friends.end(), [](friendStats a, friendStats b)
    {
        return a.initialPos < b.initialPos;
    });
    LL range = it.second->initialPos - it.first->initialPos + 1;

    std::vector<LL> times;
    
    for (LL i = 0; i < range; i++)
    {
        LL amount = 0ULL;
        for (LL j = 0; j < friends.size(); j++)
        {
            auto dist = std::abs(it.first->initialPos + i - friends[j].initialPos);
            if (dist > friends[j].hearingDist)
            {
                amount += (dist - friends[j].hearingDist) * friends[j].walkingSpeed;
            }
        }
        times.push_back(amount);
    }
    return *std::min_element(times.begin(), times.end());
}