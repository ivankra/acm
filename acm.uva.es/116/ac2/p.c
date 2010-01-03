#include <stdio.h>

int read(int, char *, int);

int main()
{
	static int a[16][128], d[16][128], s[16][128], m, n;
	static int isdig[256], isdigx[256];
	static char inbuf[4*1048576];
	register int i, j, k;
	register char *inptr;

	for (i = 0; i < 256; i++)
		isdigx[i] = isdig[i] = (i >= '0' && i <= '9');
	isdigx[0] = 1;
	isdigx['-'] = 1;

	inbuf[read(0, inptr = inbuf, sizeof(inbuf))] = '\0';

#define READ(x)\
{\
	while (!isdigx[(int)*inptr]) inptr++;\
	if (*inptr == '\0') return 0;\
	else if (*inptr == '-') {\
		for (inptr++, x = 0; isdig[(int)*inptr];)\
			x = x * 10 + *inptr++ - '0';\
		x = -x;\
	} else {\
		for (x = *inptr++ - '0'; isdig[(int)*inptr];)\
			x = x * 10 + *inptr++ - '0';\
	}\
}

	for (;;) {
		READ(m);
		READ(n);

		for (i = 1; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				READ(k);
				a[i][j] = k;
			}
		}

		for (i = 1; i <= m; i++)
			d[i][n] = a[i][n];

		for (k = n - 1; k >= 1; k--) {
			for (i = 1; i <= m; i++) {
				j = (i == 1) ? m : (i - 1);

				if ((d[i][k + 1] < d[j][k + 1]) ||
				    (d[i][k + 1] == d[j][k + 1] && j > i)) {
					d[i][k] = d[i][k + 1];
					s[i][k] = i;
				} else {
					d[i][k] = d[j][k + 1];
					s[i][k] = j;
				}

				j = (i == m) ? 1 : (i + 1);
				if ((d[j][k + 1] < d[i][k]) ||
				    (d[j][k + 1] == d[i][k] && s[i][k] > j)) {
					d[i][k] = d[j][k + 1];
					s[i][k] = j;
				}

				d[i][k] += a[i][k];
			}
		}

		for (k = 1, i = 2; i <= m; i++)
			if (d[i][1] < d[k][1]) k = i;

		for (i = 1, j = k; i <= n; j = s[j][i++])
			printf((i == n) ? "%d\n" : "%d ", j);

		printf("%d\n", d[k][1]);
	}

	return 0;
}
