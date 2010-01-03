#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int N, Q;
struct Point { int x, y; } P[20010], A, B;
double v[20010];

double solve()
{
	double a = B.y - A.y;
	double b = A.x - B.x;
	{ double t = sqrt(a*a+b*b); a /= t; b /= t; }

	// Line l: ax+by=c
	// Distance from (x,y) to l: |ax+by-c|

	for (int i = 0; i < N; i++) v[i] = a*P[i].x + b*P[i].y;

	nth_element(v, v+N/2, v+N);

	double c = v[N/2];
	double res = 0;
	for (int i = 0; i < N; i++)
		res += fabs(v[i] - c);
	return res;
}

int main()
{
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &P[i].x, &P[i].y);
	}

	for (int cs = 1; cs <= Q; cs++) {
		scanf("%d %d %d %d", &A.x, &A.y, &B.x, &B.y);
		printf("Case %d: %.0f\n", cs, solve());
	}
}

