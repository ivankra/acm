#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 1048576

char *list[16384], tab[128][128];
int count[16384], n, nrows, ncols;
int dy[]={-1,-1,-1,0,0,1,1,1}, dx[]={-1,0,1,-1,1,-1,0,1};

int child[MAX], sib[MAX], term[MAX], last;
char alpha[MAX];

void go(int y, int x, int d)
{
	int p;
	for (p = 0;; y += dy[d], x += dx[d]) {
		for (p = child[p]; alpha[p] < tab[y][x]; p = sib[p]);
		if (alpha[p] != tab[y][x]) return;
		if (term[p]) count[term[p]-1]++;
	}
}

void insert(char *s, int id)
{
	int p, x;

	for (p = 0; *s; s++) {
		for (x = child[p]; x != 0 && alpha[x] != *s; x = sib[x]);

		if (x != 0) {
			p = x;
			continue;
		}

/*		assert(last < MAX-10);*/

		sib[last] = child[p];
		child[p] = last;
		p = last; last++;
		alpha[p] = *s;
		term[p] = 0;
		child[p] = 0;
	}
	term[p] = id;
}

int cmp(const void *p, const void *q) { return strcmp(*(char **)p, *(char **)q); }

void solve()
{
	static char buf[65536];
	int i, j, k, q, nq;

	i = scanf("%d", &n);
	assert(i == 1 && 1 <= n && n <= 15000);

	for (i = 0; i < n; i++) {
		j = scanf(" %[a-z]", buf);
		assert(j == 1);
		list[i] = strdup(buf);
	}

	qsort(list, n, sizeof(list[0]), &cmp);

	last = 1;
	child[0] = sib[0] = term[0] = 0;
	alpha[0] = 127;

	for (i = n; i-- > 0;) insert(list[i],i+1);

	i = scanf("%d", &nq);
	assert(i == 1);

	for (q = 1; q <= nq; q++) {
		i = scanf("%d %d", &nrows, &ncols);
		assert(i == 2 && 0 <= nrows && nrows < 125 && 0 <= ncols && ncols < 125);

		printf("Query #%d\n", q);

		for (i = 0; i <= nrows+1; i++)
			for (j = 0; j <= ncols+1; j++)
				tab[i][j] = ' ';

		for (i = 1; i <= nrows; i++)
			for (j = 1; j <= ncols; j++) {
				while ((k = getchar()) != EOF && k == '\n');
				assert(k != EOF);
				tab[i][j] = ('a' <= k && k <= 'z') ? k : ' ';
			}

		for (i = 0; i < n; i++)
			count[i] = 0;

		for (i = 1; i <= nrows; i++)
			for (j = 1; j <= ncols; j++)
				for (k = 0; k < 8; k++)
					go(i,j,k);

		for (i = 0; i < n; i++)
			if (count[i] > 0) printf("%s %d\n", list[i], count[i]);
	}

	for (i = 0; i < n; i++)
		free(list[i]);
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		printf("Test Case #%d\n", c);
		solve();
	}

	return 0;
}
