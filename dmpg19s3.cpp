#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <map>

typedef unsigned long long LL;

LL numberOfComponents;
const std::string LEFT_BRACKET(1, '(');
const std::string RIGHT_BRACKET(1, ')');
LL mod = 1000000007;


std::map<std::string, LL> determineSolution(std::vector<std::pair<std::string, LL>> &);
std::vector<std::pair<std::string, LL>> parse(std::string a);

int main()
{
    std::cin >> numberOfComponents;
    std::cin.ignore();

    std::string componentStr;
    std::getline(std::cin, componentStr);

    auto res = parse(componentStr);
    auto mapRes = determineSolution(res);

    for (auto it = mapRes.begin(); it != mapRes.end(); it++)
    {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}

std::vector<std::pair<std::string, LL>> parse(std::string a)
{
    std::vector<std::pair<std::string, LL>> res;
    for (std::string::size_type i = 0; i < a.length(); i++)
    {
        if (std::isalpha(a[i]))
        {
            std::string nameToInsert(1, a[i]);
            i++;
            while (a[i] != ' ')
            {
                nameToInsert += a[i];
                i++;
            }
            LL amount = 0ULL;
            if (std::isdigit(a[i + 1]))
            {
                i++;
                auto space = a.find(' ', i);
                amount = std::stoull(a.substr(i, space)) % mod;
            }
            res.push_back(std::make_pair(nameToInsert, amount));
        }
        else if (a[i] == '(')
        {
            res.push_back(std::make_pair(LEFT_BRACKET, -1));
        }
        else if (a[i] == ')')
        {
            i++;
            LL amount = 0ULL;
            if (std::isdigit(a[i + 1]))
            {
                i++;
                auto space = a.find(' ', i);
                amount = std::stoull(a.substr(i, space)) % mod;
            }
            res.push_back(std::make_pair(RIGHT_BRACKET, amount));
        }
    }

    return res;
}

std::map<std::string, LL> determineSolution(std::vector<std::pair<std::string, LL>> &a)
{
    for (LL index = 0LL; index < a.size(); index++)
    {
        if (a[index].first == RIGHT_BRACKET)
        {
            auto inner = a.begin() + index;
            inner--;
            for ( ; inner->first != LEFT_BRACKET; inner--)
            {
                inner->second = (inner->second * a[index].second)%mod;
            }
            a.erase(a.begin() + index);
            a.erase(inner);
            index -= 2;
        }
    }

    std::map<std::string, LL> ret;
    for (std::pair<std::string, LL> elem : a)
    {
        if (ret.find(elem.first) == ret.end())
        {
            ret.insert(elem);
        }
        else
        {
            ret[elem.first] += elem.second;
        }
    }

    for (auto &item:ret)
    {
        item.second %= mod;
    }

    return ret;
}

