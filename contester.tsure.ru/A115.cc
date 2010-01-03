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

int main()
{
	int N;
	cin >> N;

	int a[128][128];

	for (int y = 0, x = N-1, k = 1; k <= N*N; k++) {
		a[y][x] = k;
		y++; x++;
		if (y >= N) {
			y = y - x + 1;
			x = 0;
		} else if (x >= N) {
			x = x - y - 1;
			y = 0;
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++)
			printf(x==0 ? "%d" : " %d", a[y][x]);
		printf("\n");
	}
}
