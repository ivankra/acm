#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <set>
using namespace std;

int N, M, B[128][128];
char A[128][128];

bool canPlace(int y, int x, char c) {
	return A[y][x] == '?' && A[y-1][x] != c && A[y+1][x] != c && A[y][x-1] != c && A[y][x+1] != c;
}

void go(int y, int x) {
	int ch;
	for (ch = 'A'; !canPlace(y, x, ch); ch++);

	for (int k = 1;; k++) {
		for (int i = 0; i < k; i++) {
			A[y+i][x+k-1] = ch;
			A[y+k-1][x+i] = ch;
		}
	
		if (k >= B[y][x]) return;
		for (int i = 0; i <= k; i++) {
			if (A[y+i][x+k] != '?') return;
			if (A[y+i-1][x+k] == ch) return;
			if (A[y+i][x+k+1] == ch) return;
			if (A[y+i+1][x+k] == ch) return;

			if (A[y+k][x+i] != '?') return;
			if (A[y+k][x+i-1] == ch) return;
			if (A[y+k+1][x+i] == ch) return;
			if (A[y+k][x+i+1] == ch) return;
		}

		for (int ch1 = 'A'; ch1 < ch; ch1++)
			if (canPlace(y, x+k, ch1)) return;
	}
}

int main()
{
	for (int cs = 1; scanf("%d %d", &N, &M) == 2; cs++) {
		if (N == 0 || M == 0) break;
		if (cs > 1) printf("\n");

		memset(A, '.', sizeof(A));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf(" %c", &A[i][j]);

		memset(B, 0, sizeof(B));
		for (int i = N; i >= 1; i--) {
			for (int j = M; j >= 1; j--) {
				if (A[i][j] == '?')
					B[i][j] = min(B[i+1][j], min(B[i][j+1], B[i+1][j+1])) + 1;
				else
					B[i][j] = 0;	
			}
		}

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= M; x++) {
				if (A[y][x] == '?') go(y, x);
				printf("%c", A[y][x]);
			}
			printf("\n");
		}
	}
}
