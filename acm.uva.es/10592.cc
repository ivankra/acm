#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

char grid[64][64];
int N, sector[64][64], nsec;
int seen[64][64];

void sdfs(int y, int x) {
	if (grid[y][x] != '.' && sector[y][x] == 0) {
		sector[y][x] = nsec;
		sdfs(y-1, x);
		sdfs(y+1, x);
		sdfs(y, x-1);
		sdfs(y, x+1);
	}
}

int gdfs(int y, int x, int g) {
	if ((grid[y][x] == 'P' || grid[y][x] == 'B') && grid[y][x] != g) return 1;
	if (seen[y][x] || grid[y][x] != g) return 0;
	seen[y][x] = 1;
	return gdfs(y-1,x,g) | gdfs(y+1,x,g) | gdfs(y,x-1,g) | gdfs(y,x+1,g);
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		memset(grid, '.', sizeof(grid));
		for (int y = 1; y <= N; y++)
			for (int x = 1; x <= N; x++)
				scanf(" %c", &grid[y][x]);

		memset(sector, 0, sizeof(sector));
		nsec = 0;
		for (int y = 1; y <= N; y++)
			for (int x = 1; x <= N; x++)
				if (sector[y][x] == 0 && grid[y][x] != '.') {
					nsec++;
					sdfs(y, x);
				}

		memset(seen, 0, sizeof(seen));

		int secB[64*64], secP[64*64], fight=0;
		for (int i = 0; i <= nsec; i++) secB[i] = secP[i] = 0;

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (seen[y][x]) continue;

				if (grid[y][x] == 'B') {
					secB[sector[y][x]]++;
					fight += gdfs(y, x, 'B');
				}

				if (grid[y][x] == 'P') {
					secP[sector[y][x]]++;
					fight += gdfs(y, x, 'P');
				}
			}
		}

		for (int s = 1; s <= nsec; s++)
			printf("Sector #%d: contain %d freedom fighter group(s) & %d enemy group(s)\n",
				s, secB[s], secP[s]);

		printf("Total %d group(s) are in fighting position.\n\n", fight);
	}
}
