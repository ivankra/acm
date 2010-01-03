#include <stdio.h>
#include <string.h>

int a[1024][1024], b[1024];
int v[4][4], g[4][4], f[32][32], n;
int name[32][32], bound[32][32];

void do1()
{
	int i, j, k, x, y, p;

	scanf("%d", &n);

	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++)
			name[i][j] = -1;

	for (k = 0, i = 1; i < n; i++)
		for (j = 1; j < n; j++)
			name[i][j] = k++;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &v[i][j]);

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &g[i][j]);

	for (i = 0; i <= n; i++)
		scanf("%d", &bound[n][i]);

	for (i = 0; i <= n; i++)
		scanf("%d", &bound[0][i]);

	for (i = 0; i <= n; i++)
		scanf("%d", &bound[n - i][0]);

	for (i = 0; i <= n; i++)
		scanf("%d", &bound[n - i][n]);

	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++)
			scanf("%d", &f[i][j]);

	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

for (y = 1; y < n; y++) {
    for (x = 1; x < n; x++) {
        p = name[y][x];

        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                if (name[y+i][x+j] < 0) {
                    b[p] += -n * n * v[1+i][1+j] * bound[y+i][x+j];
                } else {
                    a[p][name[y+i][x+j]] += n * n * v[1+i][1+j];
                }
            }
        }

        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                b[p] += g[1+i][1+j] * f[y+i][x+j];
            }
        }

    }
}

k = (n - 1) * (n - 1);
x = k - 1;
	for (i = 0; i < k; i++)
		for (j = 0; j < k; j++)
			printf((j < x) ? "%d " : "%d\n", a[i][j]);

	for (i = 0; i < k; i++)
		printf((i < x) ? "%d " : "%d\n", b[i]);
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;)
		do1();

	return 0;
}
