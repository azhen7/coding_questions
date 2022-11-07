#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <cctype>
#include <map>
#include <stack>


int countEvenSum(int arr[], int n)
{
    // A temporary array of size 2. temp[0] is
    // going to store count of even subarrays
    // and temp[1] count of odd.
    // temp[0] is initialized as 1 because there
    // a single even element is also counted as
    // a subarray
    int temp[2] = {1, 0};
 
    // Initialize count.  sum is sum of elements
    // under modulo 2 and ending with arr[i].
    int result = 0, sum = 0;
 
    // i'th iteration computes sum of arr[0..i]
    // under modulo 2 and increments even/odd count
    // according to sum's value
    for (int i=0; i<=n-1; i++)
    {
        // 2 is added to handle negative numbers
        sum = ( (sum + arr[i]) % 2 + 2) % 2;
 
        // Increment even/odd count
        temp[sum]++;
    }
 
    // Use handshake lemma to count even subarrays
    // (Note that an even can be formed by two even
    // or two odd)
    result = result + (temp[0]*(temp[0]-1)/2);
    result = result + (temp[1]*(temp[1]-1)/2);
 
    return (result);
}
 

int main()
{
    //int arr[] = {1, 2, 2, 3, 4, 1};
    //int n = sizeof (arr) / sizeof (arr[0]);
    //int ret = countEvenSum (arr, n);

    unsigned long long K;
    std::cin >> K;
    std::cin.ignore();
    //K = 1000001ULL*1000000ULL/2;
    //K= 8;
    unsigned long long A = ((-1+sqrt(1+8*K))/2 < 1000000)?(-1+sqrt(1+8*K))/2:1000000;
    unsigned long long delta = K - A*(A+1)/2;
 
    unsigned long long B = ((1+sqrt(1+8*delta))/2 < 1000000)?(1+sqrt(1+8*delta))/2:1000000;
   
    bool found  = false;

    while (A+B <= 1000000)
    {
        if( B*(B-1)/2 == delta)
        {
            found  = true;
            break;
        }
        B++;
        if( A*(A+1)/2 + B*(B-1)/2 > K)
            break;
    }
    
    int N = A + B; 
    if( found == false )
        std::cout << "-1" << std::endl;
    else
    {
        std::vector<int> ret;
        
        std::cout << N << std::endl;

        int start = 1;
        int index = 1;

        while( A >= 1 && B >= 1)
        {
            if(start%2 == 0)
            {
                ret.push_back(start);
                A--;
            }
            else
            {
                ret.push_back(start);
                B--;
            }
            start += ++index;
                
        }

        while( A >= 1)
        {
            if(start%2 == 0)
            {
                ret.push_back(start);
                A--;
            }
            start += ++index;
        }

        while( B >= 1)
        {
            if(start%2 != 0)
            {
                ret.push_back(start);
                B--;
            }
            start += ++index;
        }

        std::vector<int> final;
        final.push_back(ret[0]);
        for(size_t i = 1; i < ret.size(); i++)
            final.push_back(ret[i] - ret[i-1]);

        for(auto item:final)
            std::cout << item << " ";

    }




}