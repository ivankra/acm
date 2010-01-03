#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
	int x1, y1, x2, y2, ax, ay, bx, by;
	cin >> x1 >> y1 >> x2 >> y2 >> ax >> ay >> bx >> by;
	if (ax > bx) swap(ax, bx);
	if (ay > by) swap(ay, by);

	x1 >?= ax; x1 <?= bx;
	x2 >?= ax; x2 <?= bx;

	y1 >?= ay; y1 <?= by;
	y2 >?= ay; y2 <?= by;

	int r = max(abs(x1-x2), abs(y1-y2));
	if (x1 == x2 && (x1==ax || x1==bx)) r = 0;
	if (y1 == y2 && (y1==ay || y1==by)) r = 0;
	printf("%d\n", r);
}
