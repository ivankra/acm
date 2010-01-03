// DP
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

char word[20000];
int kid[20000][3], mini[20000][3], maxi[20000][3], got[20000][3], test_id;

void rec(int x, int c)
{
	if (got[x][c] == test_id) return;
	got[x][c] = test_id;
	for (int i = 0; i < word[x]-'0'; i++)
		for (int j = 0; j < 3; j++)
			rec(kid[x][i], j);

	mini[x][c] = 1<<30;
	maxi[x][c] = -1;

	if (word[x] == '0') {
		mini[x][c] = maxi[x][c] = (c == 0);
	} else if (word[x] == '1') {
		for (int lc = 0; lc < 3; lc++) {
			if (lc == c) continue;
			mini[x][c] <?= mini[kid[x][0]][lc] + (c == 0);
			maxi[x][c] >?= maxi[kid[x][0]][lc] + (c == 0);
		}
	} else {
		for (int lc = 0; lc < 3; lc++)
		for (int rc = 0; rc < 3; rc++) {
			if (lc == c || rc == c || lc == rc) continue;
			mini[x][c] <?= mini[kid[x][0]][lc] + mini[kid[x][1]][rc] + (c == 0);
			maxi[x][c] >?= maxi[kid[x][0]][lc] + maxi[kid[x][1]][rc] + (c == 0);
		}
	}
}

int pos;
void parse()
{
	int x = pos;
	int c = word[x] - '0';
	pos++;
	for (int i = 0; i < c; i++) {
		kid[x][i] = pos;
		parse();
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		test_id = cs;
		scanf(" %s", word);
		pos = 0;
		parse();

		rec(0, 0);
		rec(0, 1);
		rec(0, 2);
		printf("%d %d\n",
			max(maxi[0][0], max(maxi[0][1], maxi[0][2])),
			min(mini[0][0], min(mini[0][1], mini[0][2]))
			);
	}
}
