#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int mul[4][4] = {
	{ 1, 1, 0,  0 },
	{ 2, 1, 0,  0 },
	{ 0, 2, 2,  0 },
	{0,0,0,0}
};	

int src[128], dst, n;
int can[128][128][4], first[128][128][4];
int seg[128], segchr[128];

void join(int len, int offs, int d)
{
	int m, c1, c2, i;
	int bm=0, bc1=0, bc2=0, b=0;

	if (len < 2) return;

	for (m = 1; m < len; m++) {
		for(c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
			if (mul[c1][c2]!=d || !can[m][offs][c1] || !can[len-m][offs+m][c2])
				continue;

			if (b == 0) { bm=m; bc1=c1; bc2=c2; b=1; continue; }

			if (first[m][offs][c1] < first[bm][offs][bc1] ||
			    (first[m][offs][c1] == first[bm][offs][bc1] &&
			     first[len-m][offs+m][c2] < first[len-bm][offs+bm][bc2]) ||
			    (first[m][offs][c1] == first[bm][offs][bc1] &&
			     first[len-m][offs+m][c2] == first[len-bm][offs+bm][bc2] &&
			     m < bm)) {
				bm=m; bc1=c1; bc2=c2; b=1;
				continue;
			}
		}
	}

	c1 = bc1; c2 = bc2; m = bm;

	join(m, offs, c1);
	join(len-m, offs+m, c2);

	for (i = offs+1; i < offs+len; i++)
		seg[i] = seg[offs];
	segchr[seg[offs]] = mul[c1][c2];

	for (i = 0; i < n; i++) {
		if (i > 0 && seg[i-1] == seg[i]) continue;
		putchar(segchr[i]+'a');
	}
	putchar('\n');
}

int solve()
{
	int i, k, m, c1, c2;

	if (n <= 0 || dst < 0 || dst > 2) return 1;

	for (i = 0; i < n; i++) {
		can[1][i][0] = can[1][i][1] = can[1][i][2] = 0;
		can[1][i][src[i]] = 1;
		first[1][i][src[i]] = i;
	}

	for (k = 2; k <= n; k++) {
		for (i = 0; i <= n-k; i++) {
			can[k][i][0]=can[k][i][1]=can[k][i][2] = 0;
			for (m = 1; m < k; m++) {
				for (c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
					if ((can[m][i][c1] & can[k-m][i+m][c2]) == 0) continue;
					int d = mul[c1][c2];
					int t;

					if (m == 1 && k-m > 1)
						t = first[k-m][i+m][c2];
					else if (m > 1)
						t = first[m][i][c1];
					else
						t = i;

					if (can[k][i][d] == 0) {
						can[k][i][d] = 1;
						first[k][i][d] = t;
					} else {
						first[k][i][d] <?= t;
					}
				}
			}
		}
	}

	if (!can[n][0][dst]) return 1;

	for (i = 0; i < n; i++) {
		seg[i] = i;
		segchr[i] = src[i];
	}

	for (i = 0; i < n; i++) putchar(src[i]+'a'); putchar('\n');
	join(n, 0, dst);

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

		gets(buf);
		buf2 = 0;
		sscanf(buf, " %c", &buf2);
		dst = toupper(buf2) - 'A';

		if (solve()) printf("None exist!\n");

		if (t) printf("\n");	
	}

	return 0;
}
