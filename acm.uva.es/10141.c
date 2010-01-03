#include <stdio.h>

int main()
{
	static char s1[4096], s2[4096], r[4096];
	double c, rc;
	int i, k, n, p, t, rk;

	for (t = 1; gets(s1) && sscanf(s1, "%d %d", &n, &p) == 2 && n > 0; t++) {
		for (i = 0; i < n; i++)
			gets(s1);

		for (i = 0; i < p; i++) {
			gets(s1);

			gets(s2);
			sscanf(s2, "%lf %d", &c, &k);

			if (i == 0 || k > rk || (k == rk && c < rc)) {
				rk = k;
				rc = c;
				strcpy(r, s1);
			}

			while (k-- > 0)
				gets(s1);
		}

		printf("%sRFP #%d\n%s\n", (t == 1) ? "" : "\n", t, r);
	}

	return 0;
}
