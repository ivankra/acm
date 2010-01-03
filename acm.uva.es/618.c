#include <stdio.h>
#include <assert.h>

typedef struct {
	int w, h;
} rect;

rect R(int w, int h) { rect r; r.w = w; r.h = h; return r; }
rect F(rect r) { rect s; s.w = r.h; s.h = r.w; return s; }
int V(rect r) { return (r.w > 0 && r.h > 0); }

/* Fits two rectangles into given width.
   Returns the necessary height (unique), or -1 if impossible */
int fit2(rect a, rect b, int w)
{
	int x, y, d;

	assert(V(a) && V(b) && w > 0);

	/* a.w x + b.w y = w
	   a.h x = b.h y = h

	   x = w b.h / (a.w b.h + a.h b.w)
	   y = w a.h / (a.w b.h + a.h b.w) */

	x = w * b.h;
	y = w * a.h;
	d = a.w * b.h + a.h * b.w;

	if (((a.h * x) % d) != 0 || ((a.w * x) % d) != 0 ||
	    ((b.h * y) % d) != 0 || ((b.w * y) % d) != 0)
		return -1;

	return (a.h * x) / d;
}

int fit3y(rect a, rect b, rect c, rect z)
{
	int t;

	/* aaaaa
	   bbccc */
	if (((a.h * z.w) % a.w) == 0) {
		t = (a.h * z.w) / a.w;
		if (t <= z.h && fit2(b, c, z.w) == (z.h - t)) return 1;
	}

	/* aaa
	   bbb
	   ccc */
	if (((a.h * z.w) % a.w) == 0 && ((b.h * z.w) % b.w) == 0 &&
	    ((c.h * z.w) % c.w) == 0) {
		t = ((a.h * z.w) / a.w) + ((b.h * z.w) / b.w) + ((c.h * z.w) / c.w);
		if (t == z.h) return 1;
	}

	return 0;
}

int fit3x(rect a, rect b, rect c, rect z)
{
	return (fit3y(a, b, c, z) || fit3y(F(a), F(b), F(c), F(z)));
}

/* Fits a,b,c into z */
int fit3(rect a, rect b, rect c, rect z)
{
	assert(V(a) && V(b) && V(c) && V(z));
	return (fit3x(a, b, c, z) || fit3x(a, c, b, z) ||
		fit3x(b, a, c, z) || fit3x(b, c, a, z) ||
		fit3x(c, a, b, z) || fit3x(c, b, a, z));
}

int fit4z(rect a, rect b, rect c, rect d, rect z)
{
	int t, s;

	/* aaaa
	   .... */
	if (((a.h * z.w) % a.w) == 0) {
		t = (a.h * z.w) / a.w;
		if (t < z.h && fit3(b, c, d, R(z.w, z.h - t))) return 1;
	}

	/* a...
	   a... */
	if (((a.w * z.h) % a.h) == 0) {
		t = (a.w * z.h) / a.h;
		if (t < z.w && fit3(b, c, d, R(z.w - t, z.h))) return 1;
	}

	/* aaaabb
	   ccdddd */
	t = fit2(a, b, z.w);
	s = fit2(c, d, z.w);
	if (t > 0 && s > 0 && (s + t) == z.h) return 1;

	return 0;
}

int fit4y(rect a, rect b, rect c, rect d, rect z)
{
	return (fit4z(a, b, c, d, z) || fit4z(F(a), F(b), F(c), F(d), F(z)));
}

int fit4x(rect a, rect b, rect c, rect d, rect z)
{
	return (fit4y(a, b, c, d, z) || fit4y(a, b, d, c, z) ||
		fit4y(a, c, b, d, z) || fit4y(a, c, d, b, z) ||
		fit4y(a, d, b, c, z) || fit4y(a, d, c, b, z));
}

int fit4(rect a, rect b, rect c, rect d, rect z)
{
	assert(V(a) && V(b) && V(c) && V(d) && V(z));
	return (fit4x(a, b, c, d, z) || fit4x(b, a, c, d, z) ||
		fit4x(c, a, b, d, z) || fit4x(d, a, b, c, z));
}

int main()
{
	rect a, b, c, d, z;
	int t;

	for (t = 1; scanf("%d %d", &z.w, &z.h) == 2 && (z.w != 0 || z.h != 0); t++) {
		scanf("%d %d %d %d %d %d %d %d",
			&a.w, &a.h, &b.w, &b.h, &c.w, &c.h, &d.w, &d.h);
		printf("Set %d: %s\n", t, fit4(a,b,c,d,z) ? "Yes" : "No");
	}

	return 0;
}
