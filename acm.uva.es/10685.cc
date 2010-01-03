#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

char namebuf[6000][32], *name[6000];
int N, M, par[6000], size[6000];

int f(int x) {
	if (par[par[x]] != par[x]) {
		par[x] = f(par[x]);
	}
	return par[x];
}

bool cmp(char *a, char *b) { return strcmp(a, b) < 0; }

int readName()
{
	char buf[50];
	scanf(" %s", buf);

	int left = 0, right = N-1;
	while (left <= right) {
		int mid = (left + right) / 2;
		int t = strcmp(name[mid], buf);
		if (t < 0)
			left = mid + 1;
		else if (t == 0)
			return mid;
		else
			right = mid - 1;
	}
	abort();
}

int main()
{
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++) {
			scanf(" %s", namebuf[i]);
			name[i] = namebuf[i];
		}

		sort(name, name+N, cmp);

		for (int i = 0; i < N; i++) {
			par[i] = i;
			size[i] = 1;
		}

		for (int i = 0; i < M; i++) {
			int x = f(readName());
			int y = f(readName());
			if (x == y) continue;

			if (size[x] < size[y]) {
				par[x] = y;
				size[y] += size[x];
			} else {
				par[y] = x;
				size[x] += size[y];
			}
		}

		int best = 0;
		for (int i = 0; i < N; i++)
			best = max(best, size[i]);
		printf("%d\n", best);
	}
}
