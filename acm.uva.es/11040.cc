#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int tab[16][16], T;
	for (scanf("%d", &T); T-- > 0;) {
		memset(tab, 0, sizeof(tab));
		for (int row = 1; row <= 9; row += 2)
			for (int col = 1; col <= row; col += 2)
				scanf("%d", &tab[row][col]);

		for (int row = 9; row >= 3; row--) {
			for (int col = 2; col < row; col += 2) {
				int a = tab[row][col-1];
				int b = tab[row][col+1];
				int c = tab[row-2][col-1];
				tab[row][col] = (c-a-b)/2;
			}

			row--;
			for (int col = 1; col <= row; col++)
				tab[row][col] = tab[row+1][col] + tab[row+1][col+1];
		}

		for (int row = 1; row <= 9; row++)
			for (int col = 1; col <= row; col++)
				printf("%d%s", tab[row][col], col==row?"\n":" ");
	}
}
