#include <stdio.h>
#include <stdlib.h>

struct Point {
        int x, y, z;
};

int dist(const Point &p, const Point &q) {
        return abs(p.x-q.x) + abs(p.y-q.y) + abs(p.z-q.z);
}

int main()
{
        int cs=1, t, n, ev[8];
        Point p, ep[8];

        for (scanf("%d", &t); cs <= t && scanf("%d", &n) == 1; cs++) {
                for (int i = 0; i < 8; i++) ev[i] = -0x3fffffff;
                for (int i = 0; i < n; i++) {
                        scanf("%d %d %d", &p.x, &p.y, &p.z);

                        int k = 0;
                        for (int dx = -1; dx <= 1; dx += 2)
                        for (int dy = -1; dy <= 1; dy += 2)
                        for (int dz = -1; dz <= 1; dz += 2, k++) {
                                int v = dx*p.x+dy*p.y+dz*p.z;
                                if (v > ev[k]) { ev[k] = v; ep[k] = p; }
                        }
                }

                int best = 0;
                for (int i = 0; i < 8; i++)
                for (int j = i+1; j < 8; j++)
                        best >?= dist(ep[i], ep[j]);

                printf("Case #%d: %d\n", cs, best);
        }
        return 0;
}
