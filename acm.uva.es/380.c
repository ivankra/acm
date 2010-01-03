#include <stdio.h>
#include <string.h>

struct {
	int x, y, t1, t2, d;
} req[128];

int nreq;

int get(int s, int t)
{
	static int list[4096];
	int i, k, x;

	list[0] = s;
	k = 1;

	for (x = s;;) {
		for (i = 0; i < nreq; i++)
			if (req[i].x == x && req[i].t1 <= t && t <= req[i].t2)
				break;

		if (i >= nreq)
			return x;

		x = req[i].y;

		for (i = 0; i < k; i++)
			if (list[i] == x) return 9999;

		list[k++] = x;
	}
}

int main()
{
	int c, r, t, x;

	printf("CALL FORWARDING OUTPUT\n");
	for (scanf("%d", &r), c = 1; c <= r; c++) {
		printf("SYSTEM %d\n", c);

		for (nreq = 0; scanf("%d", &req[nreq].x) == 1 && req[nreq].x > 0; nreq++) {
			scanf("%d %d %d", &req[nreq].t1, &req[nreq].d, &req[nreq].y);
			req[nreq].t2 = req[nreq].t1 + req[nreq].d;
		}

		while (scanf("%d", &t) == 1 && t < 9000) {
			scanf("%d", &x);
			printf("AT %.4d CALL TO %.4d RINGS %.4d\n",
				t, x, get(x, t));
		}
	}

	printf("END OF OUTPUT\n");
	return 0;
}

