#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

int prime[100], order[100], prime_max[1000], got[802][64][16][2], got_id;
char memo[802][64][16][2];
int order_minr[100], order_of_2;

int even;
int can(int n, int pi, int t) {
	char &res = memo[n][pi][t][even];
	if (got[n][pi][t][even] == got_id) return res;
	got[n][pi][t][even] = got_id;

	if (n == 0) return res = (t==0);
	if (t <= 0) return res = 0;
	if (pi >= 62) return res = 0;

	if (n < order_minr[pi]) return res = 0;

	if (even == 0 || pi > order_of_2) {
		if ((n+t)&1) return res = 0;
	}

	int p = order[pi];

	int u = prime_max[p];
	u <?= t;
	if (p == 2) u <?= even;

	for (; u >= 0; u--)
		if (n>=u*p && can(n-u*p, pi+1, t-u)) return res = 1;

	return res = 0;
}

bool cmp(int x, int y) {
	char s[20], t[20];
	sprintf(s, "%d+", x);
	sprintf(t, "%d+", y);
	return strcmp(s, t) < 0;
}

int main() {
	int P = 0;
	for (int i = 2; i <= 300; i++) {
		for (int j = 0; j < P; j++)
			if (i % prime[j] == 0) goto skip;
		prime[P++] = i;
skip:;
	}
	assert(P == 62);

	for (int i = 0; i < 100; i++)
		order[i] = (i < P ? prime[i] : (1<<20));
	sort(order, order+P, cmp);

	order_minr[99] = order[99];
	for (int i = 98; i >= 0; i--)
		order_minr[i] = min(order_minr[i+1], order[i]);

	for (int i = 0; i < 100; i++)
		if (order[i] == 2) { order_of_2 = i; break; }

//	memset(got, 0, sizeof(got));
	got_id = 42;

	int NB, NQ;
	scanf("%d", &NB);

	for (int cs = 1; cs <= NB; cs++) {
		printf("Block %d:\n", cs);
		got_id++;

		for (int i = 1; i <= 61; i++) scanf("%d", &prime_max[prime[i]]);
		prime_max[2] = 1;

		scanf("%d", &NQ);
		for (int qn = 1; qn <= NQ; qn++) {
			int n, t;
			scanf("%d %d %d", &n, &t, &even);

			printf("Query %d:\n", qn);
			if (!can(n, 0, t)) {
				printf("No Solution.\n");
				continue;
			}

			for (int pi = 0; pi < 62 && t > 0 && n > 0; pi++) {
				int p = order[pi];
				int u = prime_max[p];
				u <?= t;
				if (p == 2) u <?= even;

				for (; u >= 0; u--) {
					if (n>=u*p && can(n-u*p, pi+1, t-u)) {
						for (int i = 0; i < u; i++) {
							printf(t>1 ? "%d+" : "%d", p);
							n -= p; t--;
						}
						break;
					}
				}
			}
			printf("\n");
		}

		printf("\n");
	}
}
