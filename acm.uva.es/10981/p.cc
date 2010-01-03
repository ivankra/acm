#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int mul[4][4]={{1,1,0,0},{2,1,0,0},{0,2,2,0},{0,0,0,0}};	

int src[128], dst, n;
char srcstr[128];
unsigned char tab[128][128], comb[8][8];

int first()
{
	static int a[16][16], f[16][16][4];
	int i, j, k, c1, c2, offs, len;

	assert(3 <= n && n < 16);

	for (i = 0; i < n; i++) a[i][1] = 1 << src[i];

	f[0][n][dst] = -1;	
	for(offs=n-1;offs>=0;offs--) for(len=2;offs+len<=n;len++) {
		a[offs][len] = 0;
		for(k=1;k<len;k++) for(c1=0;c1<3;c1++) {
			if ((a[offs][k] & (1 << c1)) == 0) continue;
			for (c2 = 0; c2 < 3; c2++) {
				if ((a[offs+k][len-k] & (1<<c2)) == 0) continue;

				if (k > 1) i = f[offs][k][c1];
				else if (len-k > 1) i = f[offs+k][len-k][c2];
				else i = offs;

				j = mul[c1][c2];

				if ((a[offs][len] & (1 << j)) == 0 ||
				    i < f[offs][len][j]) {
					a[offs][len] |= 1 << j;
					f[offs][len][j] = i;
				}
			}
		}
	}

	return f[0][n][dst];
}

void prep()
{
	memset(comb, 0, sizeof(comb));
	for (int a = 0; a < 8; a++) 
		for (int b = 0; b < 8; b++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (((a>>i)&1)==1 && ((b>>j)&1)==1)
						comb[a][b] |= 1 << mul[i][j];
}

int solve()
{
	static int cum[128];
	int i, j, k, offs, len;

again:
	assert(n > 0);

	if (n == 1) {
		if (src[0] != dst) return 1;
		printf("%c\n", src[0]+'a');
		return 0;
	}
	
	cum[0] = src[0];
	for (i = 1; i < n; i++)
		cum[i] = mul[cum[i-1]][src[i]];

/*printf("src: %s  dst=%c\n", srcstr, dst+'a');
printf("cum: ");for(i=0;i<n;i++)printf("%c",cum[i]+'a');printf("\n");*/
	if (cum[n-1] == dst) { offs=n; goto l1; }

	for (offs = n-1; offs >= 0; offs--) {
		tab[offs][1] = 1 << src[offs];
		for (len = 2; offs+len <= n; len++) {
			tab[offs][len] = 0;
			for (k = 1; k < len; k++)
				tab[offs][len] |= comb[tab[offs][k]]
						      [tab[offs+k][len-k]];
		}
		i = tab[offs][n-offs];
		if (offs == 0 && (i & (1<<dst))) break;
		if (offs >= 2 && (comb[1<<cum[offs-1]][i] & (1<<dst))) break;
	}

	if (offs < 0)
		return 1;

l1:
	/*printf("offs=%d n=%d\n",offs,n);*/

	if (offs > 0) {
		for (i = 0; i < offs-1; i++)
			printf("%c%s\n", cum[i]+'a', srcstr+i+1);
		src[0] = cum[offs-1];
		for (i = 1, j = offs; j < n;)
			src[i++] = src[j++];
		n = i;
		for (i = 0; i < n; i++) srcstr[i] = src[i]+'a';
		srcstr[n] = 0;
	}

	if (n <= 1) goto again;

	if (n == 2) {
		printf("%s\n%c\n", srcstr, dst);
		return 0;
	}

	printf("%s\n", srcstr);

	i = first();
	assert(0 <= i && i <= n-2);

	src[i] = mul[src[i]][src[i+1]];
	n--;	
	for (j = i+1; j < n; j++) src[j] = src[j+1];
	for (j = i; j < n; j++) srcstr[j] = src[j]+'a';
	srcstr[n] = 0;

	goto again;
}

int main()
{
	static char buf[4096], chr;
	int i, t=0;

	prep();

	for (scanf("%d", &t); t-- > 0;) {
		i = scanf(" %s %c", buf, &chr);
		assert(i == 2 && 'a' <= chr && chr <= 'c');

		for (n = 0; buf[n]; n++) {
			assert('a' <= buf[n] && buf[n] <= 'c');
			src[n] = buf[n] - 'a';
			srcstr[n] = buf[n];
		}
		srcstr[n] = 0;
		dst = chr - 'a';

		if (solve()) printf("None exist!\n");

		if (t) printf("\n");	
	}

	return 0;
}
