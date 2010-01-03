#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

struct Graph {
	typedef int dist_type;
	typedef pair<int, dist_type> edge;
	int N;
	vector<vector<edge> > adj;
	vector<dist_type> dist;
	vector<int> pred;

	Graph(int N_) { N = N_ + 1; adj.resize(N); }
	void add(int x, int y, dist_type c) { adj[x].push_back(edge(y, c)); }

	dist_type dijkstra(int s, int t) { dijkstra(s); return dist[t]; }

	void dijkstra(int s) {
		heap.clear();
		pos.assign(N, -1);
		dist.assign(N, INT_MAX);
		pred.assign(N, -1);

		heap.push_back(s);
		pos[s] = 0;
		dist[s] = 0;
		pred[s] = s;

		while (!heap.empty()) {
			int x = heapExtract();
			pos[x] = -2;

			const vector<edge> &v = adj[x];
			vector<edge>::const_iterator it = v.begin();
			for (; it != v.end(); ++it) {
				int y = it->first;
				if (dist[x] + it->second < dist[y] && pos[y] != -2) {
					if (pos[y] == -1) {
						heap.push_back(y);
						pos[y] = heap.size() - 1;
					}

					dist[y] = dist[x] + it->second;
					pred[y] = x;
					heapUp(pos[y]);
				}
			}
		}
	}

private:
	vector<int> heap, pos;

	int heapExtract() {
		int x = heap[0];
		pos[heap[0] = heap.back()] = 0;
		heap.pop_back();
		if (heap.size() != 0) {
			heapDown(0);
		}
		return x;
	}

	void heapDown(int i) {
		int n = heap.size();
		while (2*i+1 < n) {
			int j = 2*i+1;
			if (j+1 < n && dist[heap[j+1]] < dist[heap[j]]) j++;
			if (dist[heap[i]] <= dist[heap[j]]) break;
			heapSwap(i, j);
			i = j;
		}
	}

	void heapUp(int i) {
		while (i > 0 && dist[heap[i]] < dist[heap[(i-1)/2]]) {
			heapSwap(i, (i-1)/2);
			i = (i-1)/2;
		}
	}

	void heapSwap(int i, int j) {
		int t = heap[i];
		pos[heap[i] = heap[j]] = i;
		pos[heap[j] = t] = j;
	}
};

int main()
{
	int T, N, deg[11000];
	char buf1[256], buf2[256];
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		Graph G(N);

		map<string, int> mp;
		for (int i = 1; i <= N; i++) {
			scanf(" %s %d", buf1, &deg[i]);
			mp[buf1] = i;

			for (int j = 0; j < deg[i]; j++) {
				int y, c;
				scanf("%d %d", &y, &c);
				G.add(i, y, c);
			}
		}

		int Q;
		scanf("%d", &Q);

		while (Q-- > 0 && scanf(" %s %s", buf1, buf2) == 2) {
			int s = mp[buf1];
			int t = mp[buf2];
			printf("%d\n", G.dijkstra(s, t));
		}
	}

	return 0;
}
