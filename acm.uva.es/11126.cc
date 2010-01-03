#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int pile[8][32], mult[8], base[8];
bool adj[16][16];

short seen[13][17][6][6][6][6][6][6][6], counter;

bool dfs(int last, int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
	short &mem = seen[last][a0][a1][a2][a3][a4][a5][a6][a7];
	if (mem == counter) return false;
	mem = counter;

	if ((a0|a1|a2|a3|a4|a5|a6|a7) == 0) return true;

	if (a0 > 0 && dfs(pile[0][a0-1], a0-1, a1, a2, a3, a4, a5, a6, a7)) return true;
	if (a1 > 0 && adj[pile[1][a1-1]][last] && dfs(pile[1][a1-1], a0, a1-1, a2, a3, a4, a5, a6, a7)) return true;
	if (a2 > 0 && adj[pile[2][a2-1]][last] && dfs(pile[2][a2-1], a0, a1, a2-1, a3, a4, a5, a6, a7)) return true;
	if (a3 > 0 && adj[pile[3][a3-1]][last] && dfs(pile[3][a3-1], a0, a1, a2, a3-1, a4, a5, a6, a7)) return true;
	if (a4 > 0 && adj[pile[4][a4-1]][last] && dfs(pile[4][a4-1], a0, a1, a2, a3, a4-1, a5, a6, a7)) return true;
	if (a5 > 0 && adj[pile[5][a5-1]][last] && dfs(pile[5][a5-1], a0, a1, a2, a3, a4, a5-1, a6, a7)) return true;
	if (a6 > 0 && adj[pile[6][a6-1]][last] && dfs(pile[6][a6-1], a0, a1, a2, a3, a4, a5, a6-1, a7)) return true;
	if (a7 > 0 && adj[pile[7][a7-1]][last] && dfs(pile[7][a7-1], a0, a1, a2, a3, a4, a5, a6, a7-1)) return true;
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);

	memset(seen, 0, sizeof(seen));
	counter = 0;

	for (int i = 0; i < 8; i++) {
		base[i] = (i == 0 ? 17 : 6);
		mult[i] = (i > 0 ? mult[i-1]*base[i-1] : 1);
	}

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			adj[i][j] = (abs(i-j) == 1 || (i==0 && j==12) || (i==12 && j==0));

	for (int cs = 1; cs <= T; cs++) {
		for (int j = 0; j < 5; j++) {
			for (int i = 1; i <= 7; i++) {
				scanf("%d", &pile[i][j]);
				pile[i][j]--;
			}
		}

		for (int i = 0; i < 17; i++) {
			scanf("%d", &pile[0][i]);
			pile[0][i]--;
		}

		counter++;

		bool res = dfs(pile[0][16], 16, 5, 5, 5, 5, 5, 5, 5);
		printf("Case #%d: %s\n", cs, res ? "Yes" : "No");
	}

}
