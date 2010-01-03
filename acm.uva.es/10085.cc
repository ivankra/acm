#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#define STATES 362880

struct State {
	int a[9];
};

int encode(const State &S) {
	static int pos[9], b[9];
	int r=0;
	for (int i = 0; i < 9; i++) pos[b[i] = i] = i;
	for (int i = 0, m = 1; i < 9; m *= 9 - i++) {
		r += (pos[S.a[i]] - i) * m;
		int p = pos[S.a[i]];
		pos[b[p] = b[i]] = p;
	}
	return r;
}

void decode(State &S, int e) {
	for (int i = 0; i < 9; i++) S.a[i] = i;
	for (int i = 0; i < 9; e /= 9 - i++) swap(S.a[i], S.a[i+e%(9-i)]);
}

int seen[STATES], seen_id, Q[STATES], prev[STATES], prev_c[STATES];

void solve(State S) {
	int qh = 0, qt = 1;
	seen_id++;
	Q[0] = encode(S);
	seen[Q[0]] = seen_id;
	prev[Q[0]] = -1;
	for (; qh < qt; qh++) {
		decode(S, Q[qh]);

		int u, r, c;
		for (u = 0; u < 8 && S.a[u] != 0; u++);
		r = u / 3;
		c = u % 3;

#define CHK(v, C) { \
	swap(S.a[u], S.a[v]); int e = encode(S); \
	if (seen[e] != seen_id) { \
		prev[e] = Q[qh]; prev_c[e] = C; \
		seen[Q[qt++] = e] = seen_id; \
	} \
	swap(S.a[u], S.a[v]); \
}
		if (r > 0) CHK(u-3, 'U')
		if (r < 2) CHK(u+3, 'D')
		if (c > 0) CHK(u-1, 'L')
		if (c < 2) CHK(u+1, 'R')
#undef CHK
	}

	int e = Q[qt-1];
	decode(S, Q[qt-1]);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			printf(j+1 < 3 ? "%d " : "%d\n", S.a[i*3+j]);

	for (qt = 0; prev[e] >= 0; e = prev[e])
		Q[qt++] = prev_c[e];

	while (qt-- > 0) putchar(Q[qt]);
	printf("\n\n");
}

State reads() {
	State S;
	for (int i = 0; i < 9 && scanf("%d", &S.a[i]) == 1; i++);
	return S;
}

int main()
{
	int T, cs=1;
	memset(seen, 0, sizeof(seen));
	seen_id = 1;
	for (scanf("%d", &T); cs <= T; cs++) {
		printf("Puzzle #%d\n", cs);
		solve(reads());
	}
	return 0;
}
