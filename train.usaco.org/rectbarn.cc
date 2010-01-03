/*
ID: infnty1
TASK: rectbarn
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

vector<int> column[3010];
int *p[3010], height, width;

void sort_unique(vector<int> &v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
	freopen("rectbarn.in", "r", stdin);
	freopen("rectbarn.out", "w", stdout);

	int P;
	scanf("%d %d %d", &height, &width, &P);

	for (int i = 0; i < P; i++) {
		int r, c;
		scanf("%d %d", &r, &c);
		column[c].push_back(r);
	}

	for (int c = 1; c <= width; c++) {
		column[c].push_back(0);
		column[c].push_back(height+1);
		sort_unique(column[c]);
	}

	int best = 0;

	for (int c = 1; c <= width; c++)
		p[c] = &column[c][0];

	for (int row = 1; row <= height; row++) {
		for (int c = 1; c <= width; c++) {
			while (p[c][1] <= row) p[c]++;
		}

		for (int c = 1; c <= width; c++) {
			if (p[c][0] == row)
				continue;

			int a = 0;
			int b = height+1;

			for (int w = 0; c <= width && p[c][0] != row; c++) {
				a >?= p[c][0];
				b <?= p[c][1];
				w++;
				best >?= (b - a - 1) * w;
			}
		}
	}

	printf("%d\n", best);
}
