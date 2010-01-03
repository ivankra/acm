#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define GET(array, k) ((array[(k)>>3] >> ((k)&7)) & 1)
#define SET(array, k) array[(k)>>3] |= 1U << ((k)&7)
unsigned char seen1[(1<<21)+10], seen2[(1<<21)+10];

int encode(int a[]) { return a[0]|(a[1]<<6)|(a[2]<<12)|(a[3]<<18); }

void decode(int a[], int x) {
	a[0] = x & 0x3f; x >>= 6;
	a[1] = x & 0x3f; x >>= 6;
	a[2] = x & 0x3f;
	a[3] = x >> 6;
}

int read() {
	int a[4], y, x;
	for (int i = 0; i < 4; i++) {
		int t = scanf("%d %d", &y, &x);
		assert(t == 2 && 1 <= y && y <= 8 && 1 <= x && x <= 8);
		a[i] = (y-1)*8 + x-1;
	}
	sort(a, a+4);
	for (int i = 0; i < 3; i++)
		assert(a[i] != a[i+1]);
	return encode(a);
}

int moveok(int y, int x, int a[]) {
	if (y < 0 || y >= 8 || x < 0 || x >= 8) return 0;
	int t = y*8+x;
	return a[0]!=t && a[1]!=t && a[2]!=t && a[3]!=t;
}

// Marks all states rechable from the 'start' state in at most 4 moves.
void bfs(int start, unsigned char *seen) {
	static int buf[64*63*62*61/24+10];

	int *qhead=buf, *qmid=buf+1, *qtail=buf+1;
	buf[0] = start;

	for (int dist = 0; dist <= 3;) {
		if (qhead == qmid) {
			if (qmid == qtail) break;
			qmid = qtail;
			dist++;
		}

		int s = *qhead++;
		SET(seen, s);

		int a[4];
		decode(a, s);

		for (int i = 0; i < 4; i++) {
			int y0=a[i]>>3, x0=a[i]&7;
			for (int dir = 0; dir < 4; dir++) {
				int dx = "0211"[dir] - '1';
				int dy = "1102"[dir] - '1';

				int y1=y0+dy, x1=x0+dx;
				if (!moveok(y1, x1, a)) { y1 += dy; x1 += dx; }
				if (!moveok(y1, x1, a)) continue;

				int b[4] = { a[0], a[1], a[2], a[3] };
				b[i] = y1 * 8 + x1;
				sort(b, b+4);
				int t = encode(b);

				if (GET(seen, t)) continue;
				SET(seen, t);

				*qtail++ = t;
			}
		}
	}
}

int main() {
	int T;
	for (scanf("%d", &T); T-- > 0;) {
		memset(seen1, 0, sizeof(seen1));
		bfs(read(), seen1);

		memset(seen2, 0, sizeof(seen2));
		bfs(read(), seen2);

		// check, if there's at a state, reachable both from
		// starting and goal states in at most 4 moves.
		int okay = 0;
		for (int i = 0; i < (int)sizeof(seen1); i++)
			if ((seen1[i] & seen2[i]) != 0) { okay = 1; break; }

		printf(okay ? "YES\n" : "NO\n");
		if (T > 0) printf("\n");
	}
}
