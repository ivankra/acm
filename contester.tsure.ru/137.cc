#include <cstdio>
#include <cmath>

#define EPS 1e-5

int main()
{
        double a[4];
        for (int i = 0; i < 4; i++) scanf("%lf", &a[i]);

        double AM = (a[0]+a[1]+a[2]+a[3])/4.;
        double GM = sqrt(sqrt(a[0]*a[1])*sqrt(a[2]*a[3]));
        double R = AM - GM;

        int ret = -1;
        double best = 1e99;

        for (int i = 0; i < 4; i++) {
                double diff = fabs(R - a[i]);
                if (fabs(diff - best) < EPS) {
                        ret = -1;
                } else if (diff < best) {
                        ret = i;
                        best = diff;
                }
        }

        printf(ret < 0 ? "DEUCE\n" : "%d\n", ret+1);        
        return 0;
}
