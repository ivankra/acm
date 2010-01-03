#include <cstdio>
#include <cstring>

char W[1024], R[1024];
int f[1024][1024];

int main() {
	scanf(" %s %s", W, R);
	int n = strlen(W), m = strlen(R);

	memset(f, 0, sizeof(f));
	f[0][0] = 1;

	for (int j = 1; j <= m; j++) {
		if (R[j-1] == '*') {
			f[0][j] = f[0][j-1];
			for (int i = 1; i <= n; i++)
				f[i][j] = f[i-1][j] + f[i][j-1];
		} else {
			for (int i = 1; i <= n; i++)
				f[i][j] = (W[i-1] == R[j-1]) ? f[i-1][j-1] : 0;
		}
	}

	printf("%d\n", f[n][m]);
}
