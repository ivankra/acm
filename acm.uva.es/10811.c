#include <stdio.h>
#include <string.h>

#define EV(profit, nextbet) (event[(profit) + 4096][nextbet])
#define EVNEXT(profit, nextbet) (evnext[(profit) + 4096][nextbet])

double event[8192][16], evnext[8192][16];

int main()
{
	int rmin, rmax, hlim, i, j, m, b, r, t;
	double s;

	for (scanf("%d", &t); t-- > 0;) {
		scanf("%d %d %d", &rmin, &rmax, &hlim);

		for (i = -3100; i < 3100; i++)
			for (j = 0; j < 10; j++)
				EV(i, j) = 0.;

		EV(0, 0) = 1.;

		for (s = 0., r = 1; r <= rmax; r++) {
			for (i = -3100; i < 3100; i++)
				for (j = 0; j < 10; j++)
					EVNEXT(i, j) = 0.;

			for (m = -3100; m < 3100; m++) {
				for (b = 0; b < 10; b++) {
					if (EV(m, b) == 0.)
						continue;

					EVNEXT(
						m - (1 << b),
						((1 << (b + 1)) > hlim) ? 0 : (b + 1)
					) += EV(m, b) * 5. / 7.;

					EVNEXT(m + (1 << b), 0) += EV(m, b) / 7.;
					EVNEXT(m + 2 * (1 << b), 0) += EV(m, b) / 14.;
					EVNEXT(m + 3 * (1 << b), 0) += EV(m, b) / 14.;
				}
			}

			memcpy(event, evnext, sizeof(evnext));

			if (r < rmin)
				continue;

			for (m = 1; m < 3100; m++) {
				for (b = 0; b < 10; b++) {
					s += EV(m, b);
					EV(m, b) = 0.;
				}
			}
		}

		printf("%.4f\n", s);
	}

	return 0;
}
