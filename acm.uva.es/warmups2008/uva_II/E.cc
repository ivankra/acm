#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
typedef unsigned long long ull;

map<ull, ull> mp;

ull f(ull n) {
    while (n & 1) n >>= 1;
    if (n <= 1) return 1;

    if (mp.count(n)) return mp[n];
    return mp[n] = f(n>>1) + f((n>>1)-1);
}

vector<ull> v, w;

void go(ull x, int len, int extra, int extra4)
{
    v.push_back(x);
    if (x > 1000000000000000000ULL) return;
    for (int k = 2; k <= 4 && len+k <= 63; k++) {
        if (k > 2 && extra == 0) break;
        if (k == 4 && extra4 == 0) break;
        ull y = (x << k) + (1 << (k-1));
        go(y, len+k, extra - (k == 2 ? 0 : 1), extra4 - (k == 4 ? 1 : 0));
    }
}

int main()
{
    go(0, 0, 3, 1);
    sort(v.begin(), v.end());
    w.resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        w[i] = f(v[i]);
        if (i >= 1) w[i] = max(w[i], w[i-1]);
    }

    ull N;
    for (int cs = 1; scanf("%llu", &N) == 1 && N > 0; cs++) {
        int l = 0, r = v.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (v[m] <= N)
                l = m;
            else
                r = m;
        }
        printf("Case %d: %llu\n", cs, w[l]);
    }
}
