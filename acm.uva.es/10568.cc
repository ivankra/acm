#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

unsigned long long choose[64][64];

unsigned long long Count(int N, int K)
{
	unsigned long long res = choose[N][N % K];
	N -= N % K;

	int m = N/K;
	for (int i = 0; i < m; i++) {
		res *= choose[N-1][K-1];
		N -= K;
	}
	return res;
}

int used[100], nused, N, K, G;
char out[1000], *outp;
string prev;
unsigned long long recCount;

void rec(int i, int group, int group_size, int flag)
{
	if (group == G) {
		assert(nused == N);
		recCount++;
		outp[-1] = outp[0] = 0;
		printf("%s\n", out+1);

		string s = string(out+1);
		if (recCount > 0)
			assert(prev < s);
		prev = s;

		return;
	}

	if (group_size == K) {
		*outp++ = ' ';
		rec(0, group+1, 0, flag);
		outp--;
		return;
	}

	if (flag == 0 && group_size == N%K) {
		*outp++ = ' ';
		rec(0, group+1, 0, 1);
		outp--;
	}

	if (flag == 1) {
		int cnt = 0;
		for (int j = i; j < N; j++)
			if (used[j] == 0) cnt++;
		if (cnt < K-group_size) return;
	}

	for (int j = i; j < N; j++) {
		if (used[j]) continue;

		*outp++ = 'A'+j;
		used[j] = 1;
		nused++;
		rec(j+1, group, group_size+1, flag);
		nused--;
		used[j] = 0;
		outp--;

		if (group_size == 0) break;
	}
}

int main()
{
	memset(choose, 0, sizeof(choose));
	for (int n = 0; n < 64; n++) {
		choose[n][0] = 1;
		for (int k = 1; k <= n; k++)
			choose[n][k] = choose[n-1][k-1] + choose[n-1][k];
	}

	char s[100];
	while (scanf(" %s %d %d", s, &N, &K) == 3) {
		s[0] = toupper(s[0]);
		if (s[0] == 'C') {
			printf("%llu\n", Count(N, K));
		} else if (s[0] == 'G') {
			unsigned long long c = Count(N, K);
			printf("%llu\n", c);
			memset(used, 0, sizeof(used));
			nused = 0;
			memset(out, 0, sizeof(out));
			outp = out+1;
			recCount = 0;
			G = (N+K-1)/K;
			prev = "";
			rec(0, 0, 0, N%K==0 ? 1 : 0);
			assert(recCount == c);
		} else {
			break;
		}
	}
}
