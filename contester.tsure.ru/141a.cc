// A deterministic O(n log^2 n) algorithm, based of suffix and lcp arrays
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 65536

char T[MAX];
int P[MAX], R[MAX], L[MAX], N, H, n1, n2;

bool cmp(int p, int q) { return R[p+H] < R[q+H]; }

int main()
{
        scanf(" %s", T); T[n1 = strlen(T)] = 1;
        scanf(" %s", T+n1+1); n2 = strlen(T+n1+1);
        N = n1 + n2 + 1;

        // sort suffixes by first character, initialize buckets
        for (int i = H = 0; i <= N; i++) R[P[i] = i] = T[i];
        sort(P, P+N+1, cmp);

        for (int i = 0, j; i <= N; i = j) {
                for (j = i; j <= N && T[P[i]] == T[P[j]]; j++) R[P[j]] = i;
                L[i] = j-i;
        }

        // construct suffix array
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

        // construct lcp array
        for (int i = 0, c = 0; i < N; i++) {
                if (c > 0) c--;
                int y = P[R[i]-1];
                while (T[i+c] == T[y+c]) c++;
                L[R[i]] = c;
        }

        // traverse
        int best = 0;
        H = 0; R[0] = 3;
        for (int i = 1; i <= N; i++) {
                int own = 0;
                while ((R[H]>>2) > L[i]) {
                        own |= R[H] & 3;
                        R[--H] |= own;
                        if ((R[H] & 3) == 3) best = max(best, R[H]>>2);
                }
                if ((R[H]>>2) != L[i]) R[++H] = (L[i]<<2) | own;

                int d = (P[i] <= n1) ? (n1-P[i]) : (N-P[i]);
                if ((R[H]>>2) != d) R[++H] = d << 2;
                R[H] |= (P[i] <= n1) ? 1 : 2;
                if ((R[H] & 3) == 3) best = max(best, R[H]>>2);
        }

        while (H > 0) {
                R[H-1] |= R[H] & 3; H--;
                if ((R[H] & 3) == 3) best = max(best, R[H]>>2);
        }
        printf("%d\n", best);
        return 0;
}
