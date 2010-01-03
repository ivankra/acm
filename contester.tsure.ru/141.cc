// Binary search + simple geometry.
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct Point {
        double x, y;
};

double cross(const Point &p, const Point &q) { return p.x*q.y-p.y*q.x; }

Point P[1024], Q[1024];
int N;

double cut(double h) {
        int st, m=0;
        for (st = 0; st < N && P[st].y > h-EPS; st++);
        if (st >= N) return 0;

        for (int i = 0; i < N; i++) {
                Point A = P[(st+i)%N], B = P[(st+i+1)%N];
                if (A.y >= h+EPS && B.y >= h+EPS) continue;
                if (A.y < h+EPS && B.y < h+EPS) { Q[m++] = A; continue; }

                Point C = { A.x+(h-A.y)*(B.x-A.x)/(B.y-A.y), h };
                if (A.y < h+EPS) { Q[m++] = A; Q[m++] = C; }
                else { Q[m++] = C; Q[m++] = B; }
        }

        double ret = 0;
        for (int i = 0; i < m; i++)
                ret += cross(Q[i], Q[(i+1)%m]);
        return fabs(ret)/2;
}

int main()
{
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
                scanf(" %lf %lf", &P[i].x, &P[i].y);
                P[N+i] = P[i];
        }

        double rho, S = 0;
        scanf("%lf", &rho);
        for (int i = 0; i < N; i++)
                S += cross(P[i], P[i+1]);
        S = fabs(S) / 2.;

        double a = P[0].y, b = P[0].y;
        for (int i = 0; i < N; i++) {
                a = min(a, P[i].y);
                b = max(b, P[i].y);
        }

        for (int k = 0; k < 100 && b-a > EPS; k++) {
                double c = (a + b) / 2;
                if (cut(c) > rho*S) b = c; else a = c;
        }
        printf("%.3f\n", (a+b)/2.);
        return 0;
}
