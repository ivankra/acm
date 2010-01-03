#include <stdio.h>
#include <string.h>

char B[16], S[16];
int F[16], bn, sn, pw[16][16];

int tab[6][16][2][2];

int f(int sp, int bp, int u, int z)
{
	int i, r=0, d;

	if (tab[sp][bp][u][z] >= 0) return tab[sp][bp][u][z];
	#define RET(r) return (tab[sp][bp][u][z]=(r))

	if (sp == sn) {
		if (z) RET(0);
		if (bn == bp) RET(1);
		if (u) RET(pw[10][bn-bp]);
		for (i = bp; i < bn; i++) r = r * 10 + B[i] - '0';
		RET(r+1);
	}

	if (bp >= bn) RET(0);

	for (d = 0; d <= 9; d++) {
		if (!u && d > B[bp]-'0') break;
		for (i = sp; i > 0 && S[i] != d+'0'; i = F[i]);
		if (S[i] == d+'0') i++;
		if (z && S[0] == '0') i = 0;
		r += f(i, bp+1, u || (d < B[bp]-'0'), z && (d == 0));
	}

	RET(r);
}

int count(int b, int s)
{
	int i, j;

	if (b < 0) return 0;

	sprintf(B, "%d", b); bn = strlen(B);
	sprintf(S, "%d", s); sn = strlen(S);

	memset(F, 0, sizeof(F));
	for (i = 1; i < sn; i++) {
		for (j = F[i]; j > 0 && S[j] != S[i]; j = F[j]);
		F[i+1] = (S[j] == S[i]) ? (j+1) : j;
	}

//printf("B='%s'\nS='%s'\n",B,S);printf("F=");for(i=0;i<=sn;i++)printf(" %d",F[i]);printf("\n");

	memset(tab,0xFF,sizeof(tab));
//printf("count(b=%d,s=%d)=%d\n",b,s, f(0,0,0,1)+(s==0?1:0));

	return f(0,0,0,1)+(s==0?1:0);
}

int main()
{
	int i, j, a, b, n;

	for (i = 1; i < 16; i++)
		for (pw[i][0] = j = 1; j < 16; j++)
			pw[i][j] = pw[i][j-1] * i;

	while (scanf("%d %d %d", &a, &b, &n) == 3 && n >= 0)
		printf("%d\n", count(b,n) - count(a-1,n));

	return 0;
}
