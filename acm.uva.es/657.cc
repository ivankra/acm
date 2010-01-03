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

char g[64][64];
int dice[64][64], ndice;

void diceDfs(int y, int x) {
	if (dice[y][x] != 0 || g[y][x] == '.') return;
	dice[y][x] = ndice;
	diceDfs(y-1, x);
	diceDfs(y+1, x);
	diceDfs(y, x-1);
	diceDfs(y, x+1);
}

void dotDfs(int y, int x) {
	if (dice[y][x] == 0 || g[y][x] != 'X') return;
	g[y][x] = '*';
	dotDfs(y-1, x);
	dotDfs(y+1, x);
	dotDfs(y, x-1);
	dotDfs(y, x+1);
}

int main()
{
	int N, M;
	for (int cs = 1; scanf("%d %d", &M, &N) == 2 && N*M > 0; cs++) {
		memset(g, '.', sizeof(g));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf(" %c", &g[i][j]);

		memset(dice, 0, sizeof(dice));
		ndice = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (g[i][j] != '.' && dice[i][j] == 0) {
					ndice++;
					diceDfs(i, j);
				}
			}
		}

		vector<int> v(ndice, 0);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (g[i][j] == 'X') {
					++v[dice[i][j]-1];
					dotDfs(i, j);
				}
			}
		}

		sort(v.begin(), v.end());
		printf("Throw %d\n", cs);
		for (int i = 0; i < v.size(); i++)
			printf(i==0 ? "%d" : " %d", v[i]);
		printf("\n\n");
	}
}
