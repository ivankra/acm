#include <cstdio>

#define MAX 100100

int sib[MAX], kid[MAX], count = 0;
int alpha[MAX];

int main() {
	int n, m;
	while (scanf("%d", &n) == 1 && n > 0) {
		count = 0;
		sib[0] = kid[0] = alpha[0] = 0;

		while (n-- > 0 && scanf("%d", &m) == 1) {
			int path[100];
			char s[100];
			for (int i = 0; i < m && scanf(" %s", s) == 1; i++) {
				path[i] = 0;
				for (int j = 0; s[j]; j++)
					path[i] = path[i] * 128 + s[j];
			}

			for (int x = 0, i = m-1; i >= 0; i--) {
				int a = path[i], y;
				for (y = kid[x]; y != 0; y = sib[y])
					if (alpha[y] == a) break;
				if (y == 0) {
					y = ++count;
					sib[y] = kid[x];
					kid[x] = y;
					alpha[y] = a;
					kid[y] = 0;
				}
				x = y;
			}
		}

		printf("%d\n", count);
	}
}
