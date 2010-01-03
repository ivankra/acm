/*
ID: mjf28791
PROG: checker
LANG: C
*/
#include <stdio.h>
#include <string.h>

static int acol[256], adiag1[256], adiag2[256], state[256], sol[16][16];
static int n, n1, nsol;

#define ATTACKED(r,c) (acol[c] || adiag1[r + c] || adiag2[n - r + c])
#define PUT(r, c) state[r] = c; acol[c] = 1; \
		  adiag1[r + c] = 1; adiag2[n - r + c] = 1;
#define REMOVE(r, c) acol[c] = 0; adiag1[r + c] = 0; adiag2[n - r + c] = 0;

static void search(int row)
{
	register int i;

	if (row == n1) {
		for (i = 0; i < n; i++) {
			if (ATTACKED(n1, i)) continue;

			if (nsol < 3) {
				memcpy(sol[nsol], state, sizeof(int) * n);
				sol[nsol][n1] = i;
			}

			nsol++;
		}

		return;
	}

	for (i = 0; i < n; i++) {
		if (ATTACKED(row, i)) continue;

		PUT(row, i);	
		search(row + 1);
		REMOVE(row, i);
	}
}

int main()
{
	int i, j;

	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);

	scanf("%d", &n);
	n1 = n - 1;

	for (nsol = 0, i = 0; i < 256; i++)
		acol[i] = adiag1[i] = adiag2[i] = 0;

	if (n >= 8) {
		for (i = 0; i < (n / 2); i++) {
			PUT(0, i);
			search(1);
			REMOVE(0, i);
		}

		nsol *= 2;

		if ((n % 2) == 1) {
			PUT(0, (n / 2));
			search(1);
		}
	} else {
		search(0);
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < n; j++)
			printf(((j + 1) < n) ? "%d " : "%d\n", sol[i][j] + 1);
	}

	printf("%d\n", nsol);

	return 0;
}
