#include <iostream>
#include <malloc.h>
#include <math.h>
#include "numbers.dat"

using namespace std;

bool prime(int x)
{
    if(x == 2)
        return true;
    else if(x == 1 || !(x & 1))
        return false;
    int sq = sqrt(x) + 1;
    for(int i = 3; i <= sq; ++i)
    {
        if(!(x % i))
            return false;
    }
    return true;
}

int get_answ(int x, int y)
{
    int i = 0, count = 0;
    while(Data[i] < x)
        i++;
    if(Data[i] != x)
        return -1;
    while(i < Size && Data[i] <= y)
    {
        bool pr = prime(Data[i]);
        if(pr)
            count++;
        while(Data[i] == Data[i + 1])
        {
            i++;
            if(pr)
                count++;
        }
        i++;
    }
    if(Data[i - 1] != y)
        return -1;
    return count;
}

int main(int argc, char* argv[])
{
    if(argc % 2 == 0 || argc == 1)
        return -1;

    for (int i = 1; i < argc; i += 2)
    {
        int x = atoi(argv[i]);
        int y = atoi(argv[i + 1]);
        if(x > y)
        {
            cout << 0;
            return 0;
        }
        cout << get_answ(x, y) << endl;
    }
    return 0;
}
