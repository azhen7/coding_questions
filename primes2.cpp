#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

#define debug           primes.assign(R - L + 1, 0);
#define efficient       primes.reserve(R - L + 1);

typedef unsigned int UI;

UI L, R;

// __int64 power(int a, int n, int mod)
// {
//  __int64 power=a,result=1;

//  while(n)
//  {
//   if(n&1) 
//    result=(result*power)%mod;
//   power=(power*power)%mod;
//   n>>=1;
//  }
//  return result;
// }

// bool witness(int a, int n)
// {
//  int t,u,i;
//  __int64 prev,curr;

//  u=n/2;
//  t=1;
//  while(!(u&1))
//  {
//   u/=2;
//   ++t;
//  }

//  prev=power(a,u,n);
//  for(i=1;i<=t;++i)
//  {
//   curr=(prev*prev)%n;
//   if((curr==1)&&(prev!=1)&&(prev!=n-1)) 
//    return true;
//   prev=curr;
//  }
//  if(curr!=1) 
//   return true;
//  return false;
// }

// inline bool isPrime( int number )
// {
//  if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
//   return (false);

//  if(number<1373653)
//  {
//   for( int k = 1; 36*k*k-12*k < number;++k)
//   if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
//    return (false);

//   return true;
//  }

//  if(number < 9080191)
//  {
//   if(witness(31,number)) return false;
//   if(witness(73,number)) return false;
//   return true;
//  }


//  if(witness(2,number)) return false;
//  if(witness(7,number)) return false;
//  if(witness(61,number)) return false;
//  return true;

//  /*WARNING: Algorithm deterministic only for numbers < 4,759,123,141 (unsigned int's max is 4294967296)
//    if n < 1,373,653, it is enough to test a = 2 and 3.
//    if n < 9,080,191, it is enough to test a = 31 and 73.
//    if n < 4,759,123,141, it is enough to test a = 2, 7, and 61.
//    if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11.
//    if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13.
//    if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.*/
// }

bool isPrime(UI n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n == 2 || n == 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (UI i = 5; i < std::sqrt(n); i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

std::vector<UI> primes;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> L >> R;

    debug

    std::iota(primes.begin(), primes.end(), L);

    auto it = std::remove_if(primes.begin(), primes.end(), [=](UI a)
    {
        return ((a % 2 == 0 || a % 3 == 0) && (a != 2 && a != 3)) || (a == 1);
    });
    primes.erase(it, primes.end());

    for (UI i = 5; i <= std::sqrt(R); i += 6)
    {
        if (isPrime(i))
        {
            auto it = std::remove_if(primes.begin(), primes.end(), [=](UI a)
            {
                return a % i == 0 && a != i;
            });
            primes.erase(it, primes.end());
        }
        if (isPrime(i + 2))
        {
            auto it = std::remove_if(primes.begin(), primes.end(), [=](UI a)
            {
                return a % (i + 2) == 0 && a != (i + 2);
            });
            primes.erase(it, primes.end());
        }
    }

    for (const UI& a : primes)
    {
        std::cout << a << '\n';
    }
}

