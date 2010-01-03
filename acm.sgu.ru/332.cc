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

enum { MAXN = 10010 };

struct Line {
	// ax + by + c = 0;
	double a, b, c;
};

struct Side : public Line {
	long long ai, bi;
	int next, prev;
	double t;
};

Side sides[MAXN];

void updateTime(int sideIndex) {
	Side &cur = sides[sideIndex];
	const Side &prev = sides[cur.prev];
	const Side &next = sides[cur.next];

	cur.t = 1e20;

	if (prev.ai * cur.bi == prev.bi * cur.ai) return;
	if (cur.ai * next.bi == cur.bi * next.ai) return;

	Line l, m;
	l.a = prev.a - cur.a;
	l.b = prev.b - cur.b;
	l.c = prev.c - cur.c;

	m.a = cur.a - next.a;
	m.b = cur.b - next.b;
	m.c = cur.c - next.c;

	double det = l.a * m.b - l.b * m.a;
	//if (fabs(det) < 1e-9) return;

	double x = -(l.c * m.b - l.b * m.c) / det;
	double y = -(l.a * m.c - l.c * m.a) / det;
	cur.t = cur.a * x + cur.b * y + cur.c;
}

int heap[MAXN], heapPos[MAXN], heapSize;

void heapSwap(int i, int j) {
	int t = heap[i];
	heapPos[heap[i] = heap[j]] = i;
	heapPos[heap[j] = t] = j;
}

void heapDown(int i) {
	int j;
	while ((j = 2 * i) <= heapSize) {
		if (j+1 <= heapSize && sides[heap[j+1]].t < sides[heap[j]].t) j++;
		if (sides[heap[i]].t < sides[heap[j]].t) break;
		heapSwap(i, j);
		i = j;
	}
}

void heapUp(int i) {
	while (i > 1 && sides[heap[i]].t < sides[heap[i>>1]].t) {
		heapSwap(i, i>>1);
		i >>= 1;
	}
}

int main()
{
	long long Px[MAXN], Py[MAXN];
	int N;

	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			Px[i] = x;
			Py[i] = y;
		}

		for (int i = 0; i < N; i++) {
			int j = (i + 1) % N;
			Side &s = sides[i];
			s.a = s.ai = Py[i] - Py[j];
			s.b = s.bi = Px[j] - Px[i];
			double t = sqrt(s.a * s.a + s.b * s.b);
			s.a /= t;
			s.b /= t;
			s.c = -(s.a * Px[i] + s.b * Py[i]);
			sides[i].next = j;
			sides[j].prev = i;
		}

		for (int i = 0; i < N; i++) updateTime(i);

		heapSize = N;
		for (int i = N; i >= 1; i--) {
			heap[i] = i-1;
			heapPos[i-1] = i;
			heapDown(i);
		}

		double curTime = 0;
		while (heapSize >= 3) {
			int sideIndex = heap[1];
			heapSwap(1, heapSize);
			heapSize--;
			heapDown(1);

			curTime = sides[sideIndex].t;

			int next = sides[sideIndex].next;
			int prev = sides[sideIndex].prev;
			sides[next].prev = prev;
			sides[prev].next = next;

			updateTime(next);
			heapDown(heapPos[next]);
			heapUp(heapPos[next]);

			updateTime(prev);
			heapDown(heapPos[prev]);
			heapUp(heapPos[prev]);
		}

		printf("%.3f\n", curTime);
	}
}
