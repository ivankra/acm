#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int d[16][16], got[16][65536], tab[16][65536], n, id=42;

int f(int s, int m)
{
	int i, j;

	if (got[s][m] == id) return tab[s][m];
	got[s][m] = id;

	if ((m + 1) == (1 << n))
		return (tab[s][m] = d[s][0]);

	for (tab[s][m] = 0x1FFFFFFF, i = 0; i < n; i++) {
		if ((m >> i) & 1) continue;
		j = d[s][i] + f(i, m ^ (1 << i));
		if (j < tab[s][m]) tab[s][m] = j;
	}

	return tab[s][m];
}

int G(int x, int y)
{
	if (x < 0) x = -x;
	if (y < 0) y = -y;

	if (x >= y)
		return x;
	else
		return y;
}

int main()
{
	int width, height, py[256], px[256];
	int i, j, k;

	while (scanf("%d %d", &height, &width) == 2 && height > 0) {
		n = 0;
		for (i = 1; i <= height; i++) {
			for (j = 1; j <= width && (k = getchar()) != EOF;) {
				if (k == '#' || k == 'L') {
					py[n] = i; px[n] = j; n++; j++;
				} else if (k == '.') {
					j++;
				}
			}
		}

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				d[i][j] = G(px[i] - px[j], py[i] - py[j]);


/*printf("n=%d\n",n);
for(i=0;i<n;i++){
 for(j=0;j<n;j++)printf(" %5d",d[i][j]);printf("\n");}*/

		id++;
		printf("%d\n", f(0,1));
	}

	return 0;
}
