#include <bits/stdc++.h>
#include "ROSWE.cpp"
#include "ROSWEB.cpp"
#include "Tunsell.cpp"
using namespace std;

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main()
{
    int error = 0;
    for (int i = 2; i < 101; i++)
    {
        for (int j = 1;; j++)
        {
            long long x = binpow(i,j);
            if(x > INT_MAX)
                break;
            long long y = RandomOrderSlidingWindowExponentiationBinary(i, j);
            if(y != x)
                cout << x << " " << y << "\n", error++;
        }
    }
    if(!error)
        cout << "No Error Found in ROSWEB\n";
    error = 0;
    for (int i = 2; i < 101; i++)
    {
        for (int j = 1;; j++)
        {
            long long x = binpow(i,j);
            if(x > INT_MAX)
                break;
            for (int k = 2; k < 17; k++)
            {
                long long y = RandomOrderSlidingWindowExponentiation(i, k, j);
                if(x != y)
                     cout << x << " " << y << "\n", error++;
            }
            
        }
    }
    if(!error)
        cout << "No Error Found in ROSWE\n";
    error = 0;
    for (int i = 2; i < 101; i++)
    {
        for (int j = 1;; j++)
        {
            long long x = binpow(i,j);
            if(x > INT_MAX)
                break;
            for (int k = 2; k < 17; k++)
            {
                long long y = Tunsell(i, j, k);
                if(x != y)
                     cout << x << " " << y << "\n", error++;
            }
            
        }
    }
    if(!error)
        cout << "No Error Found in Tunsell\n";
}
