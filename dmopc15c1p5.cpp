#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

typedef long long int_type;
typedef std::vector<int_type> vector_type;

//Global vars
std::vector<std::vector<int_type>> scales;
std::vector<std::vector<int_type>> prefixSum;
int_type width;
int_type height;
int_type areaToSearch;

//Function declarations
void parseScales(std::string str);
int_type determineMaxScales();
int_type bruteForce(int_type startX, int_type startY, int_type subsectionWidth, int_type subsectionHeight);
void calculatePrefixSum();
int_type calculateSumOfScalesInSubsection(int_type a, int_type b, int_type c, int_type d);
void parseInput(std::string str);
void parseScales(std::string str);
vector_type determineAllFactors();

int main()
{
    std::string in;
    std::getline(std::cin, in);
    parseInput(in);

    for (int_type i = 0; i < height; i++)
    {
        std::string input;
        std::getline(std::cin, input);
        parseScales(input);
    }

    calculatePrefixSum();

    std::cout << determineMaxScales() << '\n';
}

int_type determineMaxScales()
{
    vector_type factors = determineAllFactors();
    std::set<int_type> allSums;
    for (vector_type::size_type index = 0; index < factors.size(); index += 2)
    {
        for (vector_type::size_type i = 0; i < height; i++)
        {
            for (vector_type::size_type j = 0; j < width; j++)
            {
                if (i + factors[index] - 1 < width && j + factors[index + 1] - 1 < height)
                {
                    allSums.insert(bruteForce(i, j, factors[index] - 1, factors[index + 1] - 1));
                }
                if (i + factors[index + 1] - 1 < height && j + factors[index] - 1 < width)
                {
                    allSums.insert(bruteForce(i, j, factors[index + 1] - 1, factors[index] - 1));
                }
                else
                {
                    break;
                }
            }
        }
    }

    return *std::max_element(allSums.begin(), allSums.end());
}

vector_type determineAllFactors()
{
    vector_type factors;
    for (int_type i = 1; i <= static_cast<int_type>(std::sqrt(areaToSearch)); i++)
    {
        if (areaToSearch % i == 0)
        {
            factors.push_back(i);
            factors.push_back(areaToSearch / i);
        }
    }
    return factors;
}

int_type bruteForce(int_type startX, int_type startY, int_type subsectionWidth, int_type subsectionHeight)
{
    int_type res = calculateSumOfScalesInSubsection(startX, startY, startX + subsectionWidth, startY + subsectionHeight);
    return res;
}

void calculatePrefixSum()
{
    //initialize prefix sum
    for (int_type i = 0; i < height; i++)
    {
        prefixSum.push_back(vector_type(width, 0));
    }

    for (int_type i = 0; i < height; i++)
    {
        int_type diffOfPreviousAbove = 0;
        int_type prev = 0;
        for (int_type j = 0; j < width; j++)
        {
            if (j > 0)
            {
                prev = prefixSum[i][j - 1];
            }
            if (i > 0)
            {
                diffOfPreviousAbove = prefixSum[i - 1][j];
                if (j > 0)
                {
                    diffOfPreviousAbove -= prefixSum[i - 1][j - 1];
                }
            }
            prefixSum[i][j] = scales[i][j] + prev + diffOfPreviousAbove;
        }
    }
}

/**
 * @param a Lower bound on x
 * @param b Upper bound on y
 * @param c Upper bound on x
 * @param d Lower bound on y 
 * @return int_type
 */
int_type calculateSumOfScalesInSubsection(int_type a, int_type b, int_type c, int_type d)
{
    if (a > width || b > height || c > width || d > height)
    {
        return -1;
    }

    int_type subtractLeft = 0;
    int_type subtractTop = 0;
    int_type addTopLeft = 0;

    if (a > 0)
    {
        subtractLeft = prefixSum[a - 1][d];
    }
    if (b > 0)
    {
        subtractTop = prefixSum[c][b - 1];
    }
    if (a > 0 && b > 0)
    {
        addTopLeft = prefixSum[a - 1][b - 1];
    }

    return prefixSum[c][d] - subtractLeft - subtractTop + addTopLeft;
}

void parseInput(std::string str)
{
    vector_type lines(3, 0);
    int_type j = 0;
    for (std::size_t i = 0; i < str.length() && j < 3; i++)
    {
        if (str[i] == ' ')
        {
            lines[j] /= 10;
            j++;
        }
        else
        {
            lines[j] += str[i] - '0';
            lines[j] *= 10;
        }
    }
    lines[2] /= 10;

    width = lines[0];
    height = lines[1];
    areaToSearch = lines[2];
}

void parseScales(std::string str)
{
    vector_type lines(width, 0);
    int_type j = 0;
    for (std::size_t i = 0; i < str.length() && j < width; i++)
    {
        if (str[i] == ' ')
        {
            lines[j] /= 10;
            j++;
        }
        else
        {
            lines[j] += str[i] - '0';
            lines[j] *= 10;
        }
    }
    lines[width - 1] /= 10;

    scales.push_back(lines);
}