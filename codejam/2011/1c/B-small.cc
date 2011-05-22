#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

int N, L, T;
int dist[1000010];

template<typename T>
T clamp(T x, T a, T b) {
    return min<T>(b, max<T>(a, x));
}

double solve_small()
{
    static double f[1010][3], INF=1e99;

    for (int i = 1; i <= N; i++) {
        for (int b = 0; b <= L; b++) {
            f[i][b] = INF;
        }
    }

    f[0][L] = 0;
    for (int i = 0; i < N; i++) {
        for (int b = 0; b <= L; b++) {
            for (int take = 0; take <= 1 && take <= b; take++) {
                if (!take) {
                    f[i+1][b] = min(f[i+1][b], f[i][b] + 2*dist[i]);
                } else {
                    double slow = clamp<double>(T - f[i][b], 0, 2*dist[i]);
                    f[i+1][b-1] = min(f[i+1][b-1], f[i][b] + slow + dist[i]-slow/2.0);
                }
            }
        }
    }

    double res = INF;
    for (int b = 0; b <= L; b++)
        res = min(res, f[N][b]);
    return res;
}


int main()
{
    int num_cs;
    scanf("%d", &num_cs);

    for (int cs = 1; cs <= num_cs; cs++) {
        int C, a[2000];

        scanf("%d %d %d %d", &L, &T, &N, &C);
        for (int i = 0; i < C; i++)
            scanf("%d", &a[i]);

        for (int i = 0; i < N; i++)
            dist[i] = a[i % C];

        //printf("dist=["); for (int i = 0; i < N; i++) printf(" %d", dist[i]); printf(" ]  L=%d t=%d\n", L, T);

        printf("Case #%d: %.0lf\n", cs, solve_small());
    }
}
