/*
ID: infnty1
PROB: wissqu
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
using namespace std;

char field[8][8], orig[8][8];
int nw[8][8], remain[256];

bool ok(int y, int x, char c) {
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if (field[y+dy][x+dx] == c) return false;
	return true;
}

typedef unsigned long long u64;
map<u64, int> memo;
char moves[16][20];
int nleaves = 0;

int go(int k) {
	if (k >= 16) {
		if (nleaves++ == 0) {
			for (int i = 0; i < 16; i++) printf("%s\n", moves[i]);
		}
		return 1;
	}

	u64 key = 0;
	for (int y = 1; y <= 4; y++)
		for (int x = 1; x <= 4; x++)
			key = (key << 4) | ((field[y][x]-'A')<<1) | nw[y][x];
	if (memo.count(key) != 0) return memo[key];

	int &res = memo[key];
	res = 0;

	for (int c = 'A'; c <= 'E'; c++) {
		if (remain[c] == 0) continue;
		for (int y = 1; y <= 4; y++) {
			for (int x = 1; x <= 4; x++) {
				if (nw[y][x] != 0 || !ok(y,x,c)) continue;

				nw[y][x] = 1;
				field[y][x] = c;
				remain[c]--;

				sprintf(moves[k], "%c %d %d", c, y, x);
				res += go(k+1);

				nw[y][x] = 0;
				field[y][x] = orig[y][x];
				remain[c]++;
			}
		}
	}

	return res;
}

int main() {
	freopen("wissqu.in", "r", stdin);
	freopen("wissqu.out", "w", stdout);

	memset(orig, 0, sizeof(orig));
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			scanf(" %c", &orig[i][j]);

	int res = 0;
	for (int y = 1; y <= 4; y++) {
		for (int x = 1; x <= 4; x++) {
			memcpy(field, orig, sizeof(orig));
			if (!ok(y,x,'D')) continue;
			memset(nw, 0, sizeof(nw));
			nw[y][x] = 1;
			field[y][x] = 'D';
			sprintf(moves[0], "D %d %d", y, x);
			for (int c = 'A'; c <= 'E'; c++)
				remain[c] = 3;
			res += go(1);
		}
	}

	printf("%d\n", res);
}
