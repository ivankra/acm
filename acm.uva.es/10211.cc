#include <cstdio>
#include <cassert>

int main()
{
	int T, B, D;
	scanf("%d", &T);

	while (T-- > 0 && scanf("%d %d", &B, &D) == 2) {
		assert(2 <= B && B <= 500 && 2 <= D && D <= 5000);

		int found = 0;
		for (int step = 0; step < 3; step++) {
			int z; char *fmt;

			if (step == 0)
				z = 0, fmt = "Rightmost %d\n";
			else if (step == 1)
				z = 1, fmt = "Add all %d\n";
			else
				z = D-1, fmt = "Alternate %d change sign\n";

			for (int r = 1, x = 1; r <= D+10; r++) {
				if (step > 0 && r > 1000) break;
				x = (x * B) % D;
				if (x == z) {
					found++;
					printf(fmt, r);
					break;
				}
			}
		}

		if (found == 0) printf("condition not found.\n");
		if (T > 0) printf("\n");
	}
}
