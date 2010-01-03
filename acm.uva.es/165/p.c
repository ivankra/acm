#include <stdio.h>
#include <string.h>

#define MAXS 80
#define INF 0x1FFFFFFF

int h, k;

int sol_a[16], sol_n;
int a[16];

void find(int s[], int p)
{
	int t[MAXS];
	int i, j, m;

	if (p >= k) {
		for (i = 0; s[i] < INF; i++);
		i--;

		if (i > sol_n) {
			sol_n = i;
			memcpy(sol_a, a, sizeof(a));
		}

		return;
	}

	for (a[p] = a[p - 1] + 1; s[a[p] - 1] < INF; a[p]++) {
		for (i = 0; i < MAXS; i++) {
			t[i] = s[i];

			for (j = 1; j <= h && (i - a[p] * j) >= 0; j++) {
				m = s[i - j * a[p]] + j;

				if (m < t[i] && m <= h)
					t[i] = m;
			}
		}

		find(t, p + 1);
	}
}

int main()
{
	int s[MAXS], i;

	while (scanf("%d %d", &h, &k) == 2) {
		if (h == 0 && k == 0)
			break;

		a[0] = 1;

		for (i = 0; i < MAXS; i++)
			s[i] = INF;

		s[0] = 0;

		for (i = 1; i <= h; i++)
			s[i] = i;

		memset(sol_a, 0, sizeof(sol_a));
		sol_n = 0;

		if (k > 0) {
			find(s, 1);
		}

		for (i = 0; i < k; i++)
			printf("%3d", sol_a[i]);
		printf(" ->%3d\n", sol_n);
	}

	return 0;
}
