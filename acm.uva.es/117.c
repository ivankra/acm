#include <stdio.h>
#include <string.h>

int main()
{
	static int d[32][32], g[32], r;
	static char s[65536];
	int i, j, k;

	for (;;) {
		for (i = 0; i < 26; i++)
			for (j = 0; j < 26; j++)
				d[i][j] = 0x3FFFFFFF;

		memset(g, 0, sizeof(g));

		for (r = 0; scanf(" %s", s) == 1 && strcmp(s, "deadend") != 0;) {
			k = strlen(s);
			i = s[0] - 'a';	
			j = s[k - 1] - 'a';
			if (d[i][j] > k)
				d[i][j] = d[j][i] = k;
			g[i]++;
			g[j]++;
			r += k;
		}

		if (r == 0)
			break;

		for (k = 0; k < 26; k++)
			for (i = 0; i < 26; i++)
				for (j = 0; j < 26; j++)
					if (d[i][j] > (d[i][k] + d[k][j]))
						d[i][j] = d[i][k] + d[k][j];

		for (i = 0; i < 26 && (g[i] & 1) == 0; i++);

		if (i < 26) {
			for (j = i + 1; j < 26 && (g[j] & 1) == 0; j++);
			r += d[i][j];
		}

		printf("%d\n", r);
	}

	return 0;
}
