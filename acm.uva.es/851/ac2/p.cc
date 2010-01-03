#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;

#define CELL(r, c) (1ULL << (((r)<<3)+(c)))

u64 walls, inner;
int hdist[8][8], hmax[8][256], lim, nextlim;
char *sol[8*8*8*8];

int dfs(int d, u64 s) {
	// if we're done, print the solution we've taken...
	if (s == 0) {
		for (int i = 0; i < d; i++) printf("%s\n", sol[i]);
		return 1;
	}

	// estimate distance to goal state
	int f = hmax[1][(int)(s >> 8) & 0xff];
	f >?= hmax[2][(int)(s >> 16) & 0xff];
	f >?= hmax[3][(int)(s >> 24) & 0xff];
	f >?= hmax[4][(int)(s >> 32) & 0xff];
	f >?= hmax[5][(int)(s >> 40) & 0xff];
	f >?= hmax[6][(int)(s >> 48) & 0xff];

	// stop if we aren't going to remain within current limit
	f += d;
	if (f > lim) {
		nextlim <?= f;
		return 0;
	}

	// recursively explore all possible moves

	sol[d] = "south";
	if (dfs(d+1, ((s << 8) | (s & (walls >> 8))) & inner)) return 1;

	sol[d] = "north";
	if (dfs(d+1, ((s >> 8) | (s & (walls << 8))) & inner)) return 1;

	sol[d] = "east";
	if (dfs(d+1, ((s << 1) | (s & (walls >> 1))) & inner)) return 1;

	sol[d] = "west";
	return dfs(d+1, ((s >> 1) | (s & (walls << 1))) & inner);
}

void prep() {
	int que[100], *qh=que, *qt=que;

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++) {
		if (inner & CELL(i, j)) {
			hdist[i][j] = 1000;
		} else {
			hdist[i][j] = 0;
			if ((walls & CELL(i, j)) == 0) *qt++ = i * 256 + j;
		}
	}

	for (; qh < qt; qh++) {
		int r = (*qh) >> 8, c = (*qh) & 0xff;
		for (int d = 0; d < 4; d++) {
			int r1 = r + "1102"[d] - '1', c1 = c + "0211"[d] - '1';
			if (r1 < 0 || r1 >= 8 || c1 < 0 || c1 >= 8) continue;
			if (walls & CELL(r1, c1)) continue;
			if (hdist[r1][c1] > hdist[r][c] + 1) {
				hdist[r1][c1] = hdist[r][c] + 1;
                                *qt++ = r1 * 256 + c1;
			}
		}
	}

	for (int r = 1; r <= 6; r++) {
		hmax[r][0] = 0;
		for (int m = 1; m < 256; m++) {
			int i;
			for (i = 0; ((m >> i) & 1) == 0; i++);
			hmax[r][m] = max(hmax[r][m^(1<<i)], hdist[r][i]);
		}
	}
}

int main()
{
	int cs, n;
	for (scanf("%d", &cs); cs-- > 0 && scanf("%d", &n) == 1;) {
		walls = 0;
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int c;
			while ((c = getchar()) != EOF && c != 'O' && c != '.');
			if (c == 'O')
				walls |= CELL(i, j);
		}

		inner = 0;
		for (int i = 1; i < n-1; i++)
		for (int j = 1; j < n-1; j++)
			inner |= CELL(i, j);
		inner &= ~walls;

		prep();

		// Main IDA* loop
		for (lim = 0;; lim = nextlim) {
			nextlim = 8*8*8*8;
			if (dfs(0, inner)) break;
		}

		if (cs) printf("\n");
	}
}
