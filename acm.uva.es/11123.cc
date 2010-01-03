#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &p) const { return x < p.x || (x == p.x && y < p.y); }
	bool operator ==(const Point &p) const { return x == p.x && y == p.y; }
};

long long cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(long long)(b.y-o.y) - (a.y-o.y)*(long long)(b.x-o.x);
}

struct Line {
	long long dx, dy, cnt;

	bool operator <(const Line &l) const {
		if (dx == 0 || l.dx == 0)
			return dx == 0 && l.dx != 0;
		return dy*l.dx < l.dy*dx;
	}
};

Point P[256];
int N;

long long C2(long long n) { return n*(n-1)/2; }

void makeLines(vector<Line> &output) {
	static char flag[256][256];
	memset(flag, 0, sizeof(flag));

	output.clear();
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (flag[i][j]) continue;

			static int v[256];
			int c = 0;

			for (int k = 0; k < N; k++)
				if (cross(P[i], P[j], P[k]) == 0) v[c++] = k;

			for (int k = 0; k < c; k++)
				for (int m = 0; m < c; m++)
					flag[v[k]][v[m]] = 1;

			Line l;
			l.dx = P[j].x - P[i].x;
			l.dy = P[j].y - P[i].y;
			if (l.dx < 0) { l.dx = -l.dx; l.dy = -l.dy; }
			l.cnt = c;
			output.push_back(l);
		}
	}

	sort(output.begin(), output.end());
}


long long solve() {
	sort(P, P+N);
	for (int i = 1; i < N; i++) assert(P[i].x != P[i-1].x || P[i].y != P[i-1].y);

	vector<Line> lines;
	makeLines(lines);
	int L = lines.size();

	long long fancy = 0;
	for (int a = 0, b; a < L; a = b) {
		for (b = a; b < L && !(lines[a] < lines[b]); b++);

		long long t = 0;
		for (int i = a; i < b; i++)
			t += C2(lines[i].cnt);

		for (int i = a; i < b; i++) {
			fancy += C2(lines[i].cnt) * t;
			fancy -= C2(lines[i].cnt) * C2(lines[i].cnt);
		}
	}
	fancy /= 2;

	long long paral = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			for (int k = j+1, m = j+1; k < N; k++) {
				if (cross(P[i], P[j], P[k]) == 0) continue;

				Point p;
				p.x = P[i].x + (P[j].x-P[i].x) + (P[k].x-P[i].x);
				p.y = P[i].y + (P[j].y-P[i].y) + (P[k].y-P[i].y);

				if (m <= k) m = k+1;

				while (m < N && P[m] < p) m++;
				if (m == N) break;
				if (P[m] == p) paral++;
			}
		}
	}

	return fancy - 2*paral;
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) scanf(" %d %d", &P[i].x, &P[i].y);
		printf("Case %d: %lld\n", cs, solve());
	}
}
