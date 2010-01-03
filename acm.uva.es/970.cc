#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int res[3][3]={{1,0,2},{0,1,1},{2,1,0}}, sres[1<<3][1<<3];
int memo[128][128];

int main() {
	for (int a = 0; a < (1 << 3); a++) {
		for (int b = 0; b < (1 << 3); b++) {
			sres[a][b] = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if ((a & (1 << i)) != 0 && (b & (1 << j)) != 0)
						sres[a][b] |= 1 << res[i][j];
		}
	}

	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		char str[128];
		scanf(" %s", str);

		int N = strlen(str);
		for (int i = 0; i < N; i++)
			memo[1][i] = 1 << (str[i]-'X');

		for (int m = 2; m <= N; m++) {
			for (int s = 0; s+m <= N; s++) {
				memo[m][s] = 0;
				for (int k = 1; k < m; k++) {
					if ((memo[m][s] |= sres[memo[k][s]][memo[m-k][s+k]]) == 7) break;
				}
			}
		}

		int i = 2;
		while (i > 0 && (memo[N][0] & (1 << i)) == 0) i--;
		printf("%c\n", i+'X');
	}
}
