#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long int_type;

void input();
std::vector<int> parseMeteorLine(std::string e);
int determineSideLengthOfTarp(meteors v, int speed);

struct meteors
{
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> time;

    void pushVector(std::vector<int> e)
    {
        x.push_back(x[0]);
        y.push_back(x[1]);
        time.push_back(x[2]);
    }
};

int main()
{
    input();
}

int determineSideLengthOfTarp(meteors v, int speed)
{
    int sideLength = 0;

    int x = v.x[0];
    int y = v.y[0];

    if (speed == 0)
    {
        
    }
}

void input()
{
    std::string in;
    std::getline(std::cin, in);

    std::string::size_type n, K;
    std::string::size_type space = in.find(' ');
    n = std::stoull(in.substr(0, space));
    K = std::stoull(in.substr(space + 1));

    meteors allInputs;

    std::vector<std::string> test;
    for (std::string::size_type i = 0; i < n; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        test.push_back(line);

        allInputs.pushVector(parseMeteorLine(line));
    }

    determineSideLengthOfTarp(allInputs, K);
}

std::vector<int> parseMeteorLine(std::string e)
{
    std::vector<int> lines{0, 0, 0};

    int j = 0;
    for (auto i = 0; i < e.length() && j < lines.size(); i++)
    {
        if (e[i] == ' ')
        {
            lines[j] /= 10;
            j++;
        }
        else
        {
            lines[j] += e[i] - '0';
            lines[j] *= 10;
        }
    }
    return lines;
}