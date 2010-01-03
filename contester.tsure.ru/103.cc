#include <cstdio>
#include <cstring>

int y0, x0, n, a[512][512], no[512*512/3+10];

int f() {
	int m=((1<<(2*n))-1)/3;
	for (int i = 0; i <= m; i++) no[i] = 0;

	for (int y = 0; y < (1<<n); y++)
	for (int x = 0; x < (1<<n); x++) {
		if (a[y][x] < 0 || a[y][x] > m) return 1;
		if (a[y][x] == 0 && (y != y0-1 || x != x0-1)) return 2;
		no[a[y][x]]++;
	}

	if (no[0] != 1) return 3;
	for (int i = 1; i <= m; i++)
		if (no[i] != 3) return 4;

	for (int i = 0; i <= m; i++) no[i] = 0;
	for (int y = 0; y < (1<<n); y++)
	for (int x = 0; x < (1<<n); x++) {
		if (a[y][x] == 0) continue;
		int c = a[y][x];
		int L = (x > 0 && a[y][x-1] == c);
		int R = (x+1 < (1<<n) && a[y][x+1] == c);
		int U = (y > 0 && a[y-1][x] == c);
		int D = (y+1 < (1<<n) && a[y+1][x] == c);
		no[c] |= (L|R)&(U|D);
	}

	for (int i = 1; i <= m; i++)
		if (!no[i]) return 5;
	return 0;	
}

int main()
{
	scanf("%d %d %d", &n, &y0, &x0);
	for (int i = 0; i < (1<<n); i++)
	for (int j = 0; j < (1<<n); j++)
		scanf("%d", &a[i][j]);
	printf(f()?"Wrong Answer\n":"Accepted\n");
}
