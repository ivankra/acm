#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int dx[256], dy[256];
int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
int out[1024][1024];

void sim(string s, int flag, int roach) {
	int x = 0, y = 0;
	for (int i = s.size()-1;; i--) {
		if (flag == 0) {
			min_x <?= x;
			max_x >?= x;
			min_y <?= y;
			max_y >?= y;
		} else {
			out[y - min_y][x - min_x] |= 1 << roach;
		}

		if (i < 0) break;

		x -= dx[s[i]];
		y -= dy[s[i]];
	}
}

int main()
{
	memset(dx, 0, sizeof(dx));
	memset(dy, 0, sizeof(dy));

	dx['L'] = -1;
	dx['R'] = +1;
	dy['U'] = -1;
	dy['D'] = +1;

	string A, B;
	for (;;) {
		int id;
		char mv[10];
		if (scanf("Cockroach%d-%s ", &id, mv) != 2) break;
		if (id == 1) A += mv[0]; else B += mv[0];
	}

	memset(out, 0, sizeof(out));
	for (int k = 0; k < 2; k++) {
		sim(A, k, 0);
		sim(B, k, 1);
	}

	for (int i = 0; i <= max_y - min_y; i++) {
		for (int j = 0; j <= max_x - min_x; j++) {
			if (out[i][j] == 0) putchar('.');
			else if (out[i][j] == 1) putchar('1');
			else if (out[i][j] == 2) putchar('2');
			else putchar('*');
		}
		putchar('\n');
	}


}
