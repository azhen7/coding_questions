#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

typedef unsigned long long ULL;

std::string simplifyExplosions(std::string, std::string);

const std::string EMPTY = "";
const std::string FAILURE = "FRULA";

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::string in;
    std::string explosion;

    std::getline(std::cin, in);
    std::getline(std::cin, explosion);

    std::cout << simplifyExplosions(in, explosion) << '\n';
}

std::string simplifyExplosions(std::string s, std::string explosionS)
{
    if (explosionS.length() == 1)
    {
        s.erase(std::remove(s.begin(), s.end(), explosionS[0]), s.end());
        if (s == EMPTY)
        {
            return FAILURE;
        }
        return s;
    }

    while (true)
    {
        if (explosionS.length() > s.length())
        {
            break;
        }
        if (explosionS.length() == s.length())
        {
            if (explosionS == s)
            {
                return FAILURE;
            }
            break;
        }
        // auto firstExplosionStrLocation = std::search(s.begin(), s.end(), explosionS.begin(), explosionS.end());
        // if (firstExplosionStrLocation == s.end())
        // {
        //     break;
        // }
        // else
        // {
        //     s.erase(firstExplosionStrLocation, firstExplosionStrLocation + explosionS.length());
        // }
        bool foundMatch = false;
        for (ULL i = 0; i < s.length(); i++)
        {
            if (s[i] == explosionS[0])
            {
                bool match = true;

                ULL j;
                for (j = i + 1; j < (i + explosionS.length()) && j < s.length(); j++)
                {
                    if (s[j] != explosionS[j - i])
                    {
                        match = false;
                        break;
                    }
                }

                if (j == s.length() && j < (i + explosionS.length()))
                {
                    match = false;
                }

                if (match)
                {
                    s.erase(s.begin() + i, s.begin() + j);
                }
                else
                {
                    if (j > i)
                    {
                        i = j - 1;
                    }
                }

                if (!foundMatch)
                {
                    foundMatch = match;
                }
            }
        }

        if (s == EMPTY)
        {
            return FAILURE;
        }

        if (!foundMatch)
        {
            break;
        }
    }
    return s;
}