#include <stdio.h>
#include <string.h>

int main()
{
	static int left[256], right[256], dx[256], dy[256], a[64][64];
	static int d, n, m, t, x, y;
	int i, j, k;

/*    N
    W   E
      S    */

	left['N'] = 'W'; left['W'] = 'S'; left['S'] = 'E'; left['E'] = 'N';
	right['N'] = 'E'; right['E'] = 'S'; right['S'] = 'W'; right['W'] = 'N';

	dx['N'] = 0; dy['N'] = -1;
	dx['S'] = 0; dy['S'] = 1;
	dx['W'] = -1; dy['W'] = 0;
	dx['E'] = 1; dy['E'] = 0;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		memset(a, 1, sizeof(a));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= m && (k = getchar()) != EOF;)
				if (k == ' ')
					a[i][j++] = 0;
				else if (k == '*')
					a[i][j++] = 1;

		scanf("%d %d", &y, &x);
		d = 'N';

		while ((k = getchar()) != EOF && k != 'Q') {
			if (k == 'R' || k == 'r') {
				d = right[d];
				continue;
			} else if (k == 'L' || k == 'l') {
				d = left[d];
				continue;
			} else if (k != 'F' && k != 'f') {
				continue;
			}

			if (a[y + dy[d]][x + dx[d]])
				continue;

			x += dx[d];
			y += dy[d];
		}

		printf("%d %d %c\n", y, x, d);

		if (t > 0) printf("\n");
	}

	return 0;
}
