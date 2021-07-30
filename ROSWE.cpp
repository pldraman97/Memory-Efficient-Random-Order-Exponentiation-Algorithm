#include <bits/stdc++.h>
using namespace std;
// returns i th bit of n
long long findBit(long long n, long long i)
{
    return ((n >> i) & 1);
}

//returns number 0f bit size w, n(i + w - 1)...n(i)
long long findNum(long long n, long long i, long long w)
{
    n = n >> i;
    long long k = (1 << w) - 1;
    return n & k;
}

//This is the proposed algorithm to increase the memory efficiency of Tunsell's Algorithm
//It requires m + 1 registers instead of m
//Right to Left m-ary Exponentiation
//Returns x^n where n is treated as radix base m
long long RandomOrderSlidingWindowExponentiation(long long x, long long m, long long n)
{
    srand(time(NULL));              //Seed for rand()
    long long w = log2(m);                //Size of our window

    unordered_map<long long, long long> R, S;   //stores in S[j] the value of A^i, where digit at ith position from right is j 
                                    //R acts as set of registers
    //Initialization corresponding to odd digits
    //Only odd digits are considered to further improve efficiency of sliding window by reducing m to m / 2
    for (long long i = 1; i <= m; i = i + 2)
    {
        R[i] = S[i] = 1;
    }
    long long i = 0, A = x;
    long long k = log2(n) + 1;        //binary length of n
    //Main Loop
    while (i < k)
    {   
        //If ith bit is 0, we perform squaring of A, and move to next bit 
        if (findBit(n, i) == 0)
        {
            A = A * A;
            i++;
        }
        //If ith bit is 1, we store random odd number less than m in e
        //We update R[e] and S[e]
        //We extract n(i + w - 1)...n(i) from n and store in d.
        //If the register S[d] is not available (i.e.,S[d] != 1), we reduce the size of the current window
        //to find another digit that has not yet been delayed
        //If d>0 then we update S[d] to current value of A and subtract d from n 
        else
        {
            long long e = 2 * (rand() % (m / 2)) + 1;
            R[e] *= S[e];
            S[e] = 1;
            long long d = findNum(n, i, w);
            while (S[d] != 1 && d > 0)
            {
                d = d << 1;
            }
            if (d > 0)
            {
                S[d] = A;
                n = n - ((1 << i) * d);
            }
        }
    }
    //Doing computation of left out digits
    for (long long j = 1; j <= m; j += 2)
    {
        R[j] = R[j] * S[j];
    }
   
	//Finding the product of (R[1]^1) * (R[3]^3) ... (R[m - 1]^ (m - 1)) and storing in A which is x^n
    A = 1;
    for (long long j = 1; j <= m; j += 2)
    {
        R[j] = pow(R[j], j);
        A *= R[j];
    }
    return A;
}
