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
typedef long long LL;
const double PI = 2 * acos(0.0);

typedef pair<int, int> Pair;

struct Row {
	vector<Pair> rle;
	int len;
	int at1, at2;

	Pair next() {
		assert(at1 < (int)rle.size());
		//if (at1 >= (int)rle.size()) return make_pair(0, 0);
		return make_pair(rle[at1].first - at2, rle[at1].second);
	}

	void skip(int n) {
		at2 += n;
		while (at1 < (int)rle.size()) {
			if (at2 < rle[at1].first)
				break;
			at2 -= rle[at1].first;
			at1++;
		}
	}
};

Row row[1024];
int height, width;

void readRow(int i)
{
	Row &r = row[i];
	Pair p;

	r.rle.clear();
	r.rle.push_back(make_pair(i, 0));
	for (int m = 0; m < width;) {
		scanf("%d %d", &p.first, &p.second);
		r.rle.push_back(p);
		m += p.first;
	}
	r.rle.push_back(make_pair(height-1-i, 0));
	r.at1 = r.at2 = 0;
}

struct Output {
	int curLen, curSym;
	bool first;

	Output() : curLen(0), curSym(0), first(true) { }

	void write(int len, int sym) {
		if (sym != curSym) {
			flush();
			curLen = 0;
			curSym = sym;
		}
		curLen += len;
	}

	void flush() {
		if (curLen != 0) {
			printf(first ? "%d %d" : " %d %d", curLen, curSym);
			first = false;
		}
	}

	~Output() {
		flush();
		printf("\n");
	}
};

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &width, &height);
		assert(height <= 1000);

		for (int i = 0; i < height; i++) {
			readRow(i);
		}

		Output out;
		for (int at = 0; at < height + width - 1; ) {
			int m = 0x3fffffff;
			int sum = 0;

			for (int i = 0; i < height; i++) {
				Pair p = row[i].next();
				m = min(m, p.first);
				sum += p.second;
			}

			out.write(m, sum);

			for (int i = 0; i < height; i++) {
				row[i].skip(m);
			}
			at += m;
		}
	}
}
