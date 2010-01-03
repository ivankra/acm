/*
ID: infnty1
TASK: betsy
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int N;
long long memo[8][16384];

long long ways(int height, int cross) {
	long long &res = memo[height][cross];
	if (res != -1) return res;

	int c[8];
	for (int i = 0; i < N; i++) c[i] = (cross >> (2*i)) & 3;

//{printf("ways(h=%d, c=%d:", height,cross); for (int i = 0; i < N; i++) printf("%d", c[i]); printf(")\n");}

	if (height == 1) {
		if (cross == 0) return res = 0;

		int u[8];
		for (int i = 0; i < N; i++) u[i] = i;
		for (int i = 0, j; i < N; i = j+1) {
			if (c[i] == 0) return res = 0;
			for (j = i+1; j < N && c[j] == 0; j++);
			if (j >= N) return res = 0;

			int a = u[c[i]], b = u[c[j]];
			if (a != b) {
				for (int k = 0; k < 8; k++)
					if (u[k] == b) u[k] = a;
			}
		}

		for (int i = 0, a = -1; i < N; i++) {
			if (c[i] == 0) continue;
			if (a < 0) a = u[c[i]];
			if (u[c[i]] != a) return res = 0;
		}

		return res = 1;
	}

	res = 0;
	for (int m = 0; m < (1 << (N-1)); m++) {
		int u[8], outf[8], d[8], used[8];
		for (int i = 0; i < N; i++) { u[i] = i; outf[i] = 0; }

//printf("  [%d,%d]  case m=%d  (", height,cross,m);for (int i = 0; i < N; i++) printf("%d", (m>>i)&1); printf(")\n");

		for (int i = 0, j; i < N; i = j+1) {
			for (j = i; (m & (1 << j)) != 0; j++)
				if (c[j] != 0 && j != i) goto skip;
//printf("    %d-%d  c's=%d-%d\n", i,j,c[i],c[j]);
			if (c[i] == 0 && i == j) goto skip;

			if (c[i] == 0 || c[j] == 0 || i == j) {
				outf[c[i]] = outf[c[j]] = 1;
			} else if (c[i] != 0 && c[j] != 0) {
				if (c[i] == c[j]) goto skip;
				if (u[c[i]] == u[c[j]]) goto skip;

				for (int k = 0, t = u[c[j]]; k < N; k++)
					if (u[k] == t) u[k] = u[c[i]];
			}
		}

		for (int i = 0; i < N; i++) d[i] = used[i] = 0;
		for (int i = 0; i < N; i++)
			if (c[i] != 0 && outf[c[i]]) used[u[c[i]]] = 1;

		for (int i = 0, j; i < N; i = j+1) {
			for (j = i; (m & (1 << j)) != 0; j++)
				if (c[j] != 0 && j != i) goto skip;

//printf("    %d-%d  u[c]'s=%d-%d\n", i,j,u[c[i]],u[c[j]]);

			int m;
			if (c[i] == 0 && c[j] == 0) {
				for (m = 1; used[m]; m++);
				used[m] = 1;
			} else {
				m = (c[i] == 0) ? u[c[j]] : u[c[i]];
			}

			if (c[i] == 0) d[i] = m;
			if (c[j] == 0) d[j] = m;

			if (i == j) d[i] = m;
		}

//{printf("    d=");for (int i = 0; i < N; i++) printf("%d", d[i]); printf("\n");}
		{
			int t = 0;
			for (int i = 0; i < N; i++) {
				assert(d[i] < 4);
				t |= d[i] << (2*i);
			}
			res += ways(height-1, t);
		}
skip:;
	}
//printf("  [%d,%d]  returns %d\n",height,cross,(int)res);

	return res;
}

int main()
{
	freopen("betsy.in", "r", stdin);
	freopen("betsy.out", "w", stdout);

	while (scanf("%d", &N) == 1) {
		if (N == 1) {
			printf("1\n");
		} else {
			int cross = 0;
			for (int i = 0; i < N; i++)
				cross = (cross << 2) + (i==0 || i==N-1 ? 1 : 0);

			memset(memo, 0xff, sizeof(memo));
			printf("%lld\n", ways(N, cross));
		}
	}
}
