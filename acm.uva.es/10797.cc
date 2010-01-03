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
using namespace std;

struct Point {
	double x, y;
	int id;
	Point *match;
};

double cross(Point *o, Point *a, Point *b)
{
	return (a->x - o->x) * (b->y - o->y) - (a->y - o->y) * (b->x - o->x);
}

Point *findMatch(Point *one, Point **P, int n)
{
	int a = 0, b = n-1, i, j;
	int mid = n/2;
	Point *two;

	while (a < b) {
		swap(P[a], P[(a + b) >> 1]);
		two = P[a];

		for (i = a, j = a+1; j <= b; j++) {
			if (cross(one, two, P[j]) > 0) {
				i++;
				swap(P[i], P[j]);
			}
		}
		swap(P[a], P[i]);

		// P[0..i-1] < P[i] < P[i+1..M-1]

		if (i < mid) {
			a = i+1;
		} else if (i == mid) {
			break;
		} else {
			b = i-1;
		}
	}

	return P[mid];
}

Point all[10010];
Point *A[10010], *B[10010];
int N, M;

pair<int, int> solve()
{
	assert(N % 2 == 1 && M % 2 == 1);

	for (int i = 1; i < N; i++) swap(A[i], A[rand() % (i+1)]);
	for (int i = 1; i < M; i++) swap(B[i], B[rand() % (i+1)]);

	for (int i = 0; i < N; i++) A[i]->match = findMatch(A[i], B, M);
	for (int i = 0; i < M; i++) {
		B[i]->match = findMatch(B[i], A, N);
		if (B[i]->match->match == B[i]) {
			return make_pair(B[i]->match->id, B[i]->id);
		}
	}

	abort();
}

int main()
{
	int total;
	srand(10852765);
	for (int cs = 1; scanf("%d", &total) == 1 && total > 0; cs++) {
		N = M = 0;
		for (int i = 0; i < total; i++) {
			scanf("%lf %lf", &all[i].x, &all[i].y);
			all[i].match = NULL;
			if (all[i].x < 0) {
				all[i].id = N;
				A[N++] = &all[i];
			} else {
				all[i].id = M;
				B[M++] = &all[i];
			}
		}
		pair<int, int> res = solve();
		printf("Case %d: %d %d\n", cs, res.first, res.second);
	}
}
