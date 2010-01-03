#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
} P[5010];

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		map<int, int> mx, my;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &P[i].x, &P[i].y);
			mx[P[i].x] = my[P[i].y] = 0;
		}
		sort(P, P+N);

		{
			int i = 0;
			for (map<int, int>::iterator it = mx.begin(); it != mx.end(); it++)
				it->second = i++;

			i = 0;
			for (map<int, int>::iterator it = my.begin(); it != my.end(); it++)
				it->second = i++;
			for (int i = 0; i < N; i++) {
				P[i].x = mx[P[i].x];
				P[i].y = my[P[i].y];
			}
		}

		static int xflag[5010];
		memset(xflag, 0, sizeof(xflag));

		int res = 0;
		for (int i = 0; i < N;) {
			int x = P[i].x;
			P[N].x = x+1;

			int j;
			for (j = i; P[j].x == x; j++) xflag[P[j].y] = 1;

			while (j < N) {
				int x1 = P[j].x, k = 0;
				P[N].x = x1+1;

				while (P[j].x == x1) { k += xflag[P[j].y]; j++; }
				res += k*(k-1)/2;
			}

			P[N].x = x+1;
			while (P[i].x == x) xflag[P[i++].y] = 0;
		}

		printf("Case %d: %d\n", cs, res);
	}
}
