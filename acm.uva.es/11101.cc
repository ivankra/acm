#include <cstdio>
#include <cstring>

short Dist[2001][2048];
int Queue[2000*2000+10], *Head, *Tail;

int main() {
	int N, x, y;
	while (scanf("%d", &N) == 1 && N > 0) {
		memset(Dist, 0xff, sizeof(Dist));
		Head = Tail = Queue;
		while (N-- > 0 && scanf("%d %d", &x, &y) == 2) {
			Dist[x][y] = 0;
			*Tail++ = (x<<16)+y;
		}

		scanf("%d", &N);
		while (N-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (Dist[x][y] == 0) {
				printf("0\n");
				goto done;
			}
			Dist[x][y] = -2;
		}

		for (; Head < Tail; Head++) {
			int x0 = ((*Head) >> 16);
			int y0 = ((*Head) & 0xFFFF);
			for (int d = 0; d < 4; d++) {
				x = x0 + "0211"[d] - '1';
				y = y0 + "1102"[d] - '1';
				if (x < 0 || y < 0 || x > 2000 || y > 2000)
					continue;

				if (Dist[x][y] >= 0)
					continue;

				if (Dist[x][y] == -2) {
					printf("%d\n", Dist[x0][y0] + 1);
					goto done;
				}
				Dist[x][y] = Dist[x0][y0] + 1;
				*Tail++ = (x << 16) + y;
			}
		}
done:;
	}
}
