#include <stdio.h>
#include <string.h>

#define SET(n) r[(n) >> 3] |= (1 << ((n) & 7))
#define GET(n) ((r[(n) >> 3] >> ((n) & 7)) & 1)
static unsigned char r[6272];

int main()
{
	static int t, m, s, a;
	register int i, j;

	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d", &m);

		memset(r, '\0', sizeof(r));
		SET(0);

		for (s = 0; m-- > 0;) {
			scanf("%d", &a);
			for (i = s; i > 0; i--)
				if (GET(i)) SET(i + a);
			SET(a);
			s += a;
		}

		for (i = (s & 1); i <= s; i += 2) {
			j = (s - i) >> 1;
			if (GET(j)) break;
		}

		printf("%d\n", i);
	}

	return 0;
}
