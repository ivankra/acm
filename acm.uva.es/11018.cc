#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

struct Point { double la, lo; } sites[128];
string names[128];
int dist[128][128], bneck[128][128], N;

void solve(int s, int t, int rng) {
        if (rng < bneck[s][t]) {
                printf("No route for this range, minimum required range is %d km.\n", bneck[s][t]);
                return;
        }

        int pred[128], seen[128], d[128];
        memset(seen, 0, sizeof(seen));
        memset(pred, 0xff, sizeof(pred));
        for (int i=0;i<N;i++) d[i]=0x7fffffff;
        pred[s] = s; d[s] = 0;

        for (int u, v;;) {
                for (u = -1, v = 0; v< N; v++)
                        if (!seen[v] && pred[v] >= 0 && (u < 0 || d[v] < d[u])) u=v;
                if (u < 0) break;
                seen[u] = 1;
                for (v = 0; v < N; v++) {
                        if (!seen[v] && dist[u][v] <= rng && d[u]+dist[u][v] < d[v]) {
                                pred[v] = u;
                                d[v] = d[u] + dist[u][v];
                        }
                }
        }

        int path[128]={t}, p=1;
        for (int u = t; u != s;) {
                u = pred[u];
                path[p++] = u;
        }

        for (int D = 0; p > 0;) {
                p--;
                printf("%-20s at %5d km.\n", names[path[p]].c_str(), D);
                if (p > 0) D += dist[path[p]][path[p-1]];
        }
}

double gcdist(const Point &a, const Point &b, double R) {
        double u = (1. - cos(b.la-a.la)) / 2.;
        double v = cos(a.la) * cos(b.la) * (1. - cos(b.lo-a.lo)) / 2.;
        return 2*R*atan2(sqrt(u+v), sqrt(1-u-v));
}

int main()
{
        char buf[1024], *hyp="------------------------------";
        for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
                printf("%sScenario %d:\n%s\n", cs==1?"":"\n", cs, hyp);
                for (int i = 0; i < N; i++) {
                        scanf(" %s %lf %lf", buf, &sites[i].la, &sites[i].lo);
                        names[i] = string(buf);
                }

                for (int i = 0; i < N; i++) {
                        dist[i][i] = 0;
                        for (int j = 0; j < i; j++)
                                dist[j][i] = dist[i][j] = (int)floor(
                                        .5+gcdist(sites[i], sites[j], 3390));
                }

                for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                        bneck[i][j] = dist[i][j];

                for (int k = 0; k < N; k++)
                for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                        bneck[i][j] <?= (bneck[i][k] >? bneck[k][j]);

                int m, rng;
                char src[1024], dst[1024];

                for (scanf("%d", &m); m-- > 0 && scanf(" %s %s %d", src, dst, &rng) == 3;) {
                        printf("From %s to %s with range %d km:\n", src, dst, rng);
                        int u = find(names, names+N, src) - names;
                        int v = find(names, names+N, dst) - names;
                        solve(u, v, rng);
                        printf("%s\n", hyp);
                }
        }
}
