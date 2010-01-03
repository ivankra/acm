#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[1024], y[1024], z[1024];
int f[1024][1024];

int main() {
	scanf(" %s %s", x, y);
	int n = strlen(x), m = strlen(y);

	memset(f, 0, sizeof(f));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (x[i-1] == y[j-1])
				f[i][j] = f[i-1][j-1] + 1;
			else
				f[i][j] = max(f[i-1][j], f[i][j-1]);
		}
	}

	int i = n, j = m, k = f[n][m];
	z[k--] = 0;
	while (i > 0 && j > 0) {
		if (x[i-1] == y[j-1]) {
			z[k--] = x[i-1]; i--; j--;
		} else if (f[i-1][j] >= f[i][j-1]) {
			i--;
		} else {
			j--;
		}
	}

	printf("%s\n", f[n][m] ? z : "Empty");
}
