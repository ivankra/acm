/*
TASK: newbarn
ID: infnty1
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	static int x[20000], y[20000], x0[20000], y0[20000], N;

	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x0[i], &y0[i]);
		x[i] = x0[i]; y[i] = y0[i];
	}

	sort(x, x+N);
	sort(y, y+N);

	int lowX = x[(N-1)/2], highX = x[N/2];
	int lowY = y[(N-1)/2], highY = y[N/2];

	for (int i = 0; i < N; i++) {
		x[i] = x0[i];
		y[i] = y0[i];
	}

	int inconv = 0;
	for (int i = 0; i < N; i++)
		inconv += abs(x[i] - lowX) + abs(y[i] - lowY);

	int cnt = (highX - lowX + 1) * (highY - lowY + 1);
	for (int i = 0; i < N; i++) {
		if (lowX <= x[i] && x[i] <= highX && lowY <= y[i] && y[i] <= highY)
			cnt--;
	}

	printf("%d %d\n", inconv, cnt);	
}
