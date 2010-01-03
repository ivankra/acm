#include <cstdio>
#include <cstring>

int A[1030][1030];

int main() {
	int T, d, n, x1, y1, z1;
	scanf("%d", &T);
	while (T-- > 0 && scanf("%d %d", &d, &n) == 2) {
		memset(A, 0, sizeof(A));
		while (n-- > 0 && scanf("%d %d %d", &x1, &y1, &z1) == 3)
			A[y1+1][x1+1] = z1;

		for (int y = 1; y <= 1025; y++) {
			for (int x = 1, s = 0; x <= 1025; x++) {
				s += A[y][x];
				A[y][x] = A[y-1][x] + s;
			}
		}

		x1 = y1 = 1; z1 = 0;
		int D = 2*d+1;

		for (int x = d+1; x <= 1025; x++) {
			for (int y = d+1; y <= 1025; y++) {
				int t = A[y][x];
				if (y >= D) t -= A[y-D][x];
				if (x >= D) t -= A[y][x-D];
				if (x >= D && y >= D) t += A[y-D][x-D];

				if (t > z1) { x1=x-d; y1=y-d; z1=t; }
			}
		}

		printf("%d %d %d\n", x1-1, y1-1, z1);
	}
}
