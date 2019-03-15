#include <iostream>
#include <stdio.h>
#include <chrono>
#include <malloc.h>
#include <math.h>
#include "numbers.dat"

using namespace std;

int prime(int x)
{
    int sq = sqrt(x);
    for(int i = 2; i <= sq; ++i)
    {
        if(x % i == 0)
            return 0;
    }
    return 1;
}

void fill_Sieve(int* sieve)
{
    sieve[0] = 0;
    sieve[1] = 1;
    int max = Data[Size - 1];
    int j = 0;//ind for Data array
    for(int i = 1; i < max; ++i)
    {
        while((i + 1) > Data[j])
            j++;
        if(Data[j] > (i + 1))
            sieve[i] = -1;
        else
        {
            sieve[i] = prime(i + 1);
            j++;
            if (sieve[i])
            {
                while (Data[j] == (i + 1))
                {
                    j++; sieve[i]++;
                }
            }
        }
    }
    return;
}

int get_answ(int x, int y, int*& sieve)
{
    if(sieve[x - 1] == -1 || sieve[y - 1] == -1)
        return 0;
    int count = 0;
    for(int i = x - 1; i < y; ++i)
    {
        if(sieve[i] != -1)
            count += sieve[i];
    }
    return count;
}

int main(int argc, char* argv[])
{
    if(argc % 2 == 0 || argc == 1)
        return -1;

    int *sieve = new int[Size]{0};
    fill_Sieve(sieve);

    for (int i = 1; i < argc; i += 2)
    {
        int x = atoi(argv[i]);
        int y = atoi(argv[i + 1]);
        if(x > y)
        {
            cout << 0;
            return 0;
        }
        cout << get_answ(x, y, sieve) << endl;
    }

    delete []sieve;
    return 0;
}
