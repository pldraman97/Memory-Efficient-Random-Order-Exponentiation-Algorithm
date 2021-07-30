#include <bits/stdc++.h>
using namespace std;
//returns index of first existence of ni in array D else return long long_MIN
long long lookup(long long ni, long long D[])
{
    if (D[0] == ni)
        return 0;
    if (D[1] == ni)
        return 1;
    return INT_MIN;
}

//This is the proposed algorithm to increase the memory efficiency of Tunsell's Algorithm
//It requires 5 registers instead of m + r
//Right to Left binary Exponentiation
//Returns x^n where n is treated as binary
long long RandomOrderSlidingWindowExponentiationBinary(long long x, long long n)
{
    srand(time(NULL));
    long long R[2], A[2], D[2];     //D[j] stores if there is any delay opeartion associated with register A[j] with previous valoue of i
                                    //otherwise it stores long long_MIN
    long long j;
    //Initialization
    for (long long i = 0; i <= 1; i++)
    {
        R[i] = 1;
        A[i] = 1;
        D[i] = INT_MIN;
    }
    long long M = x;                
    long long k = log2(n) + 1;            //binary length of n
    //Main Loop
    for (long long i = 0; i < k; i++)
    {
        long long b = rand() % 2;         //b is randomly chosen from 0 or 1
        long long ni = (n >> i) & 1;      //ni stores ith bit of n
        //if b is 1 then simply multiply M to the corresponding R
        if (b)
            R[ni] *= M;
        //otherwise we check if there is delayed multiplication associated with complement of ni, if found so 
        //We perform the delayed multiplication for ni complement and store current bit for delayed multiplication

        //Else We look for an available register to delay this operation
        //If there is such register we store current bit for delayed multiplication
        //Else we perform the multiplication for ni and 
        else
        {
            j = lookup(1 - ni, D);
            if (j != INT_MIN)
            {
                R[1 - ni] *= A[j];
                A[j] = M;
                D[j] = ni;
            }
            else
            {
                j = lookup(INT_MIN, D);
                if (j != INT_MIN)
                {
                    A[j] = M;
                    D[j] = ni;
                }
                else
                {
                    R[ni] *= A[ni];
                    A[ni] = M;
                }
            }
        }
        M *= M;
    }
    //we do the left out computation and result is in R[1]
    for (long long i = 0; i <= 1; i++)
    {
        if(D[i] != INT_MIN)
            R[D[i]] *= A[i];
    }
    return R[1];
}
