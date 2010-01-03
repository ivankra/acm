#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

char S[1000];
int N;

bool okay(char a, char b, char c) {
	return (a=='R') + (b=='R') + (c=='R') <= 1;
}

long long memo[128][128];

long long f(int s, int t) {
	if (t-s == -1) return 1;
	assert(s <= t);

	if ((t-s+1)%3 != 0) return 0;

	long long &res = memo[s][t];
	if (res != -1) return res;

	res = 0;
	for (int a = s, b = s+1; b <= t; b++) {
		for (int c = b+1; c <= t; c++) {
			if (!okay(S[a], S[b], S[c])) continue;
			res += f(a+1, b-1) * f(b+1, c-1) * f(c+1, t);
		}
	}
	
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %d %s", &N, S);
		for (int i = 0; i < N; i++) S[i+N] = S[i+N+N] = S[i];

		long long ways = 0;
		memset(memo, 0xff, sizeof(memo));
		for (int a = 0, b = 1; b < N; b++) {
			for (int c = b+1; c < N; c++) {
				if (!okay(S[a], S[b], S[c])) continue;
				ways += f(a+1, b-1) * f(b+1, c-1) * f(c+1, N+a-1);
			}
		}
		printf("Case %d: %lld\n", cs, ways);
	}
}
