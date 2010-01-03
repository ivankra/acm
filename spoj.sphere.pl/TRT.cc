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

int v[3000], N;
int best[2002][2002];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &v[i]);

	for (int i = 0; i < N; i++)
		best[N][i] = N * v[i];

	for (int a = N-1; a >= 1; a--) {
		int m = N-a+1;
		for (int i = 0; i+m <= N; i++) {
			int j = i + m - 1;
			best[a][i] = max(a * v[i] + best[a+1][i+1],
				             a * v[j] + best[a+1][i]);
		}
	}
	printf("%d\n", best[1][0]);
}
