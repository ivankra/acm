#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

int main()
{
	static char inbuf[1048576], outbuf[1048576], tmp[256];
	static int isdig[256], isdigm[256], a[256], sum[256], rx[128][128], ry[128][128], n;
	int i, k, m, s, t;
	char *p, *q, *u;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	for (i = '0'; i <= '9'; i++) isdigm[i] = 1; isdigm['-'] = 1;

	read(0, p = inbuf, sizeof(inbuf));
	q = outbuf;

#define R(x) {while(!isdigm[*p])p++;\
	      if(*p=='-'){p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';x=-x;}\
	      else{for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}}
#define W(x) {if(x==0){*q++='0';}else{if(x<0){x=-x;*q++='-';}for(u=tmp;x>0;x/=10)*u++=(x%10)+'0';while(u-->tmp)*q++=*u;}}

	for (;;) {
		R(i); if (i <= 0) break; n = i;

		for (i = 0, sum[0] = 0; i < n; i++) {
			R(k); a[i] = k;
			sum[i + 1] = sum[i] + k;
		}

		for (i = 0; i <= n; i++)
			rx[0][i] = 0;

		for (i = 0; i <= n; i++)
			ry[0][i] = 0;

		for (m = 1; m <= n; m++) {
			for (k = 0; (k + m) <= n; k++) {
				rx[m][k] = a[k] + ry[m - 1][k + 1];

				for (s = 0, i = 1; i <= m; i++) {
					s += a[k + i - 1];
					t = s + ry[m - i][k + i];
					if (t > rx[m][k]) rx[m][k] = t;
				}

				for (s = 0, i = 1; i <= m; i++) {
					s += a[k + m - i];
					t = s + ry[m - i][k];
					if (t > rx[m][k]) rx[m][k] = t;
				}

				ry[m][k] = sum[k + m] - sum[k] - rx[m][k];
			}
		}

		i = rx[n][0] - ry[n][0];
		W(i);
		*q++ = '\n';
	}

	write(1, outbuf, q - outbuf);
	exit(0);
}
