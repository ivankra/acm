#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct WelcomeKenny {
	int getMinTime (int N, int L, vector<int> Ve, vector<string> edges) {
		static int dist[128][128], in_v[128];

		memset(in_v, 0, sizeof(in_v));
		for (int i = 0; i < (int)Ve.size(); i++)
			in_v[Ve[i]] = 1;

		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist[i][j] = (i==j) ? 0 : (N-1);

		for (int i = 0; i < (int)edges.size(); i++) {
			int x, y;
			sscanf(edges[i].c_str(), " %d %d", &x, &y);
			dist[x][y] = dist[y][x] = 1;
		}

		for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		for (int res = 0; res < N-1; res++)
		for (int x = 0; x < N; x++) {
			vector<int> w;
			for (int y = 0; y < N; y++)
				if (dist[x][y] <= res && in_v[y]) w.push_back(y);
			int c = w.size();
			if (c < L) continue;

			int maxd = 0;
			for (int i = 0; i < c; i++)
				maxd = max(maxd, dist[x][w[i]]);

			for (int i = 0; i < c; i++) if (dist[x][w[i]] == maxd)
			for (int j = 0; j < c; j++)
				if (dist[w[i]][w[j]] > res) goto stop;

			for (int i = 0; i < c; i++) if (dist[x][w[i]] != maxd)
			for (int j = i+1; j < c; j++)
				if (dist[w[i]][w[j]] > res) goto stop;

			return res;
stop:;
		}

		return N-1;
	}
};


int main()
{
	{int N = 7;
	 int L = 2;
	 int V[]={3,5,1};
	 vector<string> E;
	 E.push_back("2 5");
         E.push_back("0 2");
         E.push_back("4 2");
         E.push_back("6 0");
         E.push_back("3 4");
         E.push_back("1 6");
	printf("%d [3]\n", WelcomeKenny().getMinTime(N,L,vector<int>(V,V+sizeof(V)/sizeof(V[0])),E));
	}

	{int V[]={2,8,1,4,7,3};
	 vector<string> E;
	 E.push_back("3 7");
         E.push_back("6 7");
         E.push_back("4 7");
         E.push_back("0 6");
         E.push_back("2 6");
         E.push_back("1 2");
         E.push_back("8 6");
         E.push_back("5 2");
	printf("%d [2]\n", WelcomeKenny().getMinTime(9,3,vector<int>(V,V+sizeof(V)/sizeof(V[0])),E));
	}

	{int N = 2;
	 int L = 2;
	 int V[]={0,1};
	 vector<string> E;
	 E.push_back("1 0");
	printf("%d [1]\n", WelcomeKenny().getMinTime(N,L,vector<int>(V,V+sizeof(V)/sizeof(V[0])),E));
	}


	{int N = 6;
	 int L = 1;
	 int V[]={1,5,2,4};
	 vector<string> E;
	 E.push_back("2 4");
	 E.push_back("5 2");
	 E.push_back("3 4");
	 E.push_back("1 5");
	 E.push_back("0 2");
	printf("%d [0]\n", WelcomeKenny().getMinTime(N,L,vector<int>(V,V+sizeof(V)/sizeof(V[0])),E));
	}


	{int N = 8;
	 int L = 8;
	 int V[]={1,3,0,4,6,2,5,7};
	 vector<string> E;
	 E.push_back("2 0");
	 E.push_back("4 2");
	 E.push_back("5 4");
	 E.push_back("7 4");
	 E.push_back("1 0");
	 E.push_back("6 2");
	 E.push_back("3 5");
	printf("%d [5]\n", WelcomeKenny().getMinTime(N,L,vector<int>(V,V+sizeof(V)/sizeof(V[0])),E));
	}

}
