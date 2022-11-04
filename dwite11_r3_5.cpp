#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int prec(char c)
{
    if (c == '~')
        return 3;
    else if (c == '^' || c == 'v')
        return 2;
    else
        return -1;
}


string infixToPostfix(string &s)
{
    stack<char> st; // For stack operations, we are using C++ built in stack
    string result;
 
    for (size_t i = 0; i < s.length(); i++) 
    {
        char c = s[i];
        
        if(c == ' ')
            continue;

        if (c >= 'a' && c <= 'j')
            result += c;
        else if (c == '(')
            st.push('(');
        else if (c == ')')
        {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && prec(c) <= prec(st.top()) )
            {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty()) 
    {
        result += st.top();
        st.pop();
    }

    return result;

}
bool evaluate(string &line, uint32_t values)
{
    bool stack[255];
	int stackSize = 0;

    for (size_t i = 0; i < line.length(); i++) 
    {
        char c = line[i];

        if (c >= 'a' && c <= 'j') 
        {
		    stack[stackSize] = ((values >> (c - 'a')) & 1UL) != 0UL;
			stackSize++;
		} else if (c == '~')
        {
			stack[stackSize - 1] = !stack[stackSize - 1];
        }
		else if (c == '^') {
			stack[stackSize - 2] = stack[stackSize - 2] && stack[stackSize - 1];
			stackSize--;
		} else if (c == 'v') {
			stack[stackSize - 2] = stack[stackSize - 2] || stack[stackSize - 1];
			stackSize--;
        }
    }
    if(stackSize >=1 )
        return stack[0];
    return false;
}

static uint32_t NUM_ATOMS = 'j' - 'a' + 1;

int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    string line;


    for(int i = 0; i < 15; i++)
    {
        std::getline(std::cin, line);
       
        string convLine = infixToPostfix(line);
        
        bool ret = true;
        for (uint32_t index = 0; index < (1UL << NUM_ATOMS); index++) 
        {
			if (!evaluate(convLine, index))
            {
				ret = false;
                break;
            }
		}
    
        if ( ret == true)
            std::cout << 'Y';
        else
            std::cout << 'N';

        if ( (i+1) %3 == 0 )
            std::cout << std::endl;
    }        

}

