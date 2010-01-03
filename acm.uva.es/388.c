#include <stdio.h>
#include <ctype.h>

#define INF 0x3FFFFFFF

int main()
{
	static int d[32][32], m;
	static double val[32], rate[1024];
	static char s[1024];
	int i, j, k;

	for (rate[0] = rate[1] = 1., i = 2; i < 1024; i++)
		rate[i] = rate[i - 1] * 0.95;

	while (scanf("%d", &m) == 1) {
		for (i = 0; i <= 26; i++) {
			for (j = 0; j <= 26; j++)
				d[i][j] = INF;
			d[i][i] = 0;
			val[i] = -1;
		}

		while (m-- > 0 && scanf(" %s", s)) {
			k = toupper(s[0]) - 'A' + 1;

			scanf("%lf %s", &val[k], s);
			
			for (i = 0; s[i]; i++) {
				if (s[i] == '*') {
					d[0][k] = d[k][0] = 1;
				} else if (isalpha(s[i])) {
					j = toupper(s[i]) - 'A' + 1;
					d[j][k] = d[k][j] = 1;
				}
			}
		}

		for (k = 0; k <= 26; k++) {
			for (i = 0; i < 26; i++) {
				if (d[i][k] == INF) continue;

				for (j = i + 1; j <= 26; j++) {
					if ((d[i][k] + d[k][j]) >= d[i][j])
						continue;

					d[i][j] = d[j][i] = d[i][k] + d[k][j];
				}
			}
		}

/*for (i = 1; i <= 26; i++) if (val[i] >= 0. && d[0][i] < INF) printf("%c: d=%d v=%.5f x=%.5f\n",i+'A'-1,d[0][i],val[i],val[i]*rate[d[0][i]]);*/

		for (k = -1, i = 1; i <= 26; i++) {
			if (val[i] < 0 || d[0][i] >= INF)
				continue;

			if (k < 0) {
				k = i;
				continue;
			}

			if ((val[i] * rate[d[0][i]]) > (val[k] * rate[d[0][k]]))
				k = i;
		}

		if (k < 0) { for(;;) malloc(100000); }

		printf("Import from %c\n", 'A' + k - 1);
	}

	return 0;
}
