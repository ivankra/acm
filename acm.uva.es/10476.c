#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXTRIG 1048576

struct {
	unsigned t;
	int f[3];
} trig[MAXTRIG];

int ntrig;

int find(unsigned t)
{
	int i;

	for (i = 0; i < ntrig; i++)
		if (trig[i].t == t) return i;

	i = ntrig++;
	trig[i].t = t;
	trig[i].f[0] = trig[i].f[1] = trig[i].f[2] = 0;
	return i;
}

void readmsg(int w)
{
	static char buf[4096];
	int i, j, m;

	while (gets(buf) && strcmp(buf, "ENDMESSAGE") != 0) {
		m = strlen(buf) - 2;

		for (i = 0; i < m; i++) {
			j = find(
				((unsigned)buf[i] << 16) |
				((unsigned)buf[i + 1] << 8) |
				(unsigned)buf[i + 2]
			);

			trig[j].f[w]++;
		}
	}
}

double sim(int a, int b)
{
	double u, v, t;
	int i;

	u = v = t = 0.;

	for (i = 0; i < ntrig; i++) {
		t += (double)trig[i].f[a] * (double)trig[i].f[b];
		u += (double)trig[i].f[a] * (double)trig[i].f[a];
		v += (double)trig[i].f[b] * (double)trig[i].f[b];
	}

	return t / sqrt(u * v);
}

int main()
{
	static char buf[4096];
	int i, c, n, s, t;
	double u, v;

	for (t = 0; gets(buf);) {
		if (sscanf(buf, "%d %d %d", &s, &n, &c) != 3) continue;

		if (s == 0 && n == 0 && c == 0)
			break;

		printf("Set %d:\n", ++t);

		for (ntrig = 0; s-- > 0;)
			readmsg(0);

		while (n-- > 0)
			readmsg(1);

		while (c-- > 0) {
			for (i = 0; i < ntrig; i++)
				trig[i].f[2] = 0;

			readmsg(2);

			u = sim(0, 2);
			v = sim(1, 2);

			printf("%.5f %.5f\n%s\n",
				u, v, (u > v) ? "spam" : "non-spam");
		}
	}

	return 0;
}
