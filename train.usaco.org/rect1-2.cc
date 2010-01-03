/*
ID: infnty1
PROB: rect1
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct event { int y, r; event(int _y, int _r) { y=_y; r=_r; } };
bool operator <(event const &a, event const &b) { return a.y < b.y; }

int main()
{
    struct rect { int x1, y1, x2, y2, c; } R[1001];
    int A[2501], i, n;
    vector<int> X;

    /* E keeps the list of events along y-axis. The events are appearance and
       disappearance of rectangles at certain y's as we move from -inf to +inf. */
    vector<event> E;

    freopen("rect1.in", "r", stdin);
    freopen("rect1.out", "w", stdout);

    R[1].x1 = R[1].y1 = 0; R[1].c = 1;
    scanf("%d %d %d", &R[1].x2, &R[1].y2, &n); n++;

    for (i = 2; i <= n; i++)
        scanf("%d %d %d %d %d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2, &R[i].c);

    for (i = 1; i <= n; i++) {
        X.push_back(R[i].x1); X.push_back(R[i].x2);
        E.push_back(event(R[i].y1, i));
        E.push_back(event(R[i].y2, -i));  /* negative 'r' indicates that the rectangle disappears */
    }
    sort(X.begin(),X.end()); sort(E.begin(),E.end());

    for (i = 1; i <= 2500; i++) A[i] = 0;

    for (i = 0; i < X.size()-1; i++) {
        int x1 = X[i], x2 = X[i+1], y1;
        set<int, greater<int> > H;

        for (vector<event>::iterator e = E.begin(); e != E.end(); e++) {
            int k = abs(e->r);
            if (R[k].x2 < x2 || R[k].x1 > x1) continue;

            if (!H.empty()) A[R[*H.begin()].c] += (e->y-y1)*(x2-x1);
            y1 = e->y;

            if (e->r > 0)
                H.insert(e->r);
            else
                H.erase(-e->r);
        }
    }

    for (i = 1; i <= 2500; i++)
        if (A[i]) printf("%d %d\n", i, A[i]);

    return 0;
}
