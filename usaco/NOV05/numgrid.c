/*
ID: infnty1
TASK: numgrid
LANG: C
*/
/* Algorithm: backtracking. */
#include <stdio.h>
#include <string.h>
#include <assert.h>

unsigned can[1000000/32+10];
int valid[8][8], a[8][8], dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };

void go(int y, int x, int n, int z)
{
	int i;

	z = z * 10 + a[y][x];

	if (n == 0) {
		can[z >> 5] |= 1U << (z & 31);
		return;
	}

	for (i = 0; i < 4; i++)
		if (valid[y+dy[i]][x+dx[i]]) go(y+dy[i], x+dx[i], n-1, z);
}

int main()
{
	int i, j;

	freopen("numgrid.in", "r", stdin);
	freopen("numgrid.out", "w", stdout);

	memset(valid, 0, sizeof(valid));
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			valid[i][j] = 1;
			scanf("%d", &a[i][j]);
			assert(0 <= a[i][j] && a[i][j] <= 9);
		}
	}

	memset(can, 0, sizeof(can));
	for (i = 1; i <= 5; i++)
		for (j = 1; j <= 5; j++)
			go(i, j, 5, 0);

	for (i = j = 0; i <= 999999; i++) {
		/*if ((can[i >> 5] >> (i & 31)) & 1U) printf("%d\n",i);*/
		j += ((can[i >> 5] >> (i & 31)) & 1U);
	}

	printf("%d\n", j);
	fflush(stdout);

	return 0;
}
