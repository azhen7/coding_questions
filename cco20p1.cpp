#include <iostream>
#include <cmath>
#include <vector>

typedef long long LL;

LL lowerBound;
LL upperBound;
LL Y;
LL numberOfFriends;

struct Friend
{
    LL x;
    LL v;
    LL h;
    LL leftLineIntersect;

    Friend(LL a, LL b, LL c)
    {
        x = a;
        v = b;
        h = c;
        leftLineIntersect = v * x;
    }

    bool pointCanBeSeen(LL inX) const
    {
        return ((-1 * v * inX + leftLineIntersect) < Y * h) && ((v * inX - leftLineIntersect) < Y * h);
    }

    // LL minXVisible()
    // {
    //     return std::ceil((h * Y - leftLineIntersect) / (v * -1));
    // }
    
    // LL maxXVisible()
    // {
    //     return std::floor((h * Y + leftLineIntersect) / v);
    // }
};

struct FriendComparator
{
    constexpr bool operator()(const Friend& a, const Friend& b) const
    {
        return a.x < b.x;
    }
};

std::vector<LL> nums;

int main()
{
    std::cin >> numberOfFriends;
    std::cin >> lowerBound >> upperBound >> Y;

    nums.assign(numberOfFriends + 1, 0);

    std::vector<Friend> friends;

    for (LL i = 0; i < numberOfFriends; i++)
    {
        LL a, b, c;
        std::cin >> a >> b >> c;

        friends.push_back(Friend(a, b, c));
    }

    for (LL i = 0; i < numberOfFriends + 1; i++)
    {
        LL numberOfPoints = 0;
        for (LL x = lowerBound; x <= upperBound; x++)
        {
            LL count = 0;
            for (auto it = friends.begin(); it != friends.end(); it++)
            {
                count += it->pointCanBeSeen(x);
            }
            if (count <= i)
            {
                numberOfPoints++;
            }
        }
        nums[i] = numberOfPoints;
    }

    for (const LL& e : nums)
    {
        std::cout << e << '\n';
    }
}