#include <cstdio>
#include <cctype>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef vector<string> VS;

VS split(const string &s) {
	VS r;
	for (int i = 0, j; i < (int)s.size();) {
		if (isspace(s[i])) { i++; continue; }
		for (j = i+1; j < (int)s.size() && !isspace(s[j]); j++);
		r.push_back(s.substr(i, j-i));
		i = j;
	}
	return r;
}

map<string, int> id;
vector<int> parent;
vector<VS> mut;
string nm, from, gene;

int process(VS &w) {
	if (id.count(from) == 0) return 1;

	int p = id[from];
	for (int i = 5; i < (int)w.size(); i++) {
		gene = w[i];
		for (int x = p; x != 0; x = parent[x])
			for (int i = 0; i < (int)mut[x].size(); i++)
				if (mut[x][i] == gene) return 2;
	}

	int x = parent.size();
	id[nm] = x;
	parent.push_back(p);
	mut.push_back(VS());
	for (int i = 5; i < (int)w.size(); i++)
		mut[x].push_back(w[i]);

	return 0;
}

int main()
{
	char line[256];
	id["ADAM"] = 0;
	parent.assign(1, 0);
	mut.assign(1, VS());
	while (gets(line)) {
		VS w = split(line);
		if (w.size() < 4 || w[0] != "clone") continue;

		nm = w[1];
		from = w[3];
		printf("clone %s from %s ", nm.c_str(), from.c_str());
	
		switch (process(w)) {
		case 0:
			printf("is consistent and safe\n");
			break;
		case 1:
			printf("has no connection to ADAM\n");
			break;
		case 2:
			printf("was at least twice mutated with %s\n",
				gene.c_str());
			break;
		}
	}
}
