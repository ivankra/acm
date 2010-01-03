#include <stdio.h>
#include <string.h>

int main()
{
	char buf[256], a[256], b[256];
	int s[32][32], w[32][32];
	int i, j, n, m, t, T;

	while (gets(buf) && sscanf(buf, "%d", &T) != 1);

	for (t = 1; t <= T; t++) {
		gets(buf); a[0]=0; sscanf(buf," %[A-Z]",a); n=strlen(a);
		gets(buf); b[0]=0; sscanf(buf," %[A-Z]",b); m=strlen(b);

		for (i = 0; i <= m; i++) { s[n][i]=m-i; w[n][i]=1; }
		for (i = 0; i <= n; i++) { s[i][m]=n-i; w[i][m]=1; }

		for (i = n-1; i >= 0; i--) {
			for (j = m-1; j >= 0; j--) {
				if (a[i]==b[j]) {
					s[i][j] = 1 + s[i+1][j+1];
					w[i][j] = w[i+1][j+1];
				} else if (s[i+1][j] == s[i][j+1]) {
					s[i][j] = 1 + s[i+1][j];
					w[i][j] = w[i+1][j] + w[i][j+1];
				} else {
					s[i][j] = 1 + (s[i+1][j] <? s[i][j+1]);
					w[i][j] = s[i+1][j]<s[i][j+1] ? w[i+1][j] : w[i][j+1];
				}
			}
		}

		printf("Case #%d: %d %d\n", t, s[0][0], w[0][0]);
	}

	return 0;
}
