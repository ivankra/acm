/*
ID: infnty1
LANG: C++
TASK: cowjog
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int N, K;
vector<int> adjY[1010], adjZ[1010];
vector<int> routes[1010];

void heapUp(int *a, int i)
{
	--a;
	while (i > 1 && a[i] < a[i / 2]) {
		swap(a[i], a[i / 2]);
		i /= 2;
	}
}

void heapDown(int *a, int i, int n)
{
	--a;
	while (2*i <= n) {
		int j = 2 * i;
		if (j + 1 <= n && a[j+1] < a[j]) j++;
		if (a[j] >= a[i]) break;
		swap(a[i], a[j]);
		i = j;
	}
}

void add(vector<int> &v, int z)
{
	if ((int)v.size() < K) {
		v.push_back(z);
		heapUp(&v[0], v.size());
	} else if (z > v[0]) {
		v[0] = z;
		heapDown(&v[0], 1, v.size());
	}
}

int main()
{
	freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);

	int M, x, y, z;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &z);
		if (x < y) swap(x, y);
		adjY[x].push_back(y);
		adjZ[x].push_back(z);
	}

	routes[1].push_back(0);
	for (x = 2; x <= N; x++) {
		routes[x].clear();
		routes[x].reserve(K + 5);
		for (int i = 0; i < (int)adjY[x].size(); i++) {
			y = adjY[x][i];
			z = adjZ[x][i];

			const vector<int> &rr = routes[y];
			for (int j = 0; j < (int)rr.size(); ++j)
				add(routes[x], z + rr[j]);
		}
		sort(routes[x].begin(), routes[x].end());
	}

	for (int i = 0; i < K; i++)
		printf("%d\n", i < (int)routes[N].size() ? routes[N][i] : -1);

}
