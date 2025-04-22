/*
You are given two integers n and maxValue, which are used to describe an ideal array.

A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:

Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: n = 2, maxValue = 5
Output: 10
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
- Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
- Arrays starting with the value 3 (1 array): [3,3]
- Arrays starting with the value 4 (1 array): [4,4]
- Arrays starting with the value 5 (1 array): [5,5]
There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
Example 2:

Input: n = 5, maxValue = 3
Output: 11
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (9 arrays): 
   - With no other distinct values (1 array): [1,1,1,1,1] 
   - With 2nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
   - With 2nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
- Arrays starting with the value 2 (1 array): [2,2,2,2,2]
- Arrays starting with the value 3 (1 array): [3,3,3,3,3]
There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.
 

Constraints:

2 <= n <= 10^4
1 <= maxValue <= 10^4


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 10010
#define MAXV 10010
#define MAXK 20

int comb[MAXN][MAXK];

// Precompute binomial coefficients C(n, k) % MOD
void precompute_combinations(int n) {
    for (int i = 0; i <= n; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j < MAXK && j <= i; ++j) {
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
        }
    }
}

int idealArrays(int n, int maxValue) {
    precompute_combinations(n);

    int dp[MAXV][MAXK];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= maxValue; ++i) {
        dp[i][1] = 1;  // Each number is a sequence of length 1
    }

    int maxLen = 1;

    // dp[x][k] = number of chains ending in x of length k
    for (int k = 2; k < MAXK; ++k) {
        for (int i = 1; i <= maxValue; ++i) {
            for (int j = 2*i; j <= maxValue; j += i) {
                dp[j][k] = (dp[j][k] + dp[i][k-1]) % MOD;
            }
        }
        maxLen = k;
    }

    long long result = 0;
    for (int i = 1; i <= maxValue; ++i) {
        for (int k = 1; k < MAXK; ++k) {
            result = (result + (long long)dp[i][k] * comb[n-1][k-1]) % MOD;
        }
    }

    return (int)result;
}
