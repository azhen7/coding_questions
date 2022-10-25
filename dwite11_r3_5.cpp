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

        if ((c >= 'a' && c <= 'j') || (c >= 'A' && c <= 'J'))
            result += tolower(c);
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
            while (!st.empty() && prec(s[i]) <= prec(st.top()) )
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

bool processOr(char c1, char c2)
{
    if(toupper(c1) == c2 || tolower(c1) == c2)
        return true;
    return false;    
}

bool evaluatePostfix(string exp)
{
    if(exp.size() <= 1)
        return false;

    stack<char> st;
    vector<bool> interResult;
    
    for (size_t i = 0; i < exp.length(); i++) 
    {
        char c = exp[i];
    
        if ((c >= 'a' && c <= 'j'))
        {
            if(i == exp.length()-1)
            {
                interResult.push_back(false);
            }
            else
            {
                st.push(c);
            }
        }
        else
        {
           
            if(c == '~')
            {
                if(st.empty())
                {
                    if(interResult.size()  >= 1)
                    {
                        bool cal = !interResult.back();
                        interResult.erase(interResult.end() - 1);
                        interResult.push_back(cal);
                    }
                    else{
                        interResult.push_back(false);
                    }
                }
                else
                {
                    if(i == exp.length()-1)
                    {
                        interResult.push_back(false);
                    }
                    else
                    {
                        char temp = toupper(st.top());
                        st.pop();
                        st.push(temp);
                    }
                }
            }

            if(c == '^')
            {
                if(st.empty())
                {   
                    if(interResult.size()  >= 2)
                    {
                        bool cal = interResult[interResult.size() - 1] && interResult[interResult.size() - 2];
                        interResult.erase(interResult.end() - 1);
                        interResult.erase(interResult.end() - 1);
                        interResult.push_back(cal);
                    }
                }
                else
                {
                    if(st.size() >= 2)
                    {
                        st.pop();
                        st.pop();
                    }
                    else
                    {
                        st.pop();
                        if(interResult.size()  >= 1)
                        {
                            interResult.erase(interResult.end() - 1);
                        }
                    }
                                     
                    interResult.push_back(false);
                }
            }             
            if(c == 'v')
            {
                if(st.empty())
                {
                    if(interResult.size()  >= 2)
                    {
                        bool cal = interResult[interResult.size() - 1] || interResult[interResult.size() - 2];
                        interResult.erase(interResult.end() - 1);
                        interResult.erase(interResult.end() - 1);
                        interResult.push_back(cal);
                    }
                }
                else
                {
                    if(st.size() >= 2)
                    {
                        char temp1 = st.top();
                        st.pop();
                        char temp2 = st.top();
                        st.pop();
                        bool ret = processOr(temp1, temp2);
                        interResult.push_back(ret);
                    }
                    else
                    {
                        st.pop();
                    }
                }
            }        
        }
    }
    if(interResult.size() > 0)
        return interResult[0];
    else
        return false;
}


int main()
{
    std::cin.sync_with_stdio();
    std::cin.tie(0);

    string line;

    std::cin.sync_with_stdio();
    std::cin.tie(0);

    for(int i = 0; i < 15; i++)
    {
        std::getline(std::cin, line);

        string convLine = infixToPostfix(line);
        bool ret = evaluatePostfix(convLine);
        if ( ret == true)
            std::cout << 'Y';
        else
            std::cout << 'N';

        if ( (i+1) %3 == 0 )
            std::cout << std::endl;
    }        

}

