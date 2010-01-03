#include <cstdio>
#include <cstring>

int main()
{
	char dig[10][256], s[512];
	for (int i = 0; i < 10; i++) scanf(" %s", dig[i]);
	scanf(" %s", s);

	int mi[512]={0}, ma[512]={0}, n=strlen(s), dn[10];
	for (int i = 0; i < 10; i++) dn[i] = strlen(dig[i]);

	for (int k = 1; k <= n; k++) {
		mi[k]=1<<20; ma[k]=-(1<<20);
		for (int d = 0; d < 10; d++) {
			if (dn[d]<=k && memcmp(s+k-dn[d], dig[d], dn[d])==0) {
				mi[k] <?= d + mi[k-dn[d]];
				ma[k] >?= d + ma[k-dn[d]];
			}
		}
	}
	printf("%d %d", mi[n], ma[n]);
}
