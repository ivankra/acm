/*
ID: infnty1
TASK: bdsum
LANG: C++
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
using namespace std;

int C[16][16], a[16], n, final;

int main()
{
	freopen("bdsum.in", "r", stdin);
	freopen("bdsum.out", "w", stdout);

	scanf("%d %d", &n, &final);
	assert(1 <= n && n <= 10 && 1 <= final && final <= 4116);

	memset(C, 0, sizeof(C));
	for (int i = 0; i < 16; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}

	for (int i = 0; i < n; i++) a[i] = i+1;

	do {
		int sum = 0, *cc = C[n-1];
		for (int i = 0; i < n; i++) sum += (*cc++) * a[i];
		if (sum == final) break;
	} while(next_permutation(a, a+n));

	for (int i = 0; i < n; i++)
		printf(i+1 < n ? "%d " : "%d\n", a[i]);

	return 0;
}
