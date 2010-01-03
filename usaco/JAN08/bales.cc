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
	long long originalValue;
};

struct Event {
	int kind, x, y;

	bool operator <(const Event &e) const {
		return x < e.x;
	}
};

int minPos[26000], maxPos[26000], good[26000], N;
long long ymap[26000], area[26000];

bool consistent(vector<Query> &Q, int NQ)
{
	for (int y = 0; y <= 25000; y++) {
		minPos[y] = -1;
		maxPos[y] = 1000000000;
	}

	for (int i = 0; i < NQ; i++) {
		Query &q = Q[i];
		if (q.originalValue < 1 || q.originalValue > 1000000000) return false;
		assert(0 <= q.value && q.value <= 25000);
		minPos[q.value] = max(minPos[q.value], q.a);
		maxPos[q.value] = min(maxPos[q.value], q.b);
		if (minPos[q.value] > maxPos[q.value]) return false;
	}

	vector<Event> evs;
	for (int y = 0; y <= 25000; y++) {
		if (minPos[y] < 0) {
			good[y] = 1;
			continue;
		}

		good[y] = 0;
		area[y] = 0;

		Event e;
		e.kind = +1;  e.x = minPos[y];      e.y = y;
		evs.push_back(e);

		e.kind = -1;  e.x = maxPos[y] + 1;  e.y = y;
		evs.push_back(e);
	}

	sort(evs.begin(), evs.end());
	if (evs.size() == 0) return true;

	//int firstX = evs[0].x;
	//int lastX = evs.back().x;

	set<int> profile;
	for (int i = 0; i < (int)evs.size();) {
		int x = evs[i].x;
		while (i < (int)evs.size() && evs[i].x == x) {
			if (evs[i].kind == 1)
				profile.insert(evs[i].y);
			else if (evs[i].kind == -1)
				profile.erase(evs[i].y);
			i++;
		}

		if (profile.size() != 0 && x <= N) {
			set<int>::iterator it = profile.end();
			--it;
			int y = *it;
			good[y] = 1;
			assert(i < (int)evs.size());
			area[y] += evs[i].x - x;
		}
	}

	for (int y = 0; y <= 25000; y++)
		if (good[y] == 0) return false;

	long long top = 1000000000;
	for (int yi = 25000; yi >= 0; --yi) {
		if (minPos[yi] < 0) continue;
		long long y = ymap[yi];
		long long a = area[yi];
		if (top - a + 1 < y) return false;
		top -= a;
	}

	return true;
}

void normalize(vector<Query> &Q)
{
	map<long long, int> y;
	for (int i = 0; i < (int)Q.size(); i++) y[Q[i].originalValue] = -1;
	int k = 0;
	foreach (it, y) { it->second = k; ymap[k] = it->first; k++; }
	for (int i = 0; i < (int)Q.size(); i++) {
		Q[i].value = y[Q[i].originalValue];
	}
}

int main()
{
	freopen("bales.in", "r", stdin);
	freopen("bales.out", "w", stdout);

	int Q;
	scanf("%d %d", &N, &Q);

	vector<Query> query(Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %lld", &query[i].a, &query[i].b, &query[i].originalValue);
		assert(1 <= query[i].a);
		assert(query[i].a <= query[i].b);
		assert(query[i].b <= N);
	}

	normalize(query);

	int left = 0, right = Q + 1;
	while (right - left > 1) {
		int mid = (left + right) / 2;
		if (consistent(query, mid))
			left = mid;
		else
			right = mid;
	}
	printf("%d\n", left < Q ? (left + 1) : 0);
}
