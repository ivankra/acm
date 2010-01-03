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
int can[128][128][4];

int nseg;
struct { int offs, len, c; } seg[128];

int join(int s)
{
	int s1k = seg[s].offs, s1o = 0;
	int s2k = n-seg[s].offs-seg[s].len-seg[s+1].len, s2o=seg[s].offs+seg[s].len+seg[s+1].len;

	int c1, c2;
	int d = mul[seg[s].c][seg[s+1].c];

printf("join(s=%d): d=%d\n", s,d);
	if (s1k > 0 && s2k > 0) {
		for(c1=0;c1<3;c1++) for(c2=0;c2<3;c2++) {
			if (!can[s1k][s1o][c1] || !can[s2k][s2o][c2]) continue;

			if (mul[mul[c1][d]][c2] == dst ||
			    mul[c1][mul[d][c2]] == dst)
			    	return 1;
		}
	} else if (s2k > 0) {
		for(c2=0;c2<3;c2++)
			if (can[s2k][s2o][c2] && mul[d][c2] == dst) return 1;
	} else if (s1k > 0) {
		for(c1=0;c1<3;c1++)
			if (can[s1k][s1o][c1] && mul[c1][d] == dst) return 1;
	} else {
		return d==dst;
	}

	return 0;
}

int solve()
{
	int i, j, k, m, c1, c2, c3;

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
					can[k][i][d] |= 1;
printf("can[k=%d][i=%d][c=%d]: m=%d c1=%d c2=%d\n",k,i,d,m,c1,c2);
				}
			}
		}
	}

	if (!can[n][0][dst]) return 1;

	nseg = n;
	for (i = 0; i < n; i++) {
		seg[i].offs = i;
		seg[i].len = 1;
		seg[i].c = src[i];
	}

	for (;;) {
		for (i = 0; i < nseg; i++) putchar(seg[i].c+'a');
		putchar('\n');
		if (nseg < 2) break;

		for (i = 0; i < nseg-1; i++)
			if (join(i)) break;

		assert(i < nseg-1);

		seg[i].len += seg[i+1].len;
		seg[i].c = mul[seg[i].c][seg[i+1].c];
		for (i++; i < nseg-1; i++)
			seg[i] = seg[i+1];
		nseg--;
	}

	return 0;
}

int main()
{
	static char buf[1024], buf2;
	int t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %s %c", buf, &buf2) == 2;) {
		dst = toupper(buf2) - 'A';
		for (n = 0; buf[n]; n++)
			src[n] = toupper(buf[n]) - 'A';

		if (solve()) printf("None exist!\n");

		if (t) printf("\n");	
	}

	return 0;
}
