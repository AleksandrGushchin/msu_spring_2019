#include <thread>
#include <iostream>
#include <atomic>

using namespace std;

atomic<int> count;
const int MAX_NUM = 500000;

void threadFunction1()
{
    while (count <= MAX_NUM)
    {
        if (count & 1)
        {
            cout << "pong" << endl;
            count++;
        }
        this_thread::yield();
    }
    return;
}

void threadFunction2()
{
    while (count <= MAX_NUM)
    {
        if (!(count & 1))
        {
            cout << "ping" << endl;
            count++;
        }
        this_thread::yield();
    }
    return;
}

int main()
{
    count = 0;
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();
    return 0;
}
