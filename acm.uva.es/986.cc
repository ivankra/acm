#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int f[42][22][22][2], N, C, H;

int main()
{
	while (scanf("%d %d %d", &N, &C, &H) == 3) {
		memset(f, 0, sizeof(f));
		f[0][0][0][0] = 1;
		for (int x = 0; x < 2*N; x++) {
			for (int y = 0; y <= N; y++) {
				for (int k = 0; k <= C; k++) {
					for (int d = 0; d < 2; d++) {
						f[x+1][y+1][k][0] += f[x][y][k][d];
						if (y != 0) {
							int k1 = (y == H && d == 0) ? (k+1) : k;
							f[x+1][y-1][k1][1] += f[x][y][k][d];
						}
					}
				}
			}
		}
		printf("%d\n", f[2*N][0][C][1]);
	}
}
