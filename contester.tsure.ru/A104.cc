#include <cstdio>
#include <cstring>
#include <cctype>

char *R[]={"X","I","II","III","IV","V","VI","VII","VIII","IX"}, s[256];
int Rn[10], sr[32][10], sn;

int memo[21][21][256];
int doit(int a, int b, int balance) {
	if (a > b) return 0;

	int &ret = memo[a][b][balance+128];
	if (ret != -1) return ret;
	if (a == b) return ret = (balance == 0) ? 1 : 0;

	ret = 0;
	for (int d = 0; d < 10; d++) {
		if (!sr[a][d] || a+Rn[d] > b) continue;
		for (int e = 0; e < 10; e++) {
			if (a+Rn[d] > b-Rn[e] || !sr[b-Rn[e]][e]) continue;
			ret += doit(a+Rn[d], b-Rn[e], balance+d-e);
		}
	}
	return ret;
}

int main()
{
	for (int i = 0; i < 10; i++) Rn[i] = strlen(R[i]);
	while (scanf(" %s", s) == 1) {
		sn = strlen(s);
		for (int i = 0; i < sn; i++)
			s[i] = toupper(s[i]);
		for (int i = 0; i < sn; i++)
		for (int d = 0; d < 10; d++)
			sr[i][d] = (i+Rn[d]<=sn && memcmp(s+i,R[d],Rn[d])==0);
		memset(memo, 0xff, sizeof(memo));
		printf("%d\n", doit(0, sn, 0));
	}
}
