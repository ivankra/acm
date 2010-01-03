#include <stdio.h>

typedef struct { double x, y, z; } pt;

int main()
{
	static pt S[128], T[128];
	int i, j, k, m, r;
	double a;

	while (scanf("%d %d", &k, &m) == 2 && k) {
		for (i = 0; i < k; i++)
			scanf("%lf %lf %lf", &S[i].x, &S[i].y, &S[i].z);

		for (j = 0; j < m; j++)
			scanf("%lf %lf %lf", &T[j].x, &T[j].y, &T[j].z);

		for (j = r = 0; j < m; j++) {
			for (i = 0; i < k; i++) {
				a = T[j].x * (S[i].x - T[j].x);
				a += T[j].y * (S[i].y - T[j].y);
				a += T[j].z * (S[i].z - T[j].z);
				if (a > -1e-8) { r++; break; }
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
