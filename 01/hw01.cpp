#include <iostream>
#include <malloc.h>
#include <math.h>
#include "numbers.dat"

using namespace std;

void fill_Sieve(int* sieve)
{
    sieve[0] = 1;
    int sq = sqrt(Size);
    for(int i = 2; i < sq; ++i)
    {
        if(!sieve[i - 1])
        {
            int i1 = 2 * i - 1;
            while(i1 < Size)
            {
                sieve[i1] = 1;//0 = prime
                i1 += i;      //1 = not prime
            }
        }
    }
    return;
}

int get_answ(int x, int y, int*& sieve)
{
    int left = 0, right = Size, count = 0, med;
    while(Data[left] < x)
    {
        med = (left + right) / 2;
        if(Data[med] <= x)
            left = med;
        else
            right = med;
    }
    while(Data[left] >= x)
        left--;
    left++;
    if(Data[left] != x)
        return 0;

    while(Data[left] <= y)
    {
        if(!sieve[Data[left] - 1])
            count++;
        left++;
    }
    if(Data[left - 1] != y)
        return 0;
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
