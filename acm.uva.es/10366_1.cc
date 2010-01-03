#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;

#define SIZE(x) int((x).size())

typedef long long LL;

struct Cell {
	LL divL, divR, water, len;
	Cell *L, *R;
};

Cell cells[2000];
LL answer;
vector<Cell *> current;

bool simulate()
{
	sort(current.begin(), current.end());
	current.erase(unique(current.begin(), current.end()), current.end());
	reverse(current.begin(), current.end());
	while (current.size() > 0 && current.back() == NULL) current.pop_back();
	if (current.size() == 0) return false;

	LL delta = LLONG_MAX;
	for (int i = 0; i < SIZE(current); i++) {
		Cell *c = current[i];
		LL t = min(c->divL, c->divR) * c->len - c->water;
		assert(t >= 0);
		delta = min(delta, t);
	}

	if (delta != 0) {
		for (int i = 0; i < SIZE(current); i++) {
			Cell *c = current[i];
			c->water += delta;
			answer += delta;
		}
		return true;
	}

	for (int i = 0; i < SIZE(current); i++) {
		Cell *c = current[i];
		if (c->water != min(c->divL, c->divR) * c->len) continue;
		if (c->divL <= c->divR && c->L == NULL) return false;
		if (c->divR <= c->divL && c->R == NULL) return false;
	}

	for (int i = 0; i < SIZE(current); i++) {
		Cell *c = current[i];
		if (c->water != min(c->divL, c->divR) * c->len) continue;

		if (c->L) assert(c->L->divR == c->divL);
		if (c->R) assert(c->R->divL == c->divR);

		if (c->divL == c->divR) {
			Cell *next[2] = { NULL, NULL };

			if (c->L->water == c->divL * c->L->len) {
				Cell *z = c->L;
				c->divL = z->divL;
				c->water += z->water;
				c->len += z->len;
				c->L = z->L;
				if (c->L != NULL) c->L->R = c;
			} else {
				next[0] = c->L;
			}

			if (c->R->water == c->divR * c->R->len) {
				Cell *z = c->R;
				c->divR = z->divR;
				c->water += z->water;
				c->len += z->len;
				c->R = z->R;
				if (c->R != NULL) c->R->L = c;
			} else {
				next[1] = c->R;
			}

			if (next[0] == NULL && next[1] == NULL) next[0] = c;

			current[i] = NULL;
			if (next[0] != NULL) current.push_back(next[0]);
			if (next[1] != NULL) current.push_back(next[1]);
			return true;
		}

		if (c->divL < c->divR) {
			if (c->L->water < c->divL * c->L->len) {
				current[i] = c->L;
			} else {
				Cell *z = c->L;
				c->divL = z->divL;
				c->water += z->water;
				c->len += z->len;
				c->L = z->L;
				if (c->L != NULL) c->L->R = c;

				for (int j = 0; j < SIZE(current); j++)
					if (current[j] == z) current[j] = NULL;
			}
			return true;
		}

		if (c->divR < c->divL) {
			if (c->R->water < c->divR * c->R->len) {
				current[i] = c->R;
			} else {
				Cell *z = c->R;
				c->divR = z->divR;
				c->water += z->water;
				c->len += z->len;
				c->R = z->R;
				if (c->R != NULL) c->R->L = c;

				for (int j = 0; j < SIZE(current); j++)
					if (current[j] == z) current[j] = NULL;
			}
			return true;
		}

	}

	return false;
}

int main()
{
	int leftX, rightX;
	while (cin >> leftX >> rightX) {
		if (leftX >= 0 || rightX <= 0) break;

		int N = (rightX - leftX) / 2, D[2000];
		for (int i = 0; i <= N; i++) cin >> D[i];

		current.clear();
		current.push_back(NULL);
		for (int i = 0; i < N; i++) {
			cells[i].L = (i == 0 ? NULL : &cells[i-1]);
			cells[i].R = (i+1 >= N ? NULL : &cells[i+1]);
			cells[i].divL = D[i];
			cells[i].divR = D[i+1];
			cells[i].len = 2;
			cells[i].water = 0;
			if (leftX + 2 * i == -1) current[0] = &cells[i];
		}

		answer = 0;
		while (simulate());
		cout << answer << endl;
	}
}
