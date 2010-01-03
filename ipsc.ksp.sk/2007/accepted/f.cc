#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include <gmpxx.h>
using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define all(v) (v).begin(), (v).end()
#define foreach(it,v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

int NB, NCells;
int bvalue[4][16][16], bcolor[4][16][16], indexOf[4][16][16];

struct Cell {
	int b, row, col, color;
	int *valuep;
	VI color_adj, adj;
} cell[4*16*16];

void rec(int b, int row, int col) {
	if (col >= 9) { row++; col = 0; }
	if (row >= 9) { b++; row = col = 0; }
	if (b >= NB) {
		printf("done  NB=%d\n",NB);
		for (int i = 0; i < NB; i++) {
			for (int j = 0; j < 9; j++) {
				for (int k = 0; k < 9; k++)
					printf(k==0?"%d":" %d", bvalue[i][j][k]);
				printf("\n");
			}
			printf("\n");
		}
		exit(0);
	}

	Cell &c = cell[indexOf[b][row][col]];
	if (bvalue[b][row][col] != 0) {
		rec(b, row, col+1);
		return;
	}

	for (int x = 1; x <= 9; x++) {
		bvalue[b][row][col] = x;
		foreach(it, c.color_adj) *(cell[*it].valuep) = x;

		foreach(it, c.adj) if (*(cell[*it].valuep) == x) goto skip;

		rec(b, row, col+1);
skip:;
	}

	bvalue[b][row][col] = 0;
	foreach(it, c.color_adj) *(cell[*it].valuep) = 0;
}

void solve()
{
	rec(0, 0, 0);
	printf("failed\n");
}

void load()
{
	cin >> NB;

	memset(bvalue, 0, sizeof(bvalue));
	memset(bcolor, 0, sizeof(bcolor));

	int ind = 0;
	for (int b = 0; b < NB; b++) {
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				for (;;) {
					int c = getchar();
					assert(c != EOF);
					if (isspace(c))
						continue;
					else if (isalpha(c))
						bcolor[b][row][col] = c;
					else if (isdigit(c)) {
						bvalue[b][row][col] = c-'0';
						break;
					} else if (c == '.') {
						bvalue[b][row][col] = 0;
						break;
					} else {
						assert(false /* invalid input */);
					}
				}

				indexOf[b][row][col] = ind;
				Cell &e = cell[ind];
				e.b = b;
				e.row = row;
				e.col = col;
				e.color = bcolor[b][row][col];
				e.valuep = &bvalue[b][row][col];
				ind++;
			}
		}
	}
	NCells = ind;

	for (int i = 0; i < NCells; i++) {
		for (int j = 0; j < NCells; j++) {
			Cell &c1 = cell[i];
			Cell &c2 = cell[j];
			if (i == j) continue;
			
			if (c1.color == c2.color && c1.color != 0) {
				c1.color_adj.push_back(j);
			}

			if (c1.b == c2.b) {
				if (c1.row == c2.row || c1.col == c2.col ||
				    (c1.row/3 == c2.row/3 && c1.col/3 == c2.col/3)) {
					c1.adj.push_back(j);
					//printf("c1:%d,%d,%d,%c c2:%d,%d,%d,%c\n",
					//	c1.b,c1.row,c1.col,c1.color,c2.b,c2.row,c2.col,c2.color);
					assert(c1.color != c2.color || c1.color == 0);
				}
			}


		}
	}

}

int main()
{
	load();
	solve();

}
