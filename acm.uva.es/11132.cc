#include <cstdio>
#include <cstring>

int main() {
	int rolls, sides;
	char s[10000];

	while (scanf(" %d D %d %s", &rolls, &sides, s) == 3) {
		if (rolls == 0 && sides == 0) break;

		int res = 0, m = 0;
		int n = strlen(s);

		int w = 0;
		for (w = 0;; w++)
			if ((1 << w) >= sides) break;

		for (int i = 0; m < rolls && i+w <= n; i += w) {
			int k = 0;
			for (int j = 0; j < w; j++)
				k = k*2 + (s[i+j] == 'H' ? 0 : 1);
			if (k >= sides) continue;

			res += k+1;
			m++;
		}

		if (m != rolls)
			printf("-1\n");
		else
			printf("%d\n", res);
	}
}
