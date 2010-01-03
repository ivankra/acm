#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef struct { double x,y,z; } vec;

vec cross(vec a, vec b)
{
	vec c = { a.y*b.z-a.z*b.y, a.x*b.z-a.z*b.x, a.x*b.y-a.y*b.x };
	return c;
}

double dot(vec a, vec b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
double len(vec a) { return sqrt(dot(a,a)); }

int main()
{
	vec p[1030], m;
	double r;
	int i, n;

	while (scanf("%d", &n) == 1 && n != 0) {
		assert(3 <= n && n <= 1024);

		for (i = 0; i < n; i++)
			scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
		p[n] = p[0];
		p[n+1] = p[1];

		for (i = n+1; i >= 0; i--)
			p[i].x -= p[0].x, p[i].y -= p[0].y, p[i].z -= p[0].z;

		m.x = m.y = m.z = r = 0.;
		for (i = 0; i <= n; i++)
			if (len(cross(p[i], p[i+1])) > r)
				r = len(m = cross(p[i], p[i+1]));
		if (r < 1e-8) { printf("0.000\n"); continue; }
		m.x /= r; m.y /= r; m.z /= r;

		for (r = 0., i = 0; i < n; i++)
			r += dot(cross(p[i], p[i+1]), m);

		printf("%.3f\n", fabs(r) / 2. + 1e-9);
	}

	return 0;
}
