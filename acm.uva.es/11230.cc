#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

enum { MAX = 128 };
int n, m, r, c;
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int sum(int y1, int x1, int y2, int x2)
{
	return C[y2][x2] - C[y1-1][x2] - C[y2][x1-1] + C[y1-1][x1-1];
}

int main() {
	while (scanf("%d %d %d %d", &n, &m, &r, &c) == 4 && n > 0) {
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(C, 0, sizeof(C));

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int ch;
				do { ch = getchar(); } while (ch != '0' && ch != '1');
				A[i][j] = ch - '0';
			}
		}

		int res = 0;
		for (int i = 1; i <= n; i++) {
			int s = 0;
			for (int j = 1; j <= m; j++) {
				C[i][j] = C[i-1][j] + s;
				if (sum(max(1, i-r+1), max(1, j-c+1), i, j) % 2 != A[i][j]) {
					if (i+r-1 > n || j+c-1 > m) goto no;
					B[i][j] = 1;
					res++;
				} else {
					B[i][j] = 0;
				}
				s += B[i][j];
				C[i][j] = C[i-1][j] + s;
			}
		}

		printf("%d\n", res);
		continue;
no:
		printf("-1\n");
	}
}
