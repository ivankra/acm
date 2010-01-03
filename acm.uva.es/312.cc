#include <cstdio>
#include <cstring>

int a[128][128], m, n;
char out[128][128];

void dfs(int r, int c) {
	if (r < 0 || r < 0 || r > m+1 || c > n+1) return;

	if (a[r][c] != 1) return;

	a[r][c] = -1;
	dfs(r-1, c);
	dfs(r+1, c);
	dfs(r, c-1);
	dfs(r, c+1);
}


int main() {
	while (scanf("%d %d", &m, &n) == 2) {
		if (m==0 && n==0) break;

		for (int i = 0; i <= m+1; i++)
		for (int j = 0; j <= n+1; j++)
			a[i][j] = 1;

		for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
		dfs(0,0);

		int K = 0;

		memset(out, ' ', sizeof(out));
		for (int r = 1; r <= m; r++)
		for (int c = 1; c <= n; c++) {
			if (a[r][c] == 1) {
				for (int i = 0; i < 4; i++)
				for (int j = 0; j < 6; j++)
					out[3*r+i-3][5*c+j-5] = '+';
				continue;
			}
			if (a[r][c] != 0) continue;

			for (int i = 0; i < 4; i++)
				out[3*r+i-3][5*c-5] = out[3*r+i-3][5*c+5-5] = '+';
			for (int j = 0; j < 6; j++)
				out[3*r-3][5*c+j-5] = out[3*r+3-3][5*c+j-5] = '+';

			if ((a[r-1][c] != 0 && a[r+1][c] == 0) ||
			    (a[r][c-1] != 0 && a[r][c+1] == 0)) {
				char s[10];
				sprintf(s, "%.3d", ++K);
				for (int i = 0; i < 3; i++)
					out[3*r+1-3][5*c+1+i-5] = s[i];
			}
		}

		for (int i = 0; i < 3*m+1; i++) {
			for (int j = 127; j >= 0 && out[i][j]==' '; j--)
				out[i][j] = 0;
			printf("%s\n", out[i]);
		}

		printf("\n");
	}
}
