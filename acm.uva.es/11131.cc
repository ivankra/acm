#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

map<string, int> id;
vector<string> name;

vector<int> kids[5010];
int parent[5010], N;

void dfs(int x, int k, vector<int> &out) {
	out.push_back(x);
	for (int i = 0; i < (int)kids[x].size(); i++) {
		dfs(kids[x][k==0 ? i : (kids[x].size()-1-i)], k, out);
	}
}

vector<int> parse(const string &s) {
	vector<int> res;
	int n = s.size();

	for (int i = 0, j; i < n; i = j) {
		for (j = i; j < n && s[j] != ','; j++);

		string t = s.substr(i, j-i);
		if (j < n && s[j] == ',') j++;

		if (id.count(t) == 0) {
			id[t] = name.size();
			name.push_back(t);
		}

		res.push_back(id[t]);
	}

	return res;
}

int main() {
	char buf[65536];

	id.clear(); name.clear();
	memset(parent, 0xff, sizeof(parent));
	for (int i = 0; i < 5000; i++) kids[i].clear();

	while (gets(buf)) {
		int m = strlen(buf);
		while (m > 0 && strchr(" \t\r\n", buf[m-1]) != NULL) buf[--m]=0;

		vector<int> v = parse(buf);
		for (int i = 1; i < (int)v.size(); i++) {
			parent[v[i]] = v[0];
			kids[v[0]].push_back(v[i]);
		}
	}

	N = name.size();

	int maxdeg = 0;
	for (int i = 0; i < N; i++)
		maxdeg = max(maxdeg, (int)kids[i].size());

	int root = 0;
	for (int i = 0; i < N; i++)
		if (parent[i] < 0) { root = i; break; }

	vector<int> res[2];
	for (int k = 0; k < 2; k++)
		dfs(root, k, res[k]);

	int m = 2;
	if (res[0] == res[1]) m--;

	printf("%d\n", m);
	for (int i = 0; i < m; i++) {
		printf("\n");
		for (int j = (int)res[i].size()-1; j >= 0; j--)
			printf("%s\n", name[res[i][j]].c_str());
	}
}
