#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int rank[256];

bool ls(const string &a, const string &b) {
	int i;
	for (i = 0; i < a.size() && i < b.size(); i++)
		if (a[i] != b[i]) return rank[a[i]] < rank[b[i]];
	return (i < b.size());
}

int main()
{
	int n;
	char s[1024];
	vector<string> v;

	memset(rank, 0, sizeof(rank));
	for (int i = 0; i < 26; i++)
		rank["qwertyuiopasdfghjklzxcvbnm"[i]] = i;

	scanf("%d %*d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", s);
		v.push_back(s);
	}

	sort(v.begin(), v.end(), ls);

	for (int i = 0; i < n; i++)
		printf("%s\n", v[i].c_str());
}
