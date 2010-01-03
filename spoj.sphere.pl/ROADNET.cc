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
#include <queue>
using namespace std;

int d[256][256];

int main()
{
	int T, N;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &d[i][j]);

		int i, j, k;
		for (i = 0; i < N; i++) {
			for (j = i+1; j < N; j++) {
				for (k = 0; k < N; k++)
					if (k != i && k != j && d[i][k] + d[k][j] == d[i][j]) break;
				if (k == N)
					printf("%d %d\n", i+1, j+1);
			}
		}

		if (cs != T) printf("\n");
	}
}
