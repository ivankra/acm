#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int mul[4][4]={{1,1,0,0},{2,1,0,0},{0,2,2,0},{0,0,0,0}};	

int src[128], dst, n;
int can[128][128][4], first[128][128][4];
int Xc1[128][128][4], Xc2[128][128][4], Xm[128][128][4];
int seg[128], segchr[128];

void prn(int len, int offs, int d)
{
	int m=Xm[len][offs][d], c1=Xc1[len][offs][d], c2=Xc2[len][offs][d], i;
	if (len < 2) {
		putchar(src[offs]+'a');
	} else {
		putchar('(');
		printf("%d", first[len][offs][d]);
		prn(m, offs, c1);
		prn(len-m, offs+m, c2);
		putchar(')');
		if (len == n) putchar('\n');
	}
}

void join(int len, int offs, int d)
{
	int m=Xm[len][offs][d], c1=Xc1[len][offs][d], c2=Xc2[len][offs][d], i;

	if (len < 2) return;

	join(m, offs, c1);
	join(len-m, offs+m, c2);

	for (i = offs+1; i < offs+len; i++)
		seg[i] = seg[offs];
	segchr[seg[offs]] = mul[c1][c2];

	for (i = 0; i < n; i++)
		if (i==0 || seg[i-1]!=seg[i]) putchar(segchr[i]+'a');
	putchar('\n');
}

int solve()
{
	int i, k, m, c1, c2;

	if (n <= 0) return 1;
	if (dst < 0 || dst > 2) assert(0==1);

	for (i = 0; i < n; i++) {
		can[1][i][0] = can[1][i][1] = can[1][i][2] = 0;
		can[1][i][src[i]] = 1;
	}

	for(k=2;k<=n;k++) for(i=0;i<=n-k;i++) {
		can[k][i][0]=can[k][i][1]=can[k][i][2] = 0;
		for (m=1;m<k;m++) for(c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
			if ((can[m][i][c1] & can[k-m][i+m][c2]) == 0) continue;
			int d = mul[c1][c2];

			int t;
			if (m > 1)
				t = first[m][i][c1];
			else if (k-m > 1)
				t = first[k-m][i+m][c2];
			else
				t = i;

/*printf("k=%d i=%d d=%d m=%d c1=%d c2=%d  t=%d first=%d\n",
 k,i,d,m,c1,c2, t, first[k][i][d]);*/

			if (can[k][i][d] == 0) goto ok;
			if (first[k][i][d] < t) continue;
			if (first[k][i][d] > t) goto ok;

			if (Xm[k][i][d] < m) continue;
			if (Xm[k][i][d] > m) goto ok;

ok:			can[k][i][d] = 1;
			first[k][i][d] = t;
			Xm[k][i][d]=m; Xc1[k][i][d]=c1; Xc2[k][i][d]=c2;
		}
	}

	if (!can[n][0][dst]) return 1;

	for (i = 0; i < n; i++) {
		seg[i] = i;
		segchr[i] = src[i];
	}

	prn(n,0,dst);
/*
	for (i = 0; i < n; i++) putchar(src[i]+'a'); putchar('\n');
	join(n, 0, dst);
*/
	return 0;
}

int main()
{
	static char buf[65536], buf2;
	int i, t=0;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0) {
		gets(buf);
		for (n = i = 0; buf[i]; i++)
			if (isalpha(buf[i]))
				src[n++] = toupper(buf[i]) - 'A';
assert(n>0);
		gets(buf);
		buf2 = 0;
		sscanf(buf, " %c", &buf2);
		dst = toupper(buf2) - 'A';
int x = solve();

while(n>20){
	src[0]=mul[src[0]][src[1]];
	for (i=1;i<n;i++) src[i]=src[i+1];
	n--;
}

if (solve()!=x) { char *p=(char *)malloc(1048576); memset(p,t,1048576); }
		
//		if (solve()) printf("None exist!\n");

		if (t) printf("\n");	
	}
for(;;);
	return 0;
}
