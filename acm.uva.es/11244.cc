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

char a[128][128];
int n, m;

int main()
{
	while (scanf("%d %d", &n, &m) == 2 && (n != 0 || m != 0)) {
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf(" %c", &a[i][j]);

		int res = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (a[i][j] != '*') continue;

				for (int dx = -1; dx <= 1; dx++)
					for (int dy = -1; dy <= 1; dy++)
						if (a[i+dy][j+dx] == '*' && (dx != 0 || dy != 0)) goto skip;
				res++;
skip:;
			}
		}

		printf("%d\n", res);
	}
}
