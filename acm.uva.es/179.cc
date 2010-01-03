#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

char plain[256], ciph1[256], ciph2[256], decr[256];
int n, k, G[128][128], ymatch[128], pi[128], seen[128];

int aug(int x) {
	if (seen[x]++) return 0;
	for (int y = 0; y < k; y++)
		if (G[x][y] && ymatch[y] < 0 || aug(ymatch[y])) {
			pi[x] = y;
			ymatch[y] = x;
			return 1;
		}
	return 0;
}

int check() {
	for (int i = 0; i < k; i++) for (int j = 0; j < k; j++) G[i][j] = 1;

	for (int i = 0; i < n; i += k)
	for (int j = 0; j < k; j++)
	for (int t = 0; t < k; t++)
		if (plain[i+j] && ciph1[i+t] && plain[i+j] != ciph1[i+t])
			G[j][t] = 0;

	memset(ymatch, 0xff, sizeof(ymatch));
	for (int i = 0; i < k; i++) {
		memset(seen, 0, sizeof(seen));
		if (!aug(i)) return 0;
	}

	int m = strlen(ciph2);
	for (int i = m; i < 256; i++) ciph2[i] = '?';

	memset(decr, 0, sizeof(decr));
	for (int i = 0; i < m; i += k)
		for (int j = 0; j < k; j++)
			decr[i+j] = ciph2[i+pi[j]];

	return 1;
}

int main()
{
	while (gets(plain) && gets(ciph1) && gets(ciph2)) {
		if (strcmp(plain, "#") == 0) break;
		n = strlen(plain); assert(n <= 80 && n == strlen(ciph1));

		for (int i = n; i < 256; i++)
			plain[i] = ciph1[i] = 0;

		for (k = 1; k <= n && !check(); k++);
		printf("%s\n", k<=n?decr:ciph2);
	}
}
