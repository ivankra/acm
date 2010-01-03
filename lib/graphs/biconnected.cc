/*
 * Biconnected components, bridges and articulation points of
 * undirected graphs
 */
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1001

int N, counter, seen[MAXN], low[MAXN];
vector<int> adj[MAXN], stk;

void dfs(int x, int parent)
{
    int kids = 0, art = 0;

    low[x] = seen[x] = ++counter;
    stk.push_back(x);

    for (vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it) {
        int y = *it;
        if (y == parent) continue;

        if (seen[y] == 0) {
            dfs(y, x);
            low[x] = min(low[x], low[y]);
            art |= (low[y] >= seen[x]);
            kids++;

            if (low[y] == seen[y]) {
                printf("Edge (%d, %d) is a bridge.\n", x, y);
            }
        } else {
            low[x] = min(low[x], seen[y]);
        }
    }

    if (parent == -1)
        art = (kids >= 2);
    if (art)
        printf("Vertex %d is an articulation point.\n", x);

    if (low[x] == seen[x]) {
        printf("Biconnected component:");
        while (true) {
            int y = stk.back();
            stk.pop_back();
            printf(" %d", y);
            if (y == x) break;
        }
        printf("\n");
    }
}

int main()
{
    int i, x, y, M;
    cin >> N >> M;
    for (i = 0; i < M; i++) {
        cin >> x >> y;
        assert(1 <= x && x <= N && 1 <= y && y <= N && x != y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    memset(seen, 0, sizeof(seen));
    counter = 0;
    stk.clear();

    for (x = 1; x <= N; x++)
        if (seen[x] == 0) dfs(x, -1);
}
