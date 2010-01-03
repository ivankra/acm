#include <cstdio>
#include <cmath>
#define EPS 1e-10

struct pt { double x, y; };

struct { pt v; char *s; } dir[] = {	
	{ {0,1}, "north" }, { {0,-1}, "south" }, { {1,0}, "east" },
	{ {-1,0}, "west" }, { {1,1}, "northeast" }, { {1,-1}, "southeast" },
	{ {-1,1}, "northwest" }, { {-1,-1}, "southwest" }
};

void solve(pt a, pt b, double r)
{
	pt c={b.x-a.x,b.y-a.y};
	double best=1e99, t;
	char out[1024];

	if (fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS) {
		printf("north %.10f\n", (double)0.);
		return;
	}	

	for (int i = 0; i < 8; i++) {
		pt d = dir[i].v;
		if (fabs(c.x*d.y-c.y*d.x) > EPS) continue;
		if (fabs(c.x-d.x) > fabs(c.y-d.y)) t=c.x/d.x; else t=c.y/d.y;
		printf("%s %.10f\n", dir[i].s, t);
		return;
	}

	out[0] = 0;
	for (int i = 0; i < 8; i++) {
		pt d1 = dir[i].v;
		for (int j = 0; j < 8; j++) {
			if (i == j) continue;
			pt d2 = dir[j].v;

			double d = d1.x * d2.y - d2.x * d1.y;
			if (fabs(d) < EPS) continue;

			double s = (c.x * d2.y - d2.x * c.y) / d;
			double t = (d1.x * c.y - c.x * d1.y) / d;
			if (s < -EPS || t < -EPS || s+t+EPS > best) continue;

			pt p={a.x+s*d1.x,a.y+s*d1.y};
			if (p.x*p.x + p.y*p.y > r*r+EPS) continue;

			best = s + t;
			sprintf(out, "%s %.10f\n%s %.10f\n",
				dir[i].s, s, dir[j].s, t);
		}
	}

	printf("%s", out);
}

int main()
{
	double r;
	pt a, b;

	for (int i = 0; i < 8; i++) {
		r = sqrt(dir[i].v.x * dir[i].v.x + dir[i].v.y * dir[i].v.y);
		dir[i].v.x /= r; dir[i].v.y /= r;
	}	
		
	for (int t = 0; scanf("%lf", &r) == 1 && r > 1e-9; t++) {
		if (t) printf("\n");
		scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
		solve(a, b, r);
	}

	return 0;
}
