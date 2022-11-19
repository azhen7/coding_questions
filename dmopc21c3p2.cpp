#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <cctype>
#include <map>
#include <stack>
#include <iostream>


int main()
{
    unsigned long long K;
    std::cin >> K;
    std::cin.ignore();
    if(K == 0)
    {
        std::cout << 1 << std::endl << 1 << std::endl;
        return 0;
    }

    unsigned long long A = ((-1+sqrt(1+8*K))/2 < 1000000)?(-1+sqrt(1+8*K))/2:1000000;
    unsigned long long B = 0;
    unsigned long long t;
    
    bool found  = false;

    while (A+B <= 1000000)
    {
        t = (B*B-B + A*A+A)/2;
        if(t > K)
            A--;
        else if (t< K)
            B++;
        else
        {
            found = true;
            break;
        }
    }

    int N = A + B; 
    if( found == false )
        std::cout << "-1" << std::endl;
    else
    {
        std::vector<int> ret;
        
        std::cout << N << std::endl;

        int prefix = 0;
        bool printed = false;
        if(B>0)
        {
            std::cout << 1;
            B--;
            prefix++;
            printed = true;
        }
        while(B>0)
        {
           
            prefix++;
            if(prefix&1)
            {
                std::cout <<" 1";
                B--;
            }
            else
            {
                std::cout <<" 0";
                A--;
            }
        }
        if( A > 0)
        {
            if(printed)
                std::cout << " 0";
            else
                std::cout << "0";
            A--;
        }
        while(A>0)
        {
            std::cout << " 0";
            A--;
        }
        std::cout << std::endl;
    }
}