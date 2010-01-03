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
#include <set>
using namespace std;
typedef long long LL;

struct Constraint {
	// a * value[x] + b * value[y] = c
	LL a, b, c;
	int x, y;
};

LL value[1024];
int N, K, isFixed[1024], seen[1024], seenId;
vector<Constraint> adj[1024];
vector<Constraint> lone, allConstraints;

bool makeImplications(int x)
{
	assert(!isFixed[x]);

	seen[x] = seenId;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		const Constraint &cs = adj[x][i];
		assert(cs.x == x);

		LL yval = cs.c - cs.a * (LL)value[x];
		if (yval % cs.b != 0) return false;
		yval /= cs.b;
		if (yval < 1 || yval > K) return false;

		if (seen[cs.y] != seenId) {
			value[cs.y] = yval;
			makeImplications(cs.y);
		} else if (value[cs.y] != yval) {
			return false;
		}
	}

	return true;
}

void setAllFixed(int x) {
	if (isFixed[x]) return;
	isFixed[x] = 1;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		setAllFixed(adj[x][i].y);
	}
}

bool tryToFixValue(int s, LL newValue)
{
	if (newValue < 1 || newValue > K) return false;
	if (isFixed[s]) { return newValue == value[s]; }

	seenId++;
	value[s] = newValue;
	if (!makeImplications(s)) return false;

	setAllFixed(s);
	return true;
}

bool solve()
{
	memset(isFixed, 0, sizeof(isFixed));
	memset(seen, 0, sizeof(seen));
	seenId = 1;

	// degenerate constraints
	for (int i = 0; i < (int)lone.size(); i++) {
		Constraint cs = lone[i];
		if (cs.a == 0 && cs.b == 0) {
			if (cs.c != 0) return false;
		} else if (cs.x == cs.y) {
			LL a = cs.a + cs.b;
			if (a == 0) {
				if (cs.c != 0) return false;
				continue;
			}
			if (cs.c % a != 0) return false;
			if (!tryToFixValue(cs.x, cs.c/a)) return false;
		} else {
			if (cs.a == 0) { swap(cs.a, cs.b); swap(cs.x, cs.y); }
			assert(cs.a != 0 && cs.b == 0);
			// cs.a * value[cs.x] = cs.c
			if (cs.c % cs.a != 0) return false;
			if (!tryToFixValue(cs.x, cs.c/cs.a)) return false;
		}
	}

	for (int s = 1; s <= N; s++) {
		if (isFixed[s]) continue;
		value[s] = 0;
		for (int v = 1; v <= K; v++) {
			if (tryToFixValue(s, v)) break;
			value[s] = 0;
		}
		if (value[s] == 0) return false;
	}

	for (int i = 0; i < (int)allConstraints.size(); i++) {
		const Constraint &cs = allConstraints[i];
		if (cs.a * (LL)value[cs.x] + cs.b * (LL)value[cs.y] != cs.c) return false;
	}

	return true;
}

int main()
{
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N, &M, &K);
		assert(1 <= N && N <= 1000 && 1 <= K && K <= 100);
		assert(0 <= M && M <= 10000);

		for (int i = 0; i < 1024; i++) adj[i].clear();
		lone.clear();
		allConstraints.clear();

		for (int i = 0; i < M; i++) {
			Constraint z;
			scanf("%lld %d %lld %d %lld", &z.a, &z.x, &z.b, &z.y, &z.c);
			assert(1 <= z.x && z.x <= N);
			assert(1 <= z.y && z.y <= N);
			allConstraints.push_back(z);
			if (z.a == 0 || z.b == 0 || z.x == z.y) {
				lone.push_back(z);
			} else {
				adj[z.x].push_back(z);
				swap(z.a, z.b);
				swap(z.x, z.y);
				adj[z.x].push_back(z);
			}
		}

		if (solve())
			printf("yes\n");
		else
			printf("no\n");
	}
}
