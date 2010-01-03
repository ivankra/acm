#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 65536

char T[MAX];
int P[MAX], R[MAX], L[MAX], N, H, n1, n2;

bool cmp(int p, int q) { return R[p+H] < R[q+H]; }

void doit() {
        scanf(" %s", T);
        N = strlen(T);

        for (int i = H = 0; i <= N; i++) R[P[i] = i] = T[i];
        sort(P, P+N+1, cmp);

        for (int i = 0; i <= N; i++) {
                R[P[i]] = i;
                L[i] = 1;
                if (i > 0 && T[P[i-1]] == T[P[i]]) {
                        L[i] = 0;
                        L[R[P[i]] = R[P[i-1]]]++;
                }
        }

        for (H = 1; H < N; H *= 2) {
                for (int a = 0; a <= N; a += L[a])
                        if (L[a] > 1) sort(P+a, P+a+L[a], cmp);

                for (int a = 0, k; a <= N; a += k) {
                        for (k = 1; k < L[a] && R[P[a]+H] == R[P[a+k]+H]; k++);
                        if (k < L[a]) L[a+k] = L[a] - k;
                        L[a] = k;
                }

                for (int a = 0; a <= N; a += L[a])
                        for (int k = 0; k < L[a]; k++)
                                R[P[a+k]] = a;
        }

        for (int i = 0, c = 0; i < N; i++) {
                if (c > 0) c--;
                int y = P[R[i]-1];
                while (T[i+c] == T[y+c]) c++;
                L[R[i]] = c;
        }

        int ret = 0;
        for (int i = 1; i <= N; i++)
                ret += N-P[i]-L[i];
        printf("%d\n", ret);
}

int main() { int T; for (scanf("%d", &T); T-- > 0;) doit(); return 0; }
