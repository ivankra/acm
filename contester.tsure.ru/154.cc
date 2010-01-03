#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

int d[128][128], v[128], p[128], n, m, x, y, z, c;
int main()
{
	map<int, int> ma;

	scanf("%d %d", &n, &m);
	z = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			d[i][j] = (i==j)?0:(1<<30);
		v[i] = 0;
		p[i] = 1<<30;
	}

	while (m-- > 0 && scanf("%d %d %d", &x, &y, &c) == 3) {
		if (ma.count(x) == 0) ma[x] = z++;
		if (ma.count(y) == 0) ma[y] = z++;
		x = ma[x]; y = ma[y];
		if (c < d[x][y]) d[x][y] = d[y][x] = c;
	}

	p[0] = 0;
	for (z = 0;;) {
		int s = -1;
		for (int t = 0; t < n; t++)
			if (!v[t] && (s<0 || p[t]<p[s])) s = t;
		if (s < 0) break;

		v[s] = 1;
		z += p[s];
		for (int t = 0; t < n; t++)
			p[t] <?= d[s][t];
	}

	printf("%d\n", z);
}
