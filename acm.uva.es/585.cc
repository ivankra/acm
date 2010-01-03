#include <cstdio>
#include <algorithm>
using namespace std;

char image[128][256];
int tab[128][256], n;

int solve()
{
	int i, k, r;

	r = 0;

	for (k = 1; k <= n; k++) {
		for (i = 2 * (n - k) + 1; i >= 1; i -= 2) {
			if (image[k][i] != '-') {
				tab[k][i] = 0;
				continue;
			}

			if (k > 1 && image[k - 1][i + 1] == '-')
				tab[k][i] = min(tab[k - 1][i], tab[k - 1][i + 2]) + 1;
			else
				tab[k][i] = 1;

			if (tab[k][i] > r)
				r = tab[k][i];
		}
	}

	for (k = n; k >= 1; k--) {
		for (i = 2 * (n - k); i >= 2; i -= 2) {
			if (image[k][i] != '-') {
				tab[k][i] = 0;
				continue;
			}

			if (k < n && image[k + 1][i - 1] == '-')
				tab[k][i] = min(tab[k + 1][i], tab[k + 1][i - 2]) + 1;
			else
				tab[k][i] = 1;

			if (tab[k][i] > r)
				r = tab[k][i];
		}
	}

	return r * r;
}

int main()
{
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		for (int i = 1; i <= n; i++)
			scanf(" %s", image[i]+1);
		printf("Triangle #%d\nThe largest triangle area is %d.\n\n", cs, solve());
	}
}
