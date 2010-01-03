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
int can[128][128][4], how[128][128][4], first[128][128][4];
int seg[128], segchr[128];

void join(int len, int offs, int d)
{
	int m = how[len][offs][d], c1, c2, i;

	if (len < 2) return;

	for(c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
		if (mul[c1][c2]!=d || !can[m][offs][c1] || !can[len-m][offs+m][c2])
			continue;

		goto ok;
	}
	assert(0==1);
	return;

ok:	join(m, offs, c1);
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
	}

	for (k = 2; k <= n; k++) {
		for (i = 0; i <= n-k; i++) {
			can[k][i][0]=can[k][i][1]=can[k][i][2] = 0;
			for (m = 1; m < k; m++) {
				for (c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
					if ((can[m][i][c1] & can[k-m][i+m][c2]) == 0) continue;
					int d = mul[c1][c2];
					if (can[k][i][d] == 0) {
						can[k][i][d] = 1;
						how[k][i][d] = m;
					} else {
						how[k][i][d] >?= m;
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
