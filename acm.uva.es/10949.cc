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

char S1[65536], S2[65536];
int N1, N2, first[256], last[256], next[65536], prev[65536];

int solve() {
	bool swapped = false;
	if (N1 > N2) {
		for (int i = 0; i <= N1; i++) swap(S1[i], S2[i]);
		swap(N1, N2);
		swapped = true;
	}
	S1[N1] = S2[N2] = S1[N1+1] = S2[N2+1] = 0;

	memset(last, 0xff, sizeof(last));
	memset(first, 0xff, sizeof(first));
	memset(next, 0xff, sizeof(next));
	memset(prev, 0xff, sizeof(prev));

	for (int i = 0; i < N1; i++) {
		int c = S1[i];
		if (last[c] < 0) {
			first[c] = i;
		} else {
			prev[i] = last[c];
			next[last[c]] = i;
		}
		last[c] = i;
	}

	static int offs[25000], L;
	L = 0;
	offs[0] = -1;

	for (int i = 0; i < N2; i++) {
		int c = S2[i];

		int up = L;
		for (int j = last[c]; j != -1; j = prev[j]) {
			if (j > offs[L]) {
				offs[++L] = j;
				up = L;
				continue;
			}

			int a = 1, b = up;
			while (a != b) {
				int mid = (a + b) >> 1;
				if (offs[mid] < j)
					a = mid + 1;
				else
					b = mid;
			}

			if (j < offs[a]) offs[a] = j;
			up = a;
		}
	}

	return L;
}

int width, height;
char grid[64][64];

void readStr(int &n, char s[]) {
	int x, y;
	scanf("%d %d %d", &n, &x, &y);
	s[0] = grid[x][y];
	for (int i = 1; i <= n; i++) {
		char c;
		scanf(" %c", &c);
		if (c == 'N') x--;
		else if (c == 'S') x++;
		else if (c == 'E') y++;
		else y--;
		x >?= 1; x <?= height;
		y >?= 1; y <?= width;
		s[i] = grid[x][y];
	}
	n++;
	s[n] = 0;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &height, &width) == 2; cs++) {
		for (int i = 1; i <= height; i++)
			for (int j = 1; j <= width; j++)
				scanf(" %c", &grid[i][j]);

		readStr(N1, S1);
		readStr(N2, S2);

		int n = N1, m = N2;
		int l = solve();
		printf("Case %d: %d %d\n", cs, n-l, m-l);
	}
}
