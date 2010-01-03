#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define EPS 1e-9
using namespace std;

struct pt {
	double x, y;
	pt(double x=0, double y=0) : x(x), y(y) {}
};

bool operator <(const pt &a, const pt &b)
{
	return a.x<b.x-EPS || (a.x<b.x+EPS && a.y<b.y-EPS);
};

vector< vector<int> > G, S;
map<pt, int> V;
int adj[128][128], x1[16], y1[16], x2[16], y2[16], nseg;

void edge(pt p, int s)
{
	if (V.count(p) == 0) {
		int i = V.size();
		G.push_back(vector<int>());
		G[i].push_back(s);
		V[p] = i;
	} else {
		G[V[p]].push_back(s);
	}
}

void check(int i, int j)
{
	int d = (y2[i]-y1[i])*(x1[j]-x2[j])-(y2[j]-y1[j])*(x1[i]-x2[i]);
	if (d == 0) return;

	double a1=y2[i]-y1[i], b1=x1[i]-x2[i], c1=a1*x1[i]+b1*y1[i];
	double a2=y2[j]-y1[j], b2=x1[j]-x2[j], c2=a2*x1[j]+b2*y1[j];
	pt p((c1*b2-c2*b1)/d, (a1*c2-a2*c1)/d);

	if (p.x<(x1[i]<?x2[i])-EPS || p.x<(x1[j]<?x2[j])-EPS) return;
	if (p.x>(x1[i]>?x2[i])+EPS || p.x>(x1[j]>?x2[j])+EPS) return;
	if (p.y<(y1[i]<?y2[i])-EPS || p.y<(y1[j]<?y2[j])-EPS) return;
	if (p.y>(y1[i]>?y2[i])+EPS || p.y>(y1[j]>?y2[j])+EPS) return;

	edge(p, i);
	edge(p, j);
}

int main()
{
	while (scanf("%d", &nseg) == 1 && nseg > 0) {
		for (int i = 0; i < nseg; i++)
			scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);

		G.clear();
		V.clear();
		S.clear();

		for (int i = 0; i < nseg; i++) {
			S.push_back(vector<int>());
			edge(pt(x1[i], y1[i]), i);
			edge(pt(x2[i], y2[i]), i);
			for (int j = 0; j < i; j++)
				check(i, j);
		}

		for (int i = 0; i < (int)G.size(); i++) {
			sort(G[i].begin(), G[i].end());
			G[i].erase(unique(G[i].begin(),G[i].end()),G[i].end());
			for (int j = 0; j < (int)G[i].size(); j++)
				S[G[i][j]].push_back(i);
		}

		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < nseg; i++)
			for (int j = 0; j < (int)S[i].size(); j++)
				for (int k = 0; k < (int)S[i].size(); k++)
					adj[S[i][j]][S[i][k]] = 1;

		int r = 0, n = G.size();
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++) {
				if (!adj[i][j]) continue;
				for (int k = j+1; k < n; k++)
					r += adj[j][k] & adj[i][k];
			}

		for (int i = 0; i < nseg; i++) {
			int j = S[i].size();
			printf("<%d>",j);
			r -= j*(j-1)*(j-2)/6;
		}

		printf("%d\n", r);
	}

	return 0;
}
