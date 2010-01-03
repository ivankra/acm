#include <stdio.h>
#include <math.h>

int main()
{
	static int x[128], y[128], z[128], v[128];
	int i, k, f, b, r, n, t, sx, sy, sz, next, next_dist2;
	double sfuel, strav, stime, reqdist, reqfuel, reqtime;
	double strav_stop;
	double u, tx, ty, tz;

	for (t = 1; scanf("%d %d %d %d", &f, &b, &r, &n) == 4; t++) {
		if (f == 0 && b == 0 && r == 0 && n == 0)
			break;

		for (i = 0; i < n; i++)
			scanf("%d %d %d", &x[i], &y[i], &z[i]);

		for (i = 0; i < n; i++)
			v[i] = 0;

		sx = 0; sy = 0; sz = 1;
		sfuel = (double)f;
		strav = 0.;
		strav_stop = 0.;
		stime = 0.;

		next = 0;
		reqfuel = 0.;

		for (;;) {
			for (i = 0; i < n; i++)
				if (x[i] == sx && y[i] == sy && z[i] == sz)
					v[i] = 1;

			for (next = next_dist2 = -1, i = 0; i < n; i++) {
				if (v[i]) continue;

				k = ((x[i] - sx) * (x[i] - sx) +
				     (y[i] - sy) * (y[i] - sy) +
				     (z[i] - sz) * (z[i] - sz));

				if (next < 0 || k < next_dist2) {
					next = i;
					next_dist2 = k;
				}
			}

			if (next < 0)
				break;

			reqdist = sqrt((double)next_dist2);
			reqtime = reqdist / (double)r;
			reqfuel = reqtime * (double)b;

			if (sfuel < 0.) {
				strav += reqdist;
			} else if (reqfuel < (sfuel + 10e-9)) {
				sfuel -= reqfuel;
				if (sfuel < 0.) sfuel = 0.;
				strav += reqdist;
				stime += reqtime;
			} else {
				u = sfuel / reqfuel;

				tx = (double)sx + u * (double)(x[next] - sx);
				ty = (double)sy + u * (double)(y[next] - sy);
				tz = (double)sz + u * (double)(z[next] - sz);

				strav_stop = strav + u * reqdist;

				strav += reqdist;

				sfuel = -1.;
			}

			sx = x[next];
			sy = y[next];
			sz = z[next];
		}

		if (sfuel >= 0.) {
			printf("Mission %d: SUCCESS!! Time: %.2f  "
			       "Traveled: %.2f  Fuel Left: %.2f\n",
			       t, stime, strav, sfuel);
		} else {
			printf("Mission %d: FAILURE!! "
			       "Traveled: %.2f  From Home: %.2f\n",
			       t, strav_stop, strav - strav_stop);
		}
	}

	return 0;
}
