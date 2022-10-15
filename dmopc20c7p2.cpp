#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>

typedef long long LL;

struct vertex
{
    LL x;
    LL y;
    mutable bool hasBeenCovered;

    vertex(LL a, LL b)
    {
        x = a;
        y = b;
        hasBeenCovered = false;
    }

    void setHasBeenCovered() const
    {
        hasBeenCovered = true;
    }

    bool operator<(const vertex& c) const
    {
        return this->x < c.x || (!(c.x < this->x) && this->y < c.y);
    }
};

bool operator==(vertex a, vertex b)
{
    return a.x == b.x && a.y == b.y;
}

LL numberOfTiles;
std::vector<vertex> vertices;

std::vector<vertex> getVertices();

short SQUARE = 1;
short OCTAGON = 0;

int main()
{
    std::cin >> numberOfTiles;

    for (LL i = 0; i < numberOfTiles; i++)
    {
        LL a, b;
        std::cin >> a >> b;
        vertices.push_back(vertex(a, b));
    }

    auto ret = getVertices();

    std::cout << ret.size() << '\n';
    for (auto e : ret)
    {
        std::cout << e.x << ' ' << e.y << '\n';
    }
}

void removeAllElementsWithDuplicates(std::multiset<vertex>& a)
{
    for (auto it = a.begin(); it != a.end(); )
    {
        auto res = it;

        unsigned long long amountOfIncrement = 0ULL;
        ++it;
        while (it != a.end() && *it == *res)
        {
            amountOfIncrement++;
            ++it;
        }

        if (amountOfIncrement > 1)
        {
            it = a.erase(res, it);
        }
        else if (amountOfIncrement == 1)
        {
            it = a.erase(res);
        }
    }
}

bool is_divisible(LL a, LL b)
{
    if (b == 0)
    {
        return false;
    }
    return ((long double) a / b) == (a / b);
}

short determineShape(vertex a)
{
    LL y_level = a.y / 2;

    short res = -1;
    if (is_divisible(a.x, 4))
    {
        res = SQUARE;
        if (!is_divisible(y_level, 2))
        {
            res = OCTAGON;
        }
    }
    else
    {
        res = OCTAGON;
        if (!is_divisible(y_level, 2))
        {
            res = SQUARE;
        }
    }
    return res;
}

void lookForNext(std::multiset<vertex>& a, std::multiset<vertex>::iterator& it)
{
    auto look = a.find(vertex(it->x + 1, it->y));
    //to the right
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    look = a.find(vertex(it->x, it->y + 1));
    //above
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    look = a.find(vertex(it->x + 1, it->y + 1));
    //to the right and above
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    look = a.find(vertex(it->x, it->y - 1));
    //below
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    look = a.find(vertex(it->x + 1, it->y - 1));
    //to the right and below
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    //to the left
    look = a.find(vertex(it->x - 1, it->y));
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    //to the left and above
    look = a.find(vertex(it->x - 1, it->y + 1));
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    //to the left and below
    look = a.find(vertex(it->x - 1, it->y - 1));
    if (look != a.end() && !look->hasBeenCovered)
    {
        it = look;
        it->setHasBeenCovered();
        return;
    }

    it = a.end();
}

std::vector<vertex> getVertices()
{
    std::multiset<vertex> ret;

    LL i = 0;
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        short shape = determineShape(*it);

        if (shape == OCTAGON)
        {
            //octagon
            ret.insert(vertex(it->x, it->y - 1));
            ret.insert(vertex(it->x - 1, it->y));
            ret.insert(vertex(it->x - 1, it->y + 1));
            ret.insert(vertex(it->x, it->y + 2));
            ret.insert(vertex(it->x + 1, it->y + 2));
            ret.insert(vertex(it->x + 2, it->y + 1));
            ret.insert(vertex(it->x + 2, it->y));
            ret.insert(vertex(it->x + 1, it->y - 1));
        }
        else
        {
            ret.insert(*it);
            ret.insert(vertex(it->x, it->y + 1));
            ret.insert(vertex(it->x + 1, it->y + 1));
            ret.insert(vertex(it->x + 1, it->y));
        }
        i++;
    }

    removeAllElementsWithDuplicates(ret);

    std::vector<vertex> clockWise;
    std::multiset<vertex>::iterator prev = ret.begin();

    clockWise.push_back(*prev);

    unsigned long long j = 0;

    while (++j < ret.size())
    {
        lookForNext(ret, prev);
        clockWise.push_back(*prev);
    }
    

    return clockWise;
}