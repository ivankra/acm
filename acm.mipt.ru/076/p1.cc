#include <cstdio>
#include <cstring>

#define INF 0x3fffffff

char s[1024];
int f[1024][1024], n;

int main() {
	scanf(" %s", s);

	n = strlen(s);
	if (n % 2 != 0) { printf("NO\n"); return 0; }

	memset(f, 0, sizeof(f));

	for (int m = 2; m <= n; m += 2) {
		for (int st = 0; st+m <= n; st++) {
			char a = s[st], b = s[st+m-1];
			int &res = f[m][st];
			res = 2 + f[m-2][st+1];
			if (a == '(' && b == ')') res <?= f[m-2][st+1];
			if (a == '(' || b == ')') res <?= 1 + f[m-2][st+1];

			for (int k = 2; k < m; k += 2)
				res <?= f[k][st] + f[m-k][st+k];
		}
	}

	printf("%d\n", f[n][0]);
}
