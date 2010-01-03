#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

struct Monkey {
	int v, a, b;
	char flag[50010];
} mon[110];
int N, M;

int main() {
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		assert(N <= 101 && M <= 5);

		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &mon[i].v, &mon[i].a, &mon[i].b);
			assert(0 <= mon[i].a && mon[i].a < mon[i].b && mon[i].b <= 50001);
			mon[i].b--;
			memset(mon[i].flag, 3, sizeof(mon[i].flag));
			for (int j = mon[i].a; j <= mon[i].b; j++) mon[i].flag[j] = 0;
		}

		for (int t = 0; t <= 50001; t++) {
			for (int k = 0; k < M; k++) {
				int best = -1;
				for (int i = 0; i < N; i++) {
					if (mon[i].flag[t] == 0 && mon[i].v > 0) {
						if (best < 0 || mon[i].b < mon[best].b) {
							best = i;
						}
					}
				}
				if (best < 0) break;

				mon[best].flag[t] = 1;
				mon[best].v--;
			}
		}

		bool okay = true;
		for (int i = 0; i < N; i++)
			okay &= (mon[i].v == 0);

		if (!okay) {
			printf("Case %d: No\n", cs);
			continue;
		}

		printf("Case %d: Yes\n", cs);
		for (int i = 0; i < N; i++) {
			int cnt = 0;
			for (int j = 0; j <= 50001; j++) {
				if (mon[i].flag[j] != 1) continue;
				cnt++;
				while (mon[i].flag[++j] == 1);
			}
			printf("%d", cnt);
			for (int j = 0; j <= 50001; j++) {
				if (mon[i].flag[j] != 1) continue;
				printf(" (%d,", j);
				while (mon[i].flag[++j] == 1);
				printf("%d)", j);
			}
			printf("\n");
		}
	}
}
