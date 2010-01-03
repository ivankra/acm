// ICPC Finals 2003 - Problem D - Eurodiffusion
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;

int grid[16][16], money[12][16][32], moneyPlus[12][16][32], K;
int countrySize[32], countryCC[32], countryT[32], gridT[16][16], gridMask[16][16];
char name[32][128];

int main()
{
	for (int cs = 1; scanf("%d", &K) == 1 && K > 0; cs++) {
		printf("Case Number %d\n", cs);

		memset(grid, 0, sizeof(grid));
		memset(gridMask, 0, sizeof(gridMask));
		memset(money, 0, sizeof(money));
		memset(moneyPlus, 0, sizeof(moneyPlus));

		for (int c = 1; c <= K; c++) {
			int x1, y1, x2, y2;
			scanf("%s %d %d %d %d", name[c], &x1, &y1, &x2, &y2);
			countrySize[c] = 0;
			countryCC[c] = 0;
			for (int x = x1; x <= x2; x++) {
				for (int y = y1; y <= y2; y++) {
					assert(grid[x][y] == 0);
					grid[x][y] = c;
					gridMask[x][y] |= 1 << (c - 1);
					money[x][y][c] += 1000000;
					++countrySize[c];
				}
			}
		}

		memset(countryT, 0x3f, sizeof(countryT));
		memset(gridT, 0x3f, sizeof(gridT));

		for (int days = 0;; days++) {
			for (int x = 1; x <= 10; x++) {
				for (int y = 1; y <= 10; y++) {
					if (grid[x][y] == 0) continue;
					if (gridMask[x][y] != (1 << K) - 1) continue;
					if (days < gridT[x][y]) {
						gridT[x][y] = days;
						++countryCC[grid[x][y]];
					}
				}
			}

			bool stopFlag = true;
			for (int c = 1; c <= K; c++) {
				if (countryCC[c] != countrySize[c])
					stopFlag = false;
				else if (days < countryT[c])
					countryT[c] = days;
			}
			if (stopFlag || K <= 1) break;

			static int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };
			for (int x = 1; x <= 10; x++) {
				for (int y = 1; y <= 10; y++) {
					if (grid[x][y] == 0) continue;
					for (int m = 1; m <= K; m++) {
						int repr = money[x][y][m] / 1000;
						if (repr == 0) continue;
						for (int dir = 0; dir < 4; dir++) {
							int xx = x + dx[dir], yy = y + dy[dir];
							if (grid[xx][yy] != 0) {
								moneyPlus[xx][yy][m] += repr;
								gridMask[xx][yy] |= 1 << (m - 1);
								money[x][y][m] -= repr;
							}
						}
					}
				}
			}

			for (int x = 1; x <= 10; x++) {
				for (int y = 1; y <= 10; y++) {
					if (grid[x][y] == 0) continue;
					for (int m = 1; m <= K; m++) {
						money[x][y][m] += moneyPlus[x][y][m];
						moneyPlus[x][y][m] = 0;
					}
				}
			}
		}

		vector<pair<int, string> > v;
		for (int c = 1; c <= K; c++) {
			v.push_back(pair<int, string>(countryT[c], string(name[c])));
		}
		sort(v.begin(), v.end());

		for (int i = 0; i < K; i++) {
			printf("   %s   %d\n", v[i].second.c_str(), v[i].first);
		}
	}
}
