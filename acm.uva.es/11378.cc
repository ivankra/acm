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
#include <set>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int INF = 0x7fffffff;

int N, Px[100010], Py[100010];

struct Event {
	int x, y, kind;

	Event(int x_, int y_, int kind_) : x(x_), y(y_), kind(kind_) {}

	bool operator <(const Event &e) const {
		if (x != e.x) return x < e.x;
		if (kind != e.kind) return kind < e.kind;
		return y < e.y;
	}
};

bool check(int dist)
{
	for (int c = 0; c < 2; c++) {
		vector<Event> evs;
		for (int i = 0; i < N; i++) {
			int x = Px[i], y = Py[i];
			if (c == 1) swap(x, y);
			evs.push_back(Event(2*x-dist, y, +1));
			evs.push_back(Event(2*x+dist, y, -1));
		}

		sort(evs.begin(), evs.end());

//printf("check dist=%d  c=%d\n", dist, c);

		set<int> sweep;
		for (int i = 0; i < (int)evs.size(); i++) {
			int y = evs[i].y;
//printf("  x=%d: %d y=%d\n", evs[i].x, evs[i].kind, evs[i].y);
			if (evs[i].kind == -1) {
				sweep.erase(y);
			} else {
				if (sweep.count(y) != 0) return false;
				sweep.insert(y);
				set<int>::iterator it = sweep.find(y);

				if (it != sweep.begin()) {
					set<int>::iterator it2 = it; --it2;
					if (y - (*it2) < dist) return false;
				}

				++it;
				if (it != sweep.end()) {
					if ((*it) - y < dist) return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &Px[i], &Py[i]);

		int left = 0, right = 2000000;
		while (right - left > 1) {
			int mid = (left + right) / 2;
			if (check(mid))
				left = mid;
			else
				right = mid;
		}
		printf("%d\n", left);
	}
}
