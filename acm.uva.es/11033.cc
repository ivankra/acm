#include <cstdio>
#include <cstring>

int sum, mod, modp;

int solve() {
	int cnt = 0;
	char sol[2][256];

	if (sum < 4 || sum > 28 || modp < 0) return 1;

	for (int a0 = 1; a0 <= 7; a0++)
	for (int a1 = 1; a1 <= 7; a1++)
	for (int a2 = 1; a2 <= 7; a2++) {
		int a3 = sum - a0 - a1 - a2;
		if (a3 < 1 || a3 > 7) continue;

		int pa = (a0 * a1 * a2 * a3) % mod;

		for (int b0 = 1; b0 <= 7; b0++)
		for (int b1 = 1; b1 <= 7; b1++)
		for (int b2 = 1; b2 <= 7; b2++) {
			int b3 = sum - b0 - b1 - b2;
			if (b3 < 1 || b3 > 7) continue;

			int pab = (pa * b0 * b1 * b2 * b3) % mod;

			for (int c0 = 1; c0 <= 7; c0++) {
				int d0 = sum - a0 - b0 - c0;
				if (d0 < 1 || d0 > 7) continue;

				int p0 = (pab * c0 * d0) % mod;

				for (int c1 = 1; c1 <= 7; c1++) {
					int d1 = sum - a1 - b1 - c1;
					if (d1 < 1 || d1 > 7) continue;
					if (d0 != sum - a3 - b2 - c1) continue;

					int p1 = (p0 * c1 * d1) % mod;

					for (int c2 = 1; c2 <= 7; c2++) {
						int d2 = sum - a2 - b2 - c2;
						if (d2 < 1 || d2 > 7) continue;

						int c3 = sum - c0 - c1 - c2;
						if (c3 < 1 || c3 > 7) continue;

						int d3 = sum - a3 - b3 - c3;
						if (d3 < 1 || d3 > 7) continue;
						if (d3 != sum-a0-b1-c2) continue;

						int prod = (p1*c2*d2*c3*d3) % mod;
						if (prod > modp) continue;

						if (cnt < 2) {
							sprintf(sol[cnt],
								"%d%d%d%d\n"
								"%d%d%d%d\n"
								"%d%d%d%d\n"
								"%d%d%d%d\n"
								"....\n",
								a0, a1, a2, a3,
								b0, b1, b2, b3,
								c0, c1, c2, c3,
								d0, d1, d2, d3);
						}

						cnt++;
					}
				}
			}
		}
	}

	printf("%d\n", cnt);
	for (int i = 0; i < cnt && i < 2; i++)
		printf("%s", sol[i]);
	return 0;
}

int main() {
	for (int cs=1; scanf("%d%d%d", &sum, &mod, &modp) == 3 && mod>0; cs++) {
		printf("Set %d:\n", cs);
		if (solve()) printf("0\n");
	}
}
