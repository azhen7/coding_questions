#include <iostream>

typedef unsigned long long ULL;

ULL numberOfElements;
ULL mod;
ULL value;
ULL maxPowerOfTwo;

ULL calculateXorMult(ULL val);
ULL chooseOneOrMore();

int main()
{
    std::cin >> numberOfElements >> mod >> maxPowerOfTwo >> value;

    ULL andElems = 1;
    ULL orElems = 1;
    ULL xorElems = 1;

    while (value > 0)
    {
        ULL currentBit = value & 1;

        if (currentBit == 1)
        {
            //and
            //all corresponding bits must be 1, so this adds no additional variations

            //or
            //number of ways to choose at least one bit set to 1
            orElems = (orElems * chooseOneOrMore()) % mod;
        }
        else
        {
            //and
            //number of ways to choose at least one bit set to 0
            andElems = (andElems * chooseOneOrMore()) % mod;

            //or
            //all corresponding bits must be 0, so this adds no additional variations
        }

        //xor
        xorElems = (xorElems * calculateXorMult(currentBit)) % mod;

        value >>= 1;
    }

    std::cout << xorElems << '\n';
    std::cout << orElems << '\n';
    std::cout << andElems << '\n';
}

ULL calculateXorMult(ULL val)
{
    ULL ret = val ? numberOfElements : 1;
    for (ULL i = val + 2; i <= numberOfElements; i += 2)
    {
        ret += ret * ((long double) ((numberOfElements - i + 2) * (numberOfElements - i + 1)) / (i * (i - 1)));
    }
    return ret;
}

ULL fastSquare(ULL base, ULL power)
{
    if (power == 0)
    {
        return 1;
    }
    if (power % 2 == 0)
    {
        return fastSquare(base * base, power / 2);
    }
    return base * fastSquare(base * base, (power - 1) / 2);
}

ULL chooseOneOrMore()
{
    ULL ret = fastSquare(2, numberOfElements) - 1;
    return ret;
}