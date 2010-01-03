#include <cstdio>
#include <cstring>

int a[128][128], n;

int dfs(int x, int y, int c) {
	if (x <= 0 || y <= 0 || x > n || y > n || a[x][y] != c) return 0;
	a[x][y] = -1;
	return 1 + dfs(x-1, y, c) + dfs(x+1, y, c) + dfs(x, y-1, c) + dfs(x, y+1, c);
}

int main() {
	char buf[65536];
	while (gets(buf)) {
		if (sscanf(buf, "%d", &n) != 1) continue;
		if (n == 0) break;

		bool ok = true;

		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n-1; i++) {
			gets(buf);
			for (char *p = buf; ok;) {
				int x, y, d;
				if (sscanf(p, " %d %d %n", &x, &y, &d) < 2) break;
				p += d;

				if (x < 1 || y < 1 || x > n || y > n || (a[x][y] > 0 && a[x][y] != i)) {
					ok = false;
					continue;
				}

				a[x][y] = i;
			}
		}

		for (int i = 1; i <= n && ok; i++) {
			for (int j = 1; j <= n && ok; j++) {
				if (a[i][j] != -1) {
					int c = a[i][j];
					ok &= dfs(i,j,c)==n;
				}
			}
		}
		printf(ok ? "good\n" : "wrong\n");
	}
}
