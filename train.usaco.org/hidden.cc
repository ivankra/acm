/*
ID: infnty1
TASK: hidden
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int p[310000], N;
char S[310000];

int main() {
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);

	scanf(" %*d");
	for (N = 0; scanf(" %s", S+N) == 1; N += strlen(S+N));
	for (int i = 0; i < N; i++) S[i+N] = S[i+N+N] = S[i];
	S[N+N+N] = 0;

	int best = 0, m = 1;
	p[0] = p[1] = 0;

	for (int pos = 1; pos <= 2*N; pos++) {
		//printf("pos=%-3d m=%d best=%s\n", pos, m, S+best);

		while (m > 0 && S[best+p[m]] > S[pos])
			m = p[m];
		best = pos - m;
		m++;

		if (m > 1) {
			int t = p[m-1];
			while (t > 0 && S[best+t] != S[pos])
				t = p[t];
			p[m] = (S[best+t] == S[pos] ? t+1 : 0);
		}
	}

	printf("%d\n", best%N);
}
