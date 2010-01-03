#include <stdlib.h>

int read(int, unsigned char *, int);
int write(int, unsigned char *, int);

unsigned char tmp[256], inbuf[1048576], outbuf[65536];
int map[128][128], isdig[256], isnd[256], ntests, width, height;
int sy[65536], sx[65536], x0;

int main2()
{
	unsigned char *p, *q;
	int i, j, r, t;

	for (i = 0; i <= 100; i++)
		for (j = 0; j <= 100; j++)
			map[i][j] = 1;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	isnd['\n'] = isnd['0'] = isnd['1'] = 1;

	inbuf[read(0, p = inbuf, sizeof(inbuf))] = '\n';
	q = outbuf;

#define R(x) {while(!isdig[*p])p++;for(i=*p++-'0';isdig[*p];)i=i*10+*p++-'0';x=i;}

	R(ntests);

	while (ntests--) {
		R(sy[0]); R(sx[0]);

		while (*p < '0') p++;

		for (i = 0; *p >= '0';) map[1][++i] = *p++ - '0';
		width = i;

		for (j = 1;;) {
			while (*p++ != '\n');

			while (isnd[*p] == 0) p++;
			if (*p == '\n') break;

			for (j++, i = 0; *p >= '0';)
				map[j][++i] = *p++ - '0';
		}
		height = j;

		if (map[sy[0]][sx[0]]) {
			*q++ = '0'; *q++ = '\n';
		} else {
			map[sy[0]][sx[0]] = 1;
			for (r = 1, t = 1; t-- > 0;) {
				i = sy[t];
				x0 = j = sx[t];

#define GO(Y,X) if (map[Y][X] == 0) { map[sy[t]=Y][sx[t]=X]=1; r++; t++; }
				GO(i+1, j); GO(i-1, j);

				for (j++; map[i][j] == 0; j++) {
					map[i][j] = 1;
					r++;
					GO(i+1, j); GO(i-1, j);
				}

				for (j = x0 - 1; map[i][j] == 0; j--) {
					map[i][j] = 1;
					r++;
					GO(i+1, j); GO(i-1, j);
				}
			}

			for (j = r, i = 0; j > 0; j /= 10)
				tmp[i++] = (j % 10) + '0';

			while (i--) *q++ = tmp[i];
			*q++ = '\n';
		}

		if (ntests) {
			*q++ = '\n';

			for (i = 1; i <= height; i++)
				for (j = 1; j <= width; j++)
					map[i][j] = 1;
		}
	}

	write(1, outbuf, q - outbuf);
	exit(0);
}
