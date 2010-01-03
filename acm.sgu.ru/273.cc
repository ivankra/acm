#include <stdio.h>
#include <string.h>

int tab[256][256], out[16][16], len;

void take()
{
	int map[256], m[4], a, b, i, j, k;
	char s[1024];

	memset(map, 0, sizeof(map));
	memset(out, 0, sizeof(out));
	memset(tab, 0, sizeof(tab));

	map['b'] = 1; map['r'] = 2; map['y'] = 4; map['w'] = 8;

	for (k = 0; k < 4; k++)
		scanf("%d", &m[k]);

	for (k = 0; k < 4; k++) {
		while (m[k]-- > 0) {
			for (a = 0; (a = getchar()) != EOF && map[a] == 0;);
			for (b = 0; (b = getchar()) != EOF && map[b] == 0;);
			a = map[a]; b = map[b];
			for(i=0;i<16;i++) for(j=0;j<16;j++)
				if ((i & a) && (j & b)) out[i][j] |= 1 << k;
		}
	}

	scanf(" %s", s);
	for (i = len = 0; s[i]; i++)
		if ((j = map[s[i]]) != 0) tab[1][len++] = j;
}

int main()
{
	int i, j, k;

	take();

	for (k = 2; k <= len; k++)
		for (i = 0; (i + k) <= len; i++)
			for (j = 1; j < k; j++)
				tab[k][i] |= out[tab[j][i]][tab[k-j][i+j]];

	for (i = j = 0; i < 4; i++)
		if ((tab[len][0] >> i) & 1) j++, putchar("bryw"[i]);
	printf(j ? "\n" : "Nobody\n");

	return 0;
}
