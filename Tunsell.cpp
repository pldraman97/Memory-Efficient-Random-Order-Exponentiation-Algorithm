#include <bits/stdc++.h>
using namespace std;

//for finding a^b
long long pow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
// Random Order Right to Left m-ary Exponentiation Function requiring m + r registers 
// It returns x^n using m as radix base of exponent n 
long Tunsell(long long x, long long n, long long m)
{	
	
	srand(time(0));				
	long long r = m + 5;				//r must be greater than m (not necessarily m + 5) and atmost l,length of exponent in radix m is required
	
	long long R[m];
	long long S[r], D[r];				//R is set of registers available
								//S is array to store the precomputed x^(m^i) where i belongs to (0, ... r-1)
								//D is the list which contains the first r digits of exponent n
	
	//Initialization
	for (long long i = 1; i < m; i++)
		R[i] = 1;
	S[0] = x;
	for (long long i = 1; i < r; i++)
	{
		S[i] = pow(S[i - 1], m);	//S = {x, x^m, x^(m^2) ... x^(m^(r-1))}
	}
	for (long long i = 0; i < r; i++)
	{
		D[i] = n % m;				//D = {d0, d1, d2, ... dr-1}
		n = n / m;
	}
	long long Y = r - 1;					//Stores index of largest power of x present in S

	//Main Loop
	//The values of S and D can be treated in any arbitrary order because for each j, we find R[D[j]] *= S[j] and multiplication is 
	//associative

	//Store a random value from {0 ... r-1} in tou and compute the register corresponding to it (R[D[tou]] *= S[tou])
	//after which D[tou] and S[tou] are no longer needed and are overwritten for next powers -> x^(m^(r)), x^(m^(r + 1)) ...

	//This is done for all digits of n in radix base m
	while (n > 0)
	{
		long long tou = rand() % r;
		if (D[tou])				
		{
			R[D[tou]] *= S[tou];
		}
		S[tou] = pow(S[Y], m);
		D[tou] = n % m;
		n = n / m;
		Y = tou;
	}
	//Computation for last r digits in S and D
	for (long long i = r - 1; i >= 0; i--)
	{
		R[D[i]] *= S[i];
	}

	//Each R[i] contains product of all those S[j]s where D[j] is i 
	//Storing R[i] * R[i + 1] ... * R[m - 1] in R[i]
	//Finding the product of (R[1]^1) * (R[2]^2) ... (R[m - 1]^ (m - 1)) and storing in A which is x^n
	long long A = R[m - 1];
	for (long long i = m - 2; i > 0; i--)
	{
		R[i] *= R[i + 1];
		A = A * R[i];
	}
	return A;
}
