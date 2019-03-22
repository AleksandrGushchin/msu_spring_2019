#include <stdio.h>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Calculator
{
    string expression;

public:
    int  result;
    int  cur_ind;
    Calculator(const string &input)
        :result(0),
         cur_ind(0)
    {
        expression = normalize(input);
        sum_and_sub();
    }

private:
    int get_num()
    {
        if(!isdigit(expression[cur_ind])){
            throw invalid_argument("error");
            return 0;
        }
        string n;
        while(isdigit(expression[cur_ind]))
            n += expression[cur_ind++];
        return atoi(n.c_str());
    }

    void sum_and_sub()
    {
        int len = expression.length();
        int arg1 = mult();
        while(cur_ind < len)
        {
            char op = expression[cur_ind++];
            int arg2 = mult();
            if(op == '+')
                arg1 += arg2;
            else
                arg1 -= arg2;
        }
        result = arg1;
    }

    int mult()
    {
        bool minus = false;
        while(expression[cur_ind] == '-')
        {
            minus = !minus; cur_ind++;
        }
        int arg1 = get_num(), len = expression.length();
        if(minus)
            arg1 *= -1;
        while(cur_ind < len && expression[cur_ind] != '-' && expression[cur_ind] != '+')
        {
            char op = expression[cur_ind++];
            int arg2 = get_num();
            switch (op) {
            case '*':
                arg1 *= arg2;
                break;
            case '/':
                if(arg2 == 0)
                    throw invalid_argument("error");
                arg1 /= arg2;
                break;
            default:
                throw invalid_argument("error");
                break;
            }
        }
        return arg1;
    }

    string normalize(const string &input)
    {
        string edit;
        int len = input.length();
        for (int i = 0; i < len; i++)
        {
            char cur = input[i];
            if(cur >= '*' && cur <= '9')
                edit += cur;
            else if (cur != ' ')
            {
                throw invalid_argument("error");
                return "";
            }
        }
        return edit;
    }
};

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "error";
        return 1;
    }
    const string s = string(argv[1]);

    try
    {
        Calculator a(s);
        cout << a.result;
    }
    catch (invalid_argument&)
    {
        cout << "error";
        return 1;
    }

    return 0;
}
