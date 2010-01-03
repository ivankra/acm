#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define NSTATES (64*63*62*61/24)
int queue_buf[NSTATES+10], *qhead, *qmid, *qtail;

unsigned char seen[(1<<21)+10];
#define GET(array, k) ((array[(k)>>3] >> ((k)&7)) & 1)
#define SET(array, k) array[(k)>>3] |= 1U << ((k)&7)

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

int main() {
	int T;
	for (scanf("%d", &T); T-- > 0;) {
		int s_start = read();
		int s_goal = read();

		memset(seen, 0, sizeof(seen));

		qhead = qmid = qtail = queue_buf;
		*qtail++ = s_start;
		qmid = qtail;

		int okay = 1;
		for (int dist = 0; dist <= 7;) {
			if (qhead == qmid) {
				if (qmid == qtail) break;
				qmid = qtail;
				dist++;
			}

			int s = *qhead++;
			if (s == s_goal) goto yes;

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

					if (t == s_goal && dist+1 <= 8) goto yes;
					*qtail++ = t;
				}
			}
		}

		okay = 0;

yes:		printf(okay ? "YES\n" : "NO\n");
		if (T > 0) printf("\n");
	}
}
