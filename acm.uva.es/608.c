#include <stdio.h>
#include <string.h>

struct {
	int a[16], b[16], r;
} w[3];

int test(int c, int m)
{
	int i, j, s, t;

	for (i = 0; i < 3; i++) {
		for (s = 0, j = 0; w[i].a[j] >= 0; j++)
			if (w[i].a[j] == c) s += m;

		for (t = 0, j = 0; w[i].b[j] >= 0; j++)
			if (w[i].b[j] == c) t += m;

		if (s < t && w[i].r >= 0) return 0;
		if (s > t && w[i].r <= 0) return 0;
		if (s == t && w[i].r != 0) return 0;
	}

	return 1;
}

int main()
{
	char s[1024], t[1024], u[1024], *p;
	int i, j, n;

	for (scanf("%d", &n); n-- > 0;) {
		for (i = 0; i < 3; i++) {
			scanf(" %[A-L] %[A-L] %[a-z]", s, t, u);

			for (p = s, j = 0; *p;)
				w[i].a[j++] = *p++ - 'A';
			w[i].a[j] = -1;

			for (p = t, j = 0; *p;)
				w[i].b[j++] = *p++ - 'A';
			w[i].b[j] = -1;

			w[i].r = ((u[0] == 'e') ? 0 : ((u[0] == 'u') ? 1 : -1));
		}


		for (i = 0; i < 12; i++) {
			if (test(i, -1)) {
				printf("%c is the counterfeit coin and it is light.\n", i + 'A');
				break;
			} else if (test(i, 1)) {
				printf("%c is the counterfeit coin and it is heavy.\n", i + 'A');
				break;
			}
		}
	}

	return 0;
}
