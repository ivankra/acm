#include <stdio.h>
#include <math.h>

#define MAXN	131072
#define EPS	1e-9	

typedef struct { double x1, y1, x2, y2, a, b, c; } seg_t;

int isect(seg_t *p, seg_t *q)
{
	double x, y;

	y = p->a * q->b - p->b * q->a;
	if (fabs(y) < EPS) return (fabs(p->c - q->c) < EPS);

	x = (p->c * q->b - p->b * q->c) / y;
	y = (p->a * q->c - p->c * q->a) / y;

	x += EPS; y += EPS;
	if ((x < p->x1 && x < p->x2) || (x < q->x1 && x < q->x2)) return 0;
	if ((y < p->y1 && y < p->y2) || (y < q->y1 && y < q->y2)) return 0;
	
	x -= 2*EPS; y -= 2*EPS;
	if ((x > p->x1 && x > p->x2) || (x > q->x1 && x > q->x2)) return 0;
	if ((y > p->y1 && y > p->y2) || (y > q->y1 && y > q->y2)) return 0;

	return 1;
}

int main()
{
	static seg_t s[MAXN];
	static int next[MAXN], prev[MAXN], q[MAXN], r[MAXN], n;
	int head, i, j, k;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = n; i >= 1; i--) {
			scanf("%lf %lf %lf %lf",
			      &s[i].x1, &s[i].y1, &s[i].x2, &s[i].y2);
			s[i].a = s[i].y2 - s[i].y1;
			s[i].b = s[i].x1 - s[i].x2;
			s[i].c = s[i].a * s[i].x1 + s[i].b * s[i].y1;
			prev[i] = i - 1;
			next[i] = i + 1;
		}
		next[n] = 0;
		next[0] = 1;

		for (head = 1; head != 0; head = next[head]) {
			k = 0;
			q[0] = head;
			r[0] = next[head];

			while (k >= 0) {
				if (r[k] < 0) {
					i = -r[k];
					prev[next[i]] = prev[i];
					next[prev[i]] = next[i];
					r[k] = next[i];
				}

				while (r[k] > 0 && !isect(&s[q[k]], &s[r[k]]))
					r[k] = next[r[k]];

				if (r[k] == 0) {
					k--;
				} else {
					q[k+1] = r[k];
					r[k+1] = next[q[k+1]];
					r[k] = -r[k];
					k++;
				}
			}
		}

		printf("Top sticks:");
		for (j = next[0]; next[j] != 0; j = next[j]);
		for (i = 0; j != 0; i++, j = prev[j])
			printf(i ? ", %d" : " %d", n + 1 - j);
		printf(".\n");
	}

	return 0;	
}

