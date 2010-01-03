#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> PII;

map<PII, int> Vmap;
vector<PII> V;
vector<vector<int> > adj;

double len(int u, int v) {
	double dx = V[u].first - V[v].first;
	double dy = V[u].second - V[v].second;
	return sqrt(dx*dx + dy*dy);
}

vector<int> readLine()
{
	vector<int> res;
	string line;
	if (!getline(cin, line)) return res;
	if (line.size() < 3) return res;

	for (int i = 0; i < line.size();) {
		if (!isdigit(line[i]) && line[i] != '-') { i++; continue; }
		int sign = 1;
		if (line[i] == '-') {
			i++;
			sign = -1;
		}
		int x = 0;
		while (i < line.size() && isdigit(line[i]))
			x = x * 10 + line[i++] - '0';
		res.push_back(sign * x);
	}

	for (int i = 0; i+1 < res.size(); i += 2) {
		if (res[i] == -1 && res[i+1] == -1) {
			res.resize(i);
			break;
		}
	}

	assert(res.size() % 2 == 0);

	for (int i = 0; 2*i < res.size(); i++) {
		PII p(res[2*i], res[2*i+1]);
		if (Vmap.count(p) == 0) {
			V.push_back(p);
			Vmap[p] = V.size() - 1;
			adj.push_back(vector<int>());
		}
		res[i] = Vmap[p];
	}
	res.resize(res.size() / 2);
	return res;
}

int main()
{
	string line;
	getline(cin, line);
	int T = atoi(line.c_str());

	getline(cin, line);

	while (T--) {
		Vmap.clear();
		V.clear();
		adj.clear();

		vector<int> s;
		do { s = readLine(); } while (s.size() == 0);

		while (true) {
			vector<int> v = readLine();
			if (v.size() == 0) break;
			for (int i = 1; i < v.size(); i++) {
				adj[v[i]-1].push_back(v[i]);
				adj[v[i]].push_back(v[i]-1);
			}
		}

		int N = V.size();
		vector<double> dist(N, 1e20);
		vector<int> seen(N, 0);
		dist[s[0]] = 0;

		double walk = 10000.0 / 3600.0;
		double subway = 40000.0 / 3600.0;

		while (true) {
			int u = -1;
			for (int x = 0; x < N; x++)
				if (!seen[x] && (u < 0 || dist[x] < dist[u])) u = x;
			if (u < 0) break;

			seen[u] = 1;

			for (int v = 0; v < N; v++)
				dist[v] <?= dist[u] + len(u, v) / walk;

			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i];
				dist[v] <?= dist[u] + len(u, v) / subway;
			}
		}

		printf("%.0f\n", dist[s[1]] / 60.0);
		if (T != 0) printf("\n");
	}
}
