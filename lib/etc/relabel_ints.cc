#include <map>
using namespace std;

void relabel(int a[], int n) {
        map<int, int> m;
        int i;
        for (i = 0; i < n; i++) m[a[i]] = -1;

        i = 0;
        for (map<int, int>::iterator it = m.begin(); it != m.end(); it++, i++)
                it->second = i;

        for (i = 0; i < n; i++)
                a[i] = m[a[i]];
}

//-----------------------------------------------------------------------------

#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void relabel(int a[], int n) {
        vector<int> v(a, a+n);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        map<int, int> m;
        for (int i = 0; i < (int)v.size(); i++)
                m[v[i]] = i;

        for (int i = 0; i < n; i++)
                a[i] = m[a[i]];
}
