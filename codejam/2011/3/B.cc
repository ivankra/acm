#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define W 10010
int C[W];

bool possible(int l)
{
    vector<int> c(C, C+W);
    c.push_back(0);
    c.push_back(0);

    for (int i = 0; i < W; i++) {
        while (c[i] != 0) {
            int j;
            for (j = i + 1; j < W && c[j] >= c[j-1]; j++);

            if (j - i < l)
                return false;

            for (int k = i; k < j; k++)
                c[k]--;
        }
    }

    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        int N;
        scanf("%d", &N);

        memset(C, 0, sizeof(C));
        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            C[x+1]++;
        }

        int res = 0;
        for (int l = 1; l <= 10000 && N > 0; l++) {
            if (possible(l)) {
                res = l;
            } else {
                break;
            }
        }

        printf("Case #%d: %d\n", cs, res);
    }
}
