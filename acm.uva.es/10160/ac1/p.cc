#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef unsigned long long u64;

int bitcnt_16[65536];

int bitcnt(u64 x) {
        int r = bitcnt_16[(int)(x & 0xffff)]; x >>= 16;
        r += bitcnt_16[(int)(x & 0xffff)]; x >>= 16;
        r += bitcnt_16[(int)(x & 0xffff)]; x >>= 16;
        return r + bitcnt_16[(int)(x & 0xffff)];
}

struct Graph {
        int n;
        u64 adj[40];

        int deg[40], seq[40], best, now;
        u64 cov;
        u64 uni[40];
};

void prep(Graph &G) {
        for (int i = 0; i < G.n; i++) {
                G.deg[i] = 0;
                G.adj[i] |= 1ULL << i;
                for (int j = 0; j < G.n; j++)
                        if (i != j) G.deg[i] += (G.adj[i] >> j) & 1;
        }

        for (int i = 0, j; i < G.n; i++) {
                for (j = i-1; j >= 0 && G.deg[G.seq[j]] < G.deg[i]; j--)
                        G.seq[j+1] = G.seq[j];
                G.seq[j+1] = i;
        }

        G.uni[G.n] = 0;
        for (int i = G.n-1; i >= 0; i--)
                G.uni[i] = G.uni[i+1] | G.adj[i];
}

void go(Graph &G, int k) {
        if (G.now >= G.best) return;
        for (;;) {
                if (k >= G.n) {
                        if (G.cov == ((1ULL<<G.n)-1)) G.best <?= G.now;
                        return;
                }

                int x = G.seq[k];
                if ((G.cov & G.adj[x]) == G.adj[x]) { k++; continue; }
                //if (G.deg[x] == 1) { k++; continue; }

                if (G.now + 1 >= G.best) return;
                if (G.now + (G.n-bitcnt(G.cov))/(G.deg[x]+1) >= G.best) return;

                u64 prev = G.cov;
                G.cov |= G.adj[x];
                G.now++;
                go(G, k+1);
                G.now--;
                G.cov = prev;

                k++;
        }
}

int solve_cc(Graph &G) {
        if (G.n <= 1) return G.n;
        if (G.n <= 3) return 1;

        prep(G);

        G.best = G.n/2;
        G.now = 0;
        G.cov = 0;

        go(G, 0);

        return G.best;
}

vector<Graph> ConCom(Graph &G) {
        vector<Graph> ret;
        int s[64], done[64], label[64];

        memset(done, 0, sizeof(done));
        for (int x = 0; x < G.n; x++) {
                if (done[x]) continue;
                memset(label, 0xff, sizeof(label));

                s[0] = x;
                int k = 0, t = 1;
                while (t-- > 0) {
                        int y = s[t];
                        label[y] = k++; done[y] = 1;
                        for (int z = 0; z < G.n; z++)
                                if (!done[z] && ((G.adj[y] >> z) & 1) != 0)
                                        done[s[t++] = z] = 1;
                }

                Graph H;
                H.n = k;
                for (int i = 0; i < H.n; i++) H.adj[i] = 1ULL << i;
                for (int y = 0; y < G.n; y++) {
                        if (label[y] < 0) continue;
                        for (int z = 0; z < G.n; z++) {
                                if (y == z || label[z] < 0) continue;
                                if (((G.adj[y] >> z) & 1) != 0) {
                                        H.adj[label[y]] |= 1ULL << label[z];
                                        H.adj[label[z]] |= 1ULL << label[y];
                                }
                        }
                }
                ret.push_back(H);
        }

        return ret;
}

int solve(Graph &G) {
        vector<Graph> cc = ConCom(G);
        int ret = 0;
        for (int i = 0; i < (int)cc.size(); i++)
                ret += solve_cc(cc[i]);
        return ret;
}

int main()
{
        Graph G;
        int m, x, y;

        for (x = 0; x < 65536; x++) {
                for (m = 0, y = x; y > 0; m++)
                        y &= y - 1;
                bitcnt_16[x] = m;
        }

        while (scanf("%d %d", &G.n, &m) == 2 && G.n > 0) {
                for (int i = 0; i < G.n; i++) G.adj[i] = (1ULL << i);

                while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
                        x--; y--;
                        G.adj[x] |= 1ULL << y;
                        G.adj[y] |= 1ULL << x;
                }

                printf("%d\n", solve(G));
        }

        return 0;
}
