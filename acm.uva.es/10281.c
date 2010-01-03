#include <stdio.h>

int main()
{
	static char buf[1024];
	static double dist, vel, nvel, r;
	static int i, t0, t1, th, tm, ts;

	dist = 0.;	/* distance travelled at t0 */
	vel = 0.;	/* current valocity (after t0) */
	t0 = 0;		/* time of last valocity change */

	while (gets(buf)) {
		i = sscanf(buf, "%d:%d:%d %lf", &th, &tm, &ts, &nvel);
		if (i < 3) continue;

		t1 = th * 3600 + tm * 60 + ts;

		if (i == 3) {
			r = dist + vel * (double)(t1 - t0) / 3600.;
			printf("%.2d:%.2d:%.2d %.2f km\n", th, tm, ts, r);
		} else {
			dist += vel * (double)(t1 - t0) / 3600.;
			vel = nvel;
			t0 = t1;
		}
	}

	return 0;
}
