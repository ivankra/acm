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

double p[128][128];

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				p[i][j] = 0;
			p[i][i] = 1;
		}

		for (int i = 0; i < m; i++) {
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c);
			if (c/100.0 > p[x][y]) p[x][y] = p[y][x] = c/100.0;
		}

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (p[i][k] * p[k][j] > p[i][j])
						p[i][j] = p[i][k] * p[k][j];
		printf("%.6f percent\n", p[1][n]*100);
	}
}
