#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
typedef long long int64;
using namespace std;

struct Edge {
	int a, b;
	int64 c;
	Edge(int A, int B, int64 C) : a(A), b(B), c(C) {}
};

int N, parent[128], kid[128], sib[128];
vector<Edge> adj[128];
int64 parcost[128], f_memo[128][128], g_memo[128][128], INF=1LL<<55;

int64 g(int x, int k);

int64 f(int x, int k) {
	if (x < 0) return (k==0 ? 0 : INF);

	int64 &res = f_memo[x][k];
	if (res != -1) return res;

	res = f(sib[x], k);
	res <?= parcost[x] + g(x, k);

	for (int u = 1; sib[x] >= 0 && u < k; u++) {
		res <?= parcost[x] + g(x, u) + f(sib[x], k-u);
	}

	return res;
}

int64 g(int x, int k) {
	if (k <= 1) return 0;

	int64 &res = g_memo[x][k];
	if (res != -1) return res;

	res = INF;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		if (adj[x][i].b == parent[x]) continue;
		res <?= f(adj[x][i].b, k-1);
	}
	return res;
}

void dfs(int x, int p) {
	parent[x] = p;
	kid[x] = -1;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		Edge &e = adj[x][i];
		if (e.b != p) {
			parcost[e.b] = e.c;
			sib[e.b] = kid[x];
			kid[x] = e.b;
			dfs(e.b, x);
		}
	}
}

struct HighwayBuilding {
	int getMaxCities(int numCities, int capital, vector<string> highways, int budget) {
		N = numCities;
		for (int i = 0; i < N; i++) adj[i].clear();

		for (int i = 0; i < (int)highways.size(); i++) {
			string s = highways[i];
			for (int j = 0; j < (int)s.size(); j++)
				if (s[j] == ',') s[j] = ' ';

			istringstream is(s);
			int a, b; int64 c;
			while (is >> a >> b >> c) {
				adj[a].push_back(Edge(a,b,c));
				adj[b].push_back(Edge(b,a,c));
			}
		}

		dfs(capital, -1);

		memset(f_memo, 0xff, sizeof(f_memo));
		memset(g_memo, 0xff, sizeof(g_memo));
		for (int i = N; i > 1; i--)
			if (g(capital, i) <= budget) {
				printf("[cost=%lld]", g(capital,i));
				return i-1;
			}
		return 0;
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	int x0;
	sscanf(p, "%d%n", &x0, &q); p+=q;
	int x1;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x1, &q); p+=q;
	vector<string> x2;
	while (*p==' '||*p==',') p++;
	while(*p && *p++!='{');
	while(*p && *p!='}') { string t=""; if(*p!='\"'&&*p!='}'){p++;continue;} p++;
	  while(*p && *p!='\"') {if(*p=='\\') {t+=p[1];p+=2;} else {t+=p[0];p++;}} p++;
	  x2.push_back(t); } while(*p && *p++!='}');
	int x3;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x3, &q); p+=q;
	int z = HighwayBuilding().getMaxCities(x0,x1,x2,x3);
	ostringstream os;
	os << z;
	if(os.str() == e) {
		if (id != "") printf("TEST %s: ", id.c_str());
		printf("\033[01;32mOK\033[0m  got %s\n", os.str().c_str());
	} else {
		printf("\n");
		if (id != "") printf("TEST %s:\n", id.c_str());
		printf("Got: %s\n", os.str().c_str());
		printf("\033[01;31mExp\033[0m: %s\n\n", e.c_str());
	}
	free(P);
}

void doex(int t=-1) {
	if(t<0||t==0) dotest("5, 1, {\"1 0 3,1 2 4,2 4 1,3 2 1\"}, 6", "3", "0");
	if(t<0||t==1) dotest("5, 0, {\"0 1 10\", \"1 2 15,2 3 5\", \"3 4 100000\"}, 200000", "4", "1");
	if(t<0||t==2) dotest("3, 0, {\"0 1 10\", \"1 2 9\"}, 9", "0", "2");
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		doex(-1);
	} else if (argc >= 2 && strcmp(argv[1], "-") == 0) {
		if (argc == 2) {
			string s=""; char buf[65536];
			while(gets(buf))s+=string(buf); dotest(s,"?");
		} else {
			string s="";
			for(int i=2; i<argc; i++) s+=string(argv[i])+" ";
			printf("Args: %s\n", s.c_str());
			dotest(s,"?");
		}
	} else {
		for (int i=1; i<argc; i++) doex(atoi(argv[i]));
	}
}
