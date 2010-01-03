#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long int64;

int N, W, H;

struct Rect {
	int x1, y1, x2, y2, up;
	int64 area, visible;
} R[65536];

struct Event {
	int x, id, flag;
	Event(int X, int ID, int F) : x(X), id(ID), flag(F) {}
	bool operator <(const Event &other) const {
		if (x != other.x) return x < other.x;
		return flag < other.flag;
	}
};

struct Segment {
	int id;
	Segment(int ID) : id(ID) {}
	bool operator <(const Segment &other) const {
		return R[id].y1 < R[other.id].y1;
	}
};

struct Segment2 {
	int id;
	Segment(int ID) : id(ID) {}
	bool operator <(const Segment &other) const {
		return R[id].y1 < R[other.id].y1;
	}
};

int main() {
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d %d %d", &N, &W, &H);

	R[0].x1 = 0; R[0].x2 = W;
	R[0].y1 = 0; R[0].y2 = H;
	for (int i = 1; i <= N; i++) {
		Rect &r = R[i];
		scanf("%d %d %d %d", &r.x1, &r.y1, &r.x2, &r.y2);
	}

	vector<Event> eq;
	for (int i = 0; i <= N; i++) {
		Rect &r = R[i];
		if (r.x1 > r.x2) swap(r.x1, r.x2);
		if (r.y1 > r.y2) swap(r.y1, r.y2);

		r.area = (int64)r.x2 - (int64)r.x1;
		r.area *= (int64)r.y2 - (int64)r.y1;
		r.visible = r.area;
		r.up = -1;

		if (i > 0) {
			eq.push_back(Event(r.x1, i, +1));
			eq.push_back(Event(r.x2, i, -1));
		}
	}
	sort(eq.begin(), eq.end());

	set<Segment> sweep, sweep2;
	sweep.insert(Segment(0));
	sweep.insert(Segment2(0));

	for (int i = 0; i < (int)eq.size(); i++) {
		Event &e = eq[i];
printf("event: x=%d id=%d flag=%d\n", e.x, e.id, e.flag);fflush(stdout);

		if (e.flag == +1) {
			set<Segment>::iterator it = sweep.insert(Segment(e.id)).first;
			it--;
			int up = it->id;

printf("  parent of #%d (%d,%d-%d,%d): #%d\n",
	   e.id, R[e.id].x1, R[e.id].y1, R[e.id].x2, R[e.id].y2,
	   up);

			R[e.id].up = up;
			R[up].visible -= R[e.id].area;
		} else {
			sweep.erase(Segment(e.id));
		}
	}
printf("done\n");

	vector<int64> out;
	for (int i = 0; i <= N; i++)
		out.push_back(R[i].visible);
	sort(out.begin(), out.end());

	for (int i = 0; i < (int)out.size(); i++)
		printf(i==0 ? "%lld" : " %lld", out[i]);
	printf("\n");

	return 0;
}