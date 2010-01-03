#include <stdio.h>

int read(int, unsigned char *, int);

unsigned char inbuf[1048576];
int map[128][128], isdig[256], isnd[256], ntests, width, height;
int sy[65536], sx[65536];

int main()
{
	unsigned char *p;
	int i, j, k, r;

	for (i = 0; i < 128; i++)
		for (j = 0; j < 128; j++)
			map[i][j] = 1;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	isnd['\n'] = isnd['0'] = isnd['1'] = 1;

	inbuf[read(0, p = inbuf, sizeof(inbuf))] = '\n';

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
			printf("0\n");
		} else {
			for (r = 0, k = 1; k-- > 0;) {
				i = sy[k];
				j = sx[k];
				map[i][j] = 1;
				r++;

#define GO(Y,X) if (map[Y][X] == 0) { map[sy[k]=Y][sx[k]=X]=1; k++; }
				GO(i+1, j); GO(i-1, j); GO(i, j+1); GO(i, j-1);
			}
			printf("%d\n", r);
		}

		if (ntests) {
			putchar('\n');

			for (i = 1; i <= height; i++)
				for (j = 1; j <= width; j++)
					map[i][j] = 1;
		}
	}

	return 0;
}
