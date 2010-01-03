#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int losing[100100];

void precalc(int k)
{
	memset(losing, 0xff, sizeof(losing));
	losing[0] = 0;
	
	long long diag = k;
	long long x, y;
	for (y = 1; y <= 100010 && diag <= 100010; y++) {
		if (losing[y] >= 0) continue;

		x = y + diag + 1;
		if (x > 100010) break;

		assert(x >= y);

		losing[y] = x;
		losing[x] = y;

		diag += k+1;

//if(y<=50) printf("y=%d x=%d\n",y,x);
	}
}

bool answer(int a, int b) {
	if (a <= b)
		return losing[a] == b;
	else
		return losing[b] == a;
}
/*
void dbg(int k) {
	const int N = 150;
	static char win[N+1][N+1];
	memset(win, 0 ,sizeof(win));
	for (int a = 0; a <= N; a++) {
		for (int b = 0; b <= N; b++) {
			win[a][b] = 0;
			if (a != 0 || b != 0) {
				for (int x = 0; x <= a; x++) {
					for (int y = 0; y <= b; y++) {
						if (x == 0 && y == 0) continue;
						if (x != 0 && y != 0 && abs(x-y) > k) continue;
						win[a][b] |= !win[a-x][b-y];
					}
				}
			}
		}
	}

	for (int a = 0; a <= N; a++) {
		for (int b = 0; b <= N; b++) {
			if (win[a][b])
				putchar('.');
			else
				putchar('L');

			bool X = answer(a, b);
			bool Y = !win[a][b];
			if (X != Y) {
				printf("\n");
				printf("error a=%d b=%d: answer=%d  must be=%d\n", a,b,X,Y);
				fflush(stdout);
				exit(1);
			}
		}
		printf("\n");
	}

}
*/

int main()
{
	int T;
	scanf("%d", &T);

	int k, q, a, b;
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &k, &q);
		precalc(k);
//		dbg(k);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &a, &b);
			if (answer(a, b))
				printf("LOSING\n");
			else
				printf("WINNING\n");
		}
		printf("\n");
	}
}
