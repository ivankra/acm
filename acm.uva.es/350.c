#include <stdio.h>
#include <memory.h>

int main()
{
	static int a, b, m, s, t, i;
	static int w[10001];

	for (t = 1; scanf("%d %d %d %d", &a, &b, &m, &s) == 4; t++) {
		if (a == 0 && b == 0 && m == 0 && s == 0)
			break;

		memset(w, 0, sizeof(w));

		for (i = 1;; i++) {
			w[s] = i;
			s = (a * s + b) % m;
			if (w[s])
				break;
		}

		printf("Case %d: %d\n", t, i - w[s] + 1);
	}

	return 0;
}
