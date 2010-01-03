#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

map<string, string> author;
map<string, int> pos;
vector<string> all;

bool cmp(const string &a, const string &b) {
	if (author[a] != author[b]) return author[a] < author[b];
	return a < b;
}

int main() {
	char buf[1024], cmd[1024], st[1024], sa[1024];
	while (gets(buf) && sscanf(buf, " \"%[^\"]\" by %[^\n\r]", st, sa)==2){
		author[string(st)] = string(sa);
		all.push_back(string(st));
	}

	int N = all.size();

	sort(all.begin(), all.end(), cmp);
	for (int i = 0; i < N; i++)
		pos[all[i]] = i;

	set<int> avail;
	for (int i = 0; i < N; i++) avail.insert(i);

	vector<int> ret;

	while (gets(buf) && sscanf(buf, " %[A-Z]", cmd) == 1) {
		if (strcmp(cmd, "END") == 0) break;

		if (strcmp(cmd, "BORROW") == 0) {
			sscanf(buf, " BORROW \"%[^\"]\"", st);
			avail.erase(pos[string(st)]);
		} else if (strcmp(cmd, "RETURN") == 0) {
			sscanf(buf, " RETURN \"%[^\"]\"", st);
			ret.push_back(pos[string(st)]);
		} else if (strcmp(cmd, "SHELVE") == 0) {
			sort(ret.begin(), ret.end());
			for (int i = 0; i < (int)ret.size(); i++) {
				printf("Put \"%s\" ", all[ret[i]].c_str());
				set<int>::iterator it = avail.insert(ret[i]).first;
				if (it == avail.begin())
					printf("first\n");
				else
					printf("after \"%s\"\n", all[*(--it)].c_str());
			}
			printf("END\n");
			ret.clear();
		}
	}

}
