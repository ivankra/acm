/*
ID: infnty1
PROB: window
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;

struct Window {
	int visible, z;
	int x1, y1, x2, y2;
} wnd[256];

#define dprintf printf

double solve(int id) {
	if (!wnd[id].visible) return 0.0;

	for (int i = 0; i < 128; i++) {
		if (wnd[i].visible) {
			if (wnd[i].x1 > wnd[i].x2) swap(wnd[i].x1, wnd[i].x2);
			if (wnd[i].y1 > wnd[i].y2) swap(wnd[i].y1, wnd[i].y2);
		}
	}

	vector<int> xs;
	for (int i = 0; i < 128; i++) {
		if (wnd[i].visible && wnd[i].z <= wnd[id].z) {
			xs.push_back(wnd[i].x1);
			xs.push_back(wnd[i].x2);
		}
	}

	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());

	double hidden = 0;

	for (int i = 1; i < (int)xs.size(); i++) {
		int x1 = xs[i-1], x2 = xs[i];
		if (x2 <= wnd[id].x1 || x1 >= wnd[id].x2) continue;

		vector<int> on, off;
		for (int j = 0; j < 128; j++) {
			Window &w = wnd[j];
			if (!w.visible || w.z >= wnd[id].z) continue;
			if (x2 <= w.x1 || x1 >= w.x2) continue;

			if (max(w.y1, w.y2) <= wnd[id].y1) continue;
			if (min(w.y1, w.y2) >= wnd[id].y2) continue;

			on.push_back(w.y1 >? wnd[id].y1);
			off.push_back(w.y2 <? wnd[id].y2);
		}

		sort(on.begin(), on.end());
		sort(off.begin(), off.end());

		int m = on.size(), y = wnd[id].y1, c = 0;

		for (int i = 0, j = 0;;) {
			while (i < m && on[i] == y) { c++; i++; }
			while (j < m && off[j] == y) { c--; j++; }
			if (i >= m && j >= m) break;

			int y1 = 1<<30;
			if (i < m) y1 = on[i];
			if (j < m) y1 <?= off[j];

			if (c > 0)
				hidden += (x2-x1)*(double)(y1-y);
			y = y1;
		}
	}

	double all = (wnd[id].x2 - wnd[id].x1) * (double)(wnd[id].y2 - wnd[id].y1);
	return 1-hidden/all;
}

void top(int id) {
	wnd[id].z = 0;
	for (int i = 0; i < 128; i++)
		if (wnd[i].visible && i!=id) wnd[id].z <?= wnd[i].z - 1;
}

int main() {
	freopen("window.in", "r", stdin);
	freopen("window.out", "w", stdout);

	for (int i = 0; i < 128; i++)
		wnd[i].visible = wnd[i].z = 0;

	char cmd, id_c;
	while (scanf(" %c ( %c ", &cmd, &id_c) == 2) {
		int id = id_c;
		Window &w = wnd[id];
		cmd = tolower(cmd);

		if (cmd == 'w') {
			scanf(" , %d , %d , %d , %d",
				&w.x1, &w.y1, &w.x2, &w.y2);
			w.visible = 1;
			top(id);
		} else if (cmd == 't') {
			top(id);
		} else if (cmd == 'b') {
			w.z = 0;
			for (int i = 0; i < 128; i++)
				if (wnd[i].visible && i!=id)
					w.z >?= wnd[i].z + 1;
		} else if (cmd == 'd') {
			w.visible = 0;
		} else if (cmd == 's') {
			printf("%.3f\n", solve(id)*100.0);
		}

		scanf(" ) ");
	}
}
