#include <cstdio>
#include <cstring>

#define MAXN 40

int N;
unsigned ans[MAXN+1][8], memo[MAXN+1][MAXN+1][MAXN+1][MAXN+1], next[MAXN+1][MAXN+1][MAXN+1][MAXN+1];

int main()
{
	memset(ans, 0, sizeof(ans));
	ans[0][0] = ans[1][1] = 1;

	memset(memo, 0, sizeof(memo));
	memset(next, 0, sizeof(next));
	memo[1][1][1][1] = 1;

	for (N = 1; N < MAXN;) {
		for (int a5 = N; a5 >= 1; a5--)
		for (int a4 = a5==N?N:a5-1; a4 >= 1; a4--)
		for (int a3 = a4==N?N:a4-1; a3 >= 1; a3--)
		for (int a2 = a3==N?N:a3-1; a2 >= 1; a2--) {
			unsigned x = memo[a2][a3][a4][a5];
			int pos = a5;
#define add(R) {unsigned &r=R; r+=x; while (r>=1000000000U) r-=1000000000U;}
			while (pos > a4) add(next[a2][a3][a4][pos--])
			while (pos > a3) add(next[a2][a3][pos--][a5+1])
			while (pos > a2) add(next[a2][pos--][a4+1][a5+1])
			while (pos > 0) add(next[pos--][a3+1][a4+1][a5+1])
			add(next[a2+1][a3+1][a4+1][a5+1])
		}

		N++;

		for (int a5 = N; a5 >= 1; a5--)
		for (int a4 = a5==N?N:a5-1; a4 >= 1; a4--)
		for (int a3 = a4==N?N:a4-1; a3 >= 1; a3--)
		for (int a2 = a3==N?N:a3-1; a2 >= 1; a2--) {
			unsigned x = next[a2][a3][a4][a5];
			memo[a2][a3][a4][a5] = x;
			next[a2][a3][a4][a5] = 0;
			if (a2 == N) add(ans[N][1])
			else if (a3 == N) add(ans[N][2])
			else if (a4 == N) add(ans[N][3])
			else if (a5 == N) add(ans[N][4])
			else add(ans[N][5])
		}
	}

	int q, qn, qd;
	for (scanf("%d", &q); q-- > 0 && scanf("%d %d", &qn, &qd) == 2;)
		printf("%u\n", ans[qn][qd]);
}


/*

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// larger MAXN require 64-bit integers, bignums or cRT.
#define MAXN 12

int N, ans[MAXN+1][8];	// ans[N][D] = computed answer for test case N, D.

// For a fixed N, memo[a2][a3][a4][a5] = how many permutations of {1,...,N}
// are there, such that the length of longest increasing subsequence is at
// most 5, and the least index at which an increasing subsequence of size i
// ends is a_i ("doesn't exist" is indicated by a_i=N).
int memo[MAXN+1][MAXN+1][MAXN+1][MAXN+1];
int next[MAXN+1][MAXN+1][MAXN+1][MAXN+1];

int main()
{
	printf("mem: ~%d bytes\n", sizeof(memo)+sizeof(next));

	memset(ans, 0, sizeof(ans));
	ans[0][0] = ans[1][1] = 1;
	memset(memo, 0, sizeof(memo));
	memo[1][1][1][1] = 1;

	for (N = 1; N < MAXN;) {
		// Invariant: `memo' is correct for the current value of N.

		memset(next, 0, sizeof(next));

		for (int a2 = 1; a2 <= N; a2++)
		for (int a3 = (a2+1)<?N; a3 <= N; a3++)
		for (int a4 = (a3+1)<?N; a4 <= N; a4++)
		for (int a5 = (a4+1)<?N; a5 <= N; a5++) {
			int x = memo[a2][a3][a4][a5];

			// Each permutation of {1, ..., N+1} is formed by inserting
			// the value N+1 at some position of some permutation of {1, ..., N}.
			for (int pos = 0; pos <= N; pos++) {
				// will insert N+1 before position `pos'

				if (pos == 0)
					next[a2+1][a3+1][a4+1][a5+1] += x;
				else if (pos <= a2)
					next[pos][a3+1][a4+1][a5+1] += x;
				else if (pos <= a3)
					next[a2][pos][a4+1][a5+1] += x;
				else if (pos <= a4)
					next[a2][a3][pos][a5+1] += x;
				else if (pos <= a5)
					next[a2][a3][a4][pos] += x;
			}
		}

		N++;

		for (int a2 = 1; a2 <= N; a2++)
		for (int a3 = (a2+1)<?N; a3 <= N; a3++)
		for (int a4 = (a3+1)<?N; a4 <= N; a4++)
		for (int a5 = (a4+1)<?N; a5 <= N; a5++) {
			int x = next[a2][a3][a4][a5];
			if (a2 == N) ans[N][1] += x;
			else if (a3 == N) ans[N][2] += x;
			else if (a4 == N) ans[N][3] += x;
			else if (a5 == N) ans[N][4] += x;
			else ans[N][5] += x;
		}

		memcpy(memo, next, sizeof(next));
	}

	for (int n = 1; n <= MAXN; n++) {
		for (int d = 1; d <= n && d <= 5; d++)
			printf(d==1?"%d":" %d", ans[n][d]);
		printf("\n");
	}
}
*/
