//Алгоритм Габова для поиска максимального паросочетания в произвольном графе за O(V^3).

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 250;
const int MAXB = MAXN + 1;

int n;
int g[MAXB][MAXB];
int label[MAXB], mate[MAXB], first[MAXB];
queue<int> q;

void restore_path(int v, int w)
{
	int t = mate[v];
	mate[v] = w;
	if (mate[t] != v) return;
	if (label[v] <= n)
	{
		mate[t] = label[v];
		restore_path(label[v], t);
		return;
	}
	int x = (label[v] - 1) / n, y = (label[v] - 1) % n + 1;
	restore_path(x, y), restore_path(y, x);
}

void assign_edge_label(int x, int y)
{
	int r = first[x], s = first[y];
	if (r == s) return;
	int code = x * n + y;
	label[r] = label[s] = -code;
	for (;;)
	{
		if (s)
		{
			int t;
			t = r, r = s, s = t;
		}
		r = first[label[mate[r]]];
		if (label[r] != -code)
		{
			label[r] = -code;
			continue;
		}
		else break;
	}
	for (int i = 0; i < 2; i++)
	{
		int v = i ? first[x]: first[y];
		while (v != r)
		{
			q.push(v);
			label[v] = code;
			first[v] = r;
			v = first[label[mate[v]]];
		}
	}
	for (int i = 0; i <= n; i++)
		if (label[i] >= 0 && label[first[i]] >= 0)
			first[i] = r;
}

int main()
{
	scanf("%d", &n);
	memset(g, 0, sizeof(g));
	int a, b;
	while (scanf("%d%d", &a, &b) == 2) g[a][b] = g[b][a] = 1;
	memset(mate, 0, sizeof(mate));
	for (int u = 1; u <= n; u++)
	{
		if (mate[u]) continue;
		memset(label, -1, sizeof(label));
		label[u] = first[u] = 0;
		while (!q.empty()) q.pop();
		q.push(u);
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			bool done = false;
			for (int y = 1; y <= n; y++)
			{
				if (!g[x][y]) continue;
				if (!mate[y] && y != u)
				{
					mate[y] = x;
					restore_path(x, y);
					done = true;
					break;
				}
				if (label[y] >= 0)
				{
					assign_edge_label(x, y);
					continue;
				}
				int v = mate[y];
				if (label[v] < 0)
				{
					label[v] = x;
					first[v] = y;
					q.push(v);
					continue;
				}
			}
			if (done) break;
		}
	}
	int total = 0;
	for (int i = 1; i <= n; i++)
		if (mate[i]) total++;
	printf("%d\n", total);
	for (int i = 1; i <= n; i++)
		if (mate[i] > i) printf("%d %d\n", i, mate[i]);
	return 0;
}

