#include <cstdio>
#include <algorithm>
using namespace std;

struct P { int x, y; } w[1024], r[1024];
int n, m;

bool cmp1r(const P &a, const P &b) { return a.x>b.x || (a.x==b.x && a.y<b.y); }
bool cmp2(const P &a, const P &b) { return a.y<b.y || (a.y==b.y && a.x<b.x); }

int main()
{
        for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
                for (int i = 0; i < n; i++) scanf("%d %d", &w[i].x, &w[i].y);
                scanf("%d", &m);
                for (int i = 0, a, b; i < m; i++) {
                        scanf("%d %d : %d", &r[i].x, &a, &b);
                        r[i].y = (a - 14) * 60 + b;
                }

                sort(w, w+n, cmp1r);
                sort(r, r+m, cmp2);

                int z1 = n, z2 = 0;
                for (int i = 0; i < n; i++) z2 += w[i].x;

                for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n; j++) {
                                if (w[j].x >= 0 && w[j].x <= r[i].x && w[j].y <= r[i].y) {
                                        z1--;
                                        z2 -= w[j].x;
                                        w[j].x = -1;
                                        break;
                                }
                        }
                }

                printf("Trial %d: %d %d\n\n", cs, z1, z2);
        }
}
