#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

int a[32][32][32], x, y, z, w;
int N;

bool move(int x1, int y1, int z1) {
	x1 = (x1 + N) % N;
	y1 = (y1 + N) % N;
	z1 = (z1 + N) % N;
	if (a[x1][y1][z1] == 0) {
		x = x1; y = y1; z = z1;
		a[x][y][z] = w++;
		return true;
	} else {
		return false;
	}
}

int main()
{
	int first = 1;
	while (scanf("%d", &N) == 1 && N > 0) {
		assert(N % 2 == 1 && N <= 30);
		memset(a, 0, sizeof(a));

		x = N-1; y = N/2; z = N/2; w = 1;
		a[x][y][z] = w++;
		while (w <= N*N*N) {
			if (!move(x+1, y, z+1)) { //down right
				if (!move(x+1, y-1, z)) { // back down
					if (!move(x-1, y, z)) {
						abort();
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			if (!first) printf("\n");
			first = 0;
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++)
					printf(k==0 ? "%5d" : " %5d", a[i][j][k]);
				printf("\n");
			}
		}
	}
}
