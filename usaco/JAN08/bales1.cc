/*
ID: infnty1
LANG: C++
TASK: bales
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct Query {
	int a, b, value;
};

struct Event {
	int kind, x, h;

	bool operator <(const Event &e) const {
		return x < e.x;
	}
};

int minPos[26000], maxPos[26000], good[26000];

bool consistent(vector<Query> &Q)
{
	for (int y = 0; y <= 25000; y++) {
		minPos[y] = -1;
		maxPos[y] = 1000000000;
	}

	foreach (q, Q) {
		minPos[q->value] = max(minPos[q->value], q->a);
		maxPos[q->value] = min(maxPos[q->value], q->b);
		if (minPos[q->value] > maxPos[q->value]) return false;
	}

	vector<Event> evs;
	for (int y = 0; y <= 25000; y++) {
		if (minPos[y] < 0) {
			good[y] = 1;
			continue;
		}

		good[y] = 0;

		Event e;
		e.kind = +1;  e.x = minPos[y];      e.h = y;
		evs.push_back(e);

		e.kind = -1;  e.x = maxPos[y] + 1;  e.h = y;
		evs.push_back(e);
	}

	sort(evs.begin(), evs.end());

	set<int> profile;
	for (int i = 0; i < (int)evs.size();) {
		int x = evs[i].x;
		while (i < (int)evs.size() && evs[i].x == x) {
			if (evs[i].kind == 1)
				profile.insert(evs[i].h);
			else
				profile.erase(evs[i].h);
			i++;
		}

		if (profile.size() != 0) {
			set<int>::iterator it = profile.end();
			--it;
			int y = *it;
			good[y] = 1;
		}
	}

	for (int y = 0; y <= 25000; y++)
		if (good[y] == 0) return false;
	return true;
}

void normalize(vector<Query> &Q)
{
	map<int, int> y;
	for (int i = 0; i < (int)Q.size(); i++) {
		y[Q[i].value] = -1;
	}

	int k = 0;
	for (map<int, int>::iterator it = y.begin(); it != y.end(); ++it) {
		it->second = k;
		k++;
	}

	for (int i = 0; i < (int)Q.size(); i++) {
		Q[i].value = y[Q[i].value];
	}
}

int main()
{
	freopen("bales.in", "r", stdin);
	freopen("bales.out", "w", stdout);

	int N, Q;
	scanf("%d %d", &N, &Q);

	vector<Query> query(Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d", &query[i].a, &query[i].b, &query[i].value);
	}

	normalize(query);

	int left = 0, right = Q + 1;
	while (right - left > 1) {
		int mid = (left + right) / 2;
		vector<Query> part(query.begin(), query.begin() + mid);
		if (consistent(part))
			left = mid;
		else
			right = mid;
	}
	printf("%d\n", left < Q ? (left + 1) : 0);
}
