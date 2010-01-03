#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

int nrows, ncols;
char field[1024][1024];

int Up[1024][1024], Left[1024][1024], Right[1024][1024];

int main()
{
	scanf("%d %d", &ncols, &nrows);
	memset(field, 0, sizeof(field));
	for (int i = 1; i <= nrows; i++) {
		for (int j = 1; j <= ncols; j++) {
			int c;
			do { c = getchar(); } while (c != '0' && c != '1');
			field[i][j] = c - '0';
		}
	}

	memset(Up, 0, sizeof(Up));
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++)
			Up[r][c] = (field[r][c] ? Up[r-1][c] + 1 : 0);

		{
			vector<pair<int, int> > stk;
			stk.push_back(make_pair(-1, 0));

			for (int c = 1; c <= ncols; c++) {
				int len = 1;
				while (stk.back().first >= Up[r][c]) {
					len += stk.back().second;
					stk.pop_back();
				}
				Left[r][c] = field[r][c] ? len : 0;
				stk.push_back(make_pair(Up[r][c], len));
			}
		}

		{
			vector<pair<int, int> > stk;
			stk.push_back(make_pair(-1, 0));

			for (int c = ncols; c >= 1; --c) {
				int len = 1;
				while (stk.back().first >= Up[r][c]) {
					len += stk.back().second;
					stk.pop_back();
				}
				Right[r][c] = field[r][c] ? len : 0;
				stk.push_back(make_pair(Up[r][c], len));
			}
		}
	}

	/*
	printf("\nfield:\n");
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++) printf("%d", (int)field[r][c]);
		printf("\n");
	}

	printf("\nup:\n");
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++) printf("%d", (int)Up[r][c]);
		printf("\n");
	}

	printf("\nleft:\n");
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++) printf("%d", (int)Left[r][c]);
		printf("\n");
	}

	printf("\nright:\n");
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++) printf("%d", (int)Right[r][c]);
		printf("\n");
	}
*/

	int res = 0;
	for (int r = 1; r <= nrows; r++) {
		for (int c = 1; c <= ncols; c++) {
			if (field[r][c] == 0) continue;
			res = max(res, Up[r][c] * (Left[r][c] + Right[r][c] - 1));
		}
	}
	printf("%d\n",res);
}
