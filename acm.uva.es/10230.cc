#include <cstdio>
#include <cstring>

char out[1040][1040];

void doit(int r0, int c0, int n, int xr, int xc) {
	if (n <= 0) return;

	int h = 1 << (n - 1);
	if (n > 1) {
		for (int z = 0; z < 4; z++)
			if (((z&1) ^ (xr < r0+h)) && (((z&2)==2) ^ (xc < c0+h)))
				doit(r0+(z&1?h:0), c0+(z&2?h:0), n-1, xr, xc);
			else
				doit(r0+(z&1?h:0), c0+(z&2?h:0), n-1, r0+h-(z&1?0:1), c0+h-(z&2?0:1));
	}

	int u = 0;
	for (int i = -2; i < 2; i++) {
		for (int j = -2; j < 2; j++) {
			int c = out[r0+h+i][c0+h+j];
			if ('a' <= c && c <= 'z') u |= 1 << (c - 'a');
		}
	}

	for (int i = 0;; i++)
		if ((u & (1 << i)) == 0) { u = 'a' + i; break; }

	for (int z = 0; z < 4; z++) {
		if (((z & 1) ^ (xr < r0+h)) && (((z&2)==2) ^ (xc < c0+h))) continue;
		out[r0+h-(z&1?0:1)][c0+h-(z&2?0:1)] = u;
	}
}

int main() {
	int n, xr, xc;
	while (scanf("%d %d %d", &n, &xc, &xr) == 3) {
		memset(out, '*', sizeof(out));
		doit(1, 1, n, xr, xc);
		for (int i = 1; i <= 1<<n; i++) {
			fwrite(&out[i][1], 1, 1<<n, stdout);
			printf("\n");
		}
		printf("\n");
	}
}
