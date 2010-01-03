/*
ID: infnty1
PROB: spin
LANG: C++
*/
#include <cstdio>
#include <cstring>

struct Wheel {
	int v, m, ws[10], we[10];
} wh[5];

int main()
{
	freopen("spin.in", "r", stdin);
	freopen("spin.out", "w", stdout);

	for (int i = 0; i < 5; i++) {
		scanf("%d %d", &wh[i].v, &wh[i].m);
		for (int j = 0; j < (int)wh[i].m; j++)
			scanf("%d %d", &wh[i].ws[j], &wh[i].we[j]);
	}

	for (int t = 0; t < 10000; t++) {
		int v[360];
		memset(v, 0, sizeof(v));
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < (int)wh[i].m; j++) {
				int s = (wh[i].ws[j] + (t%360) * wh[i].v) % 360;
				for (int k = 0; k <= wh[i].we[j]; k++)
					v[(s+k)%360] |= 1 << i;
			}
		}

		for (int i = 0; i < 360; i++)
			if (v[i] == 31) { printf("%d\n", t); return 0; }
	}

	printf("none\n");
	return 0;
}
