#include <cstdio>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &q) const {
		return x<q.x || (x==q.x && y<q.y);
	}
	bool operator ==(const Point &q) const {
		return x == q.x && y == q.y;
	}
} P[301];

bool on(const Point &p, const Point &a, const Point &b) {
	return (a.x-p.x)*(b.y-p.y)-(a.y-p.y)*(b.x-p.x) == 0;
}

int main()
{
	for (;;) {
		int N;
		for (N = 0; scanf("%d %d", &P[N].x, &P[N].y) == 2; N++)
			if ((P[N].x | P[N].y) == 0) break;
		if (N == 0) break;

		sort(P, P+N);
		N = unique(P, P+N) - P;

		int ln = 0;
		for (int a = 0; a < N; a++)
		for (int b = a+1; b < N; b++) {
			int c;
			for (c = 0; c < b; c++)
				if (c != a && on(P[c], P[a], P[b])) break;
			if (c < b) continue;

			for (c = b+1; c < N; c++)
				if (on(P[c], P[a], P[b])) break;
			if (c >= N) continue;

			if (ln++ == 0)
				printf("The following lines were found:\n");

			for (c = a; c < N; c++)
				if (on(P[c], P[a], P[b]))
					printf("(%4d,%4d)", P[c].x, P[c].y);
			printf("\n");
		}

		if (ln == 0)
			printf("No lines were found\n");
	}
}
