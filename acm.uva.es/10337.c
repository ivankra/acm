#include <stdio.h>

int read(int, char *, int);

int main()
{
	static int w[1024][16], isdig[256], isdigx[256], r1[16], r2[16], x, t;
	static char inbuf[8*1048576];
	int i, k, *row, *next;
	char *inptr;

	for (i = 0; i < 256; i++) isdigx[i] = isdig[i] = 0;
	for (i = '0'; i <= '9'; i++)isdigx[i] = isdig[i] = 1;
	isdigx[0] = 1; isdigx['-'] = 1;

	inbuf[read(0, inptr = inbuf, sizeof(inbuf))] = 0;

#define READ(x) \
  {while(!isdigx[(int)*inptr])inptr++;if((*inptr)==0)return(0);else if(\
  (*inptr)=='-'){for(inptr++,x=0;isdig[(int)*inptr];)x=x*10+(*inptr++)-'0';\
  x=-x;}else{for(x=(*inptr++)-'0';isdig[(int)*inptr];)x=x*10+(*inptr++)-'0';}}

	READ(t);

	while (t-- > 0) {
		READ(x);
		x /= 100;

		for (k = 10; k >= 1; k--) {
			for (i = 0; i < x; i++) {
				register int m;
				READ(m);
				w[i][k] = m;
			}
		}

		for (row = r1, next = r2, i = 0; i <= 11; i++)
			r1[i] = 0x3FFFFFFF;
		r1[1] = 0;
		r2[0] = r2[11] = 0x3FFFFFFF;

		for (k = 0; k < x; k++) {
			for (i = 1; i <= 10; i++) {
				register int m;

				next[i] = row[i - 1] - w[k][i - 1] + 60;

				m = row[i] - w[k][i] + 30;
				if (m < next[i])
					next[i] = m;

				m = row[i + 1] - w[k][i + 1] + 20;
				if (m < next[i])
					next[i] = m;
			}

			row = next;
			next = (next == r1) ? r2 : r1;
		}

		printf("%d\n\n", row[1]);
	}

	return 0;
}


/*
#include <stdio.h>

int main()
{
	static int w[1024][16], r1[16], r2[16], x, t;
	int i, k, m, *row, *next;

	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d", &x);
		x /= 100;

		for (k = 10; k >= 1; k--)
			for (i = 0; i < x; i++)
				scanf("%d", &w[i][k]);

		row = r1;
		next = r2;
		for (i = 0; i <= 11; i++)
			row[i] = 0x3FFFFFFF;
		row[1] = 0;

		for (k = 0; k < x; k++) {
			for (i = 1; i <= 10; i++) {
				next[i] = row[i - 1] - w[k][i - 1] + 60;

				m = row[i] - w[k][i] + 30;
				if (m < next[i])
					next[i] = m;

				m = row[i + 1] - w[k][i + 1] + 20;
				if (m < next[i])
					next[i] = m;
			}
			next[0] = next[11] = 0x3FFFFFFF;

			row = next;
			next = (next == r1) ? r2 : r1;
		}

		printf("%d\n\n", row[1]);
	}

	return 0;
}
*/