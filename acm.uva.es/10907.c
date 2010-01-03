#include <stdio.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-8

typedef long long num;
typedef struct { num x, y; } pt_t;
typedef struct { double x, y; } fpt_t;
typedef struct { num a, b, c; } line_t;

pt_t P[64], L;
int e, n;
double total;

int isect(line_t l, line_t m, fpt_t *q)
{
	/*(y2-y1)x + (x1-x2)y = x1(y2-y1) + y1(x1-x2)*/
	num d = l.a * m.b - l.b * m.a;
	if (d == 0) return 0;
	q->x = (double)(l.c * m.b - l.b * m.c) / (double)d;
	q->y = (double)(l.a * m.c - l.c * m.a) / (double)d;
	return 1;
}

line_t line(pt_t A, pt_t B)
{
	line_t l;
	l.a = B.y - A.y;
	l.b = A.x - B.x;
	l.c = A.x * l.a + A.y * l.b;
	return l;
}

int coll(pt_t A, pt_t B, pt_t C)
{
	line_t l;
	l = line(A, B);
	return ((l.a * C.x + l.b * C.y) == l.c);
}

fpt_t fpt(pt_t a)
{
	fpt_t b;
	b.x = (double)a.x;
	b.y = (double)a.y;
	return b;
}

double dist(fpt_t A, fpt_t B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double solve()
{
	static fpt_t E, F, R[128];
	double a, t;
	int i, m;

	if (L.x == P[e].x && L.y == P[e].y)
		return total;

	E = fpt(P[e]);

	assert(dist(E, fpt(L)) > 0.5);

	for (i = 0; i < n; i++) {
		if (i == e || (P[i].x == L.x && P[i].y == L.y)) continue;
		if (!coll(L, P[e], P[i])) continue;
		F = fpt(P[i]);
		if (dist(E, F) > dist(fpt(L), F)) continue;
		break;
	}

	if (i < n) {
/*printf("exact, i=%d\n",i);*/
		R[0] = E;
		for (m = 1;;) {
			if (((n + i - e) % n) == 0) break;
			R[m++] = fpt(P[i]);
			i = (i + 1) % n;
		}
	} else {
		for (i = 0; i < n; i++) {
			if (!isect(line(L, P[e]), line(P[i], P[i+1]), &F))
				continue;

			if (dist(E, F) > dist(fpt(L), F)) continue;
			if (fabs(dist(E,F) + dist(fpt(L),F) - dist(E,fpt(L))) < EPS) continue;

			if (F.x < (P[i].x - EPS) && F.x < (P[i+1].x - EPS)) continue;
			if (F.x > (P[i].x + EPS) && F.x > (P[i+1].x + EPS)) continue;
			if (F.y < (P[i].y - EPS) && F.y < (P[i+1].y - EPS)) continue;
			if (F.y > (P[i].y + EPS) && F.y > (P[i+1].y + EPS)) continue;

			break;
		}

		if (i >= n)
			return total;

/*printf("F=(%.3f,%.3f)  line seg %d-%d\n",F.x,F.y,i,i+1);*/

		R[0] = E;
		R[1] = F;
		for (m = 2;;) {
			i = (i + 1) % n;
			if (((n + i - e) % n) == 0) break;
			R[m++] = fpt(P[i]);
		}
	}

	for (i = 0; i < m; i++)
		R[i + m] = R[i];

	for (a = 0., i = 0; i < m; i++)
		a += R[i].x * R[i+1].y - R[i+1].x * R[i].y;
	a /= 2.;

/*printf("Reg A: ");for(i=0;i<m;i++)printf(" (%.3f,%.3f)",R[i].x,R[i].y);printf("\n");
printf("a=%.5f vs %.5f\n",a,total-a);
*/

	assert(a >= -EPS);

	if ((total - a) < EPS) return a;
	if (a < EPS || m < 2) return (total - a);

	F = fpt(L);
	for (i = 0; i < m; i++) {
		t = (R[i].x - F.x) * (R[i+1].y - F.y);
		t -= (R[i+1].x - F.x) * (R[i].y - F.y);
		if (t < -EPS) return (total - a);
	}

	return a;
}

int main()
{
	int i, j, g, q;
	num t;

	for (g = 1; scanf("%d", &n) == 1 && n > 0; g++) {
		printf("Gallery #%d\n", g);

		assert(4 <= n && n <= 20);
		for (i = 0; i < n; i++) {
			scanf("%lld %lld", &P[i].x, &P[i].y);
			P[n + i] = P[i];
		}

		for (i = 0, t = 0; i < n; i++)
			t += P[i].x * P[i+1].y - P[i+1].x * P[i].y;
		assert(t > 0);
		total = (double)t / 2.;

		for (i = 1, j = 0, e = -1; i <= n; i++) {
			t = (P[i].x - P[i-1].x) * (P[i+1].y - P[i-1].y);
			t -= (P[i+1].x - P[i-1].x) * (P[i].y - P[i-1].y);
			if (t < 0) j++, e = i;
		}
		assert(j == 1);
		e %= n;

		for (scanf("%d", &q); q-- > 0 && scanf("%lld %lld", &L.x, &L.y) == 2;)
			printf("%.2f\n", solve());
	}

	return 0;
}
