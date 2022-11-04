#include <iostream>
#include <set>

int main()
{
    std::multiset<int> nums;
    
    int N;
    int X;
    std::cin >> N;
    std::cin >> X;
    
    for (int i = 0; i < N; i++)
    {
        int a;
        std::cin >> a;
        nums.insert(a);
    }

    int num1, num2;
    bool has_set = false;
    
    for (int i = 0; i < N; i++)
    {
        num1 = *nums.begin();
        auto test = nums.lower_bound(X - *nums.begin());

        if (test == nums.end() || *test > X - *nums.begin())
        {
            nums.erase(nums.begin());
            continue;
        }

        num2 = *test;
        has_set = true;
        break;
    }

    if (has_set)
    {
        std::cout << num1 << ' ' << num2 << '\n';
    }
    else
    {
        std::cout << "No pair of elements adds up to " << X << '\n';
    }
}