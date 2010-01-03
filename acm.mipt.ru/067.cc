#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> divs[2010];
int order[2010], N, nleft[2010], out[2010], used[2010];

void doit(int k) {
	if (k == N) {
		for (int i = 1; i <= N; i++)
			printf(i<N ? "%d " : "%d\n", out[i]);
		return;
	}

	int d = order[k];
	for (vector<int>::const_iterator it = divs[d].begin(); it != divs[d].end(); it++) {
		int x = *it;
		if (!used[x]) {
			out[d] = x; used[x] = 1;
			doit(k+1);
			used[x] = 0;
		}
	}
}

bool cmp(int x, int y) { return divs[x].size() < divs[y].size(); }

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) order[i] = 1+i;

	for (int i = 2; i <= N+1; i++)
		for (int j = 1; j <= i; j++)
			if (i % j == 0)
				divs[j].push_back(i);

	sort(order, order+N, cmp);

	memset(nleft, 0, sizeof(nleft));
	for (int i = 1; i <= N; i++)
		nleft[i] = divs[i].size();

	memset(out, 0, sizeof(out));
	memset(used, 0, sizeof(used));
	doit(0);
}
