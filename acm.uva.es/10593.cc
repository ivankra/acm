#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <cassert>
using namespace std;

int a[512][512], b[512][512], n;

int solve()
{
	int i, j, r, t;

	for (i = 0; i < n; i++) {
		b[i][0] = (a[i][0] == '.') ? 0 : 1;
		b[0][i] = (a[0][i] == '.') ? 0 : 1;
	}

	for (i = 1; i < n; i++)
		for (j = 1; j < n; j++) {
			if (a[i][j] == '.') { b[i][j] = 0; continue; }
			t = min(b[i-1][j], b[i][j-1]);
			b[i][j] = (a[i-t][j-t] == '.') ? t : (t+1);
		}

	r = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (b[i][j] > 1) r += b[i][j] - 1;

	for (i = 1; i < n; i++) {
		for (j = 1; j < n-1; j++) {
			if (a[i][j] == '.') { b[i][j] = 0; continue; }
			t = min(min(b[i-1][j-1], b[i-1][j+1]), i>>1);
			b[i][j] = (a[i-2*t][j] == '.') ? t : (t+1);
		}
		b[i][n-1] = (a[i][n-1] == '.') ? 0 : 1;
	}

	for (i = 1; i < n; i++)
		for (j = 1; j < n; j++) {
			t = min(b[i][j], b[i-1][j]+1);
			if (t > 1) r += t - 1;
		}

	return r;
}

int main()
{
	int i, j, k;

	while (scanf("%d", &n) == 1) {
		assert(1 <= n && n <= 500);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++) {
				while ((k = getchar()) != EOF && !isalpha(k) && k != '.');
				a[i][j] = k;
			}

		if ((n & 1) == 0) {
			for (i = 0; i <= n; i++) a[i][n]=a[n][i]='.';
			n++;
		}

		printf("%d\n", solve());
	}

	return 0;
}
