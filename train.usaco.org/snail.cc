/*
ID: infnty1
PROB: snail
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

char A[128][128];

int rec(int y, int x, int dy, int dx) {
	int res = 0;
	if (A[y+dy][x+dx] == '.') {
		A[y+dy][x+dx] = '+';
		res = 1 + rec(y+dy, x+dx, dy, dx);
		A[y+dy][x+dx] = '.';
	} else if (A[y+dy][x+dx] == '#') {
		if (A[y-dx][x+dy] == '.') res >?= rec(y,x, -dx,dy);
		if (A[y+dx][x-dy] == '.') res >?= rec(y,x, dx,-dy);
	}
	return res;
}

int main() {
	freopen("snail.in", "r", stdin);
	freopen("snail.out", "w", stdout);

	int N, B;
	scanf("%d %d", &N, &B);

	memset(A, '#', sizeof(A));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			A[i][j] = '.';

	int row; char col;
	while (B-- > 0 && scanf(" %c%d", &col, &row) == 2)
		A[row][toupper(col)-'A'+1] = '#';

	if (A[1][1] == '#') { printf("0\n"); return 0; }

	A[1][1] = '+';
	printf("%d\n", 1 + max(rec(1,1, 0,1), rec(1,1, 1,0)));
}
