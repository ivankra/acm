/*
ID: infnty1
LANG: C++
TASK: lineup
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int N, K;

struct Record {
	int a[30], index;
	bool operator <(const Record &b) const { return memcmp(a, b.a, K*sizeof(int)) < 0; }
	bool operator ==(const Record &b) const { return memcmp(a, b.a, K*sizeof(int)) == 0; }
};

Record rec[100010];

int main() {
	freopen("lineup.in", "r", stdin);
	freopen("lineup.out", "w", stdout);

	scanf("%d %d", &N, &K);

	for (int i = 0; i < K; i++)
		rec[0].a[i] = 0;
	rec[0].index = 0;

	for (int i = 1; i <= N; i++) {
		int x;
		scanf("%d", &x);

		for (int j = 0; j < K; j++)
			rec[i].a[j] = rec[i-1].a[j] + ((x >> j) & 1);

		int mi = rec[i].a[0];
		for (int j = 0; j < K; j++)
			mi = min(mi, rec[i].a[j]);

		for (int j = 0; j < K; j++)
			rec[i].a[j] -= mi;

		rec[i].index = i;
	}

	sort(rec, rec+N+1);

	int best = 0;
	for (int i = 0, j = 0; i <= N; i = j) {
		int mi = rec[i].index, ma = rec[i].index;
		for (j = i+1; j <= N && rec[i] == rec[j]; j++) {
			mi = min(mi, rec[j].index);
			ma = max(ma, rec[j].index);
		}
		best = max(best, ma - mi);
	}
	printf("%d\n", best);
}
