#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
using namespace std;
typedef long long LL;

int main()
{
    int T, C;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d", &C);

        map<int, int> mp;
        set<int> two;
        for (int i = 0; i < C; i++) {
            int P, V;
            scanf("%d %d", &P, &V);
            mp[P] = V;
            if (V >= 2)
                two.insert(P);
        }

        LL res = 0;

        /*
        while (two.size() != 0) {
            int x = *two.begin();
            int y = mp[x];
            int d = y / 2;
            if ((mp[x-1] += d) >= 2) two.insert(x-1);
            if ((mp[x+1] += d) >= 2) two.insert(x+1);
            mp[x] -= 2*d;
            two.erase(x);
            res += d;
        }
        */
        
        while (two.size() != 0) {
            int x = *two.begin();
            int d = mp[x] / 2;
            mp[x] -= 2 * d;
            two.erase(x);

            for (int z = x - d; z <= x + d; z++) {
                if (z == x) continue;
                if ((mp[z] += 1) >= 2)
                    two.insert(z);
            }

            res += d*LL(d+1)*LL(2*d+1)/6;
        }

#if 0
        int min_x = mp.begin()->first;
        int max_x = min_x;
        for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) max_x = max(max_x, it->first);

        printf("x=%d..%d ", min_x, max_x);
        for (int x = min_x; x <= max_x; x++) {
            printf("%d ", mp[x]);
        }
        printf("\n");
#endif

        printf("Case #%d: %lld\n", cs, res);
    }
}
