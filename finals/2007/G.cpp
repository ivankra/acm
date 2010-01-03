// ACM ICPC World Finals 2007
// Problem G. Network.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int order[10], size[10], buf, N, M;
struct Packet { int id, a, b; } pack[1024];

bool has[5][65536];

int simulate() {
	int maxUsed = 0;
	memset(has, 0, sizeof(has));

	int s[5], total[5];
	memset(s, 0, sizeof(s));
	memset(total, 0, sizeof(total));

	for (int pi = 0; pi < M; pi++) {
		Packet &p = pack[pi];
		for (int i = p.a; i <= p.b; i++)
			has[p.id][i] = true;
		total[p.id] += p.b - p.a + 1;

		while (s[p.id] < size[p.id] && has[p.id][s[p.id]])
			s[p.id]++;

		int used = 0, flag = 1;
		for (int i = 0; i < N; i++) {
			int j = order[i];
			if (flag == 0) {
				used += total[j];
			} else if (s[j] < size[j]) {
				used += total[j] - s[j];
				flag = 0;
			}
		}
		maxUsed = max(maxUsed, used);
	}

	return maxUsed;
}

int main() {
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++) scanf("%d", &size[i]);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &pack[i].id, &pack[i].a, &pack[i].b);
			pack[i].id--;
			pack[i].a--;
			pack[i].b--;
		}

		int best = 64000;

		for (int i = 0; i < N; i++) order[i] = i;
		do {
			best = min(best, simulate());
		} while (next_permutation(order, order+N));

		printf("Case %d: %d\n\n", cs, best);
	}
}
