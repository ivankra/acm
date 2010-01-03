#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<string> VS;  typedef vector<VS> VVS;

string chop(const string &s) {
	int l, r;
	for (l = 0; l < (int)s.size() && isspace(s[l]); l++);
	for (r = s.size()-1; r >= l && isspace(s[r]); r--);
	return s.substr(l, r-l+1);
}

VS splitBy(const string &s, char c=',') {
	VS r;
	for (int i = 0, j; i < (int)s.size();) {
		for (j = i; j < (int)s.size() && s[j] != c; j++);
		r.push_back(chop(s.substr(i, j-i)));
		i = j;
		if (i < (int)s.size() && s[i] == c) i++;
	}
	return r;
}

int main()
{
	char buf[1024];
	gets(buf);
	VS show = splitBy(buf, ',');

	gets(buf);
	VS whereFoo = splitBy(buf, ',');
	VVS where;
	for (int i = 0; i < (int)whereFoo.size(); i++)
		where.push_back(splitBy(whereFoo[i], '='));

	gets(buf);
	VS cols = splitBy(buf, ',');

	map<string, int> colNo;
	for (int i = 0; i < (int)cols.size(); i++)
		colNo[cols[i]] = i;

	for (int i = 0; i < (int)show.size(); i++)
		printf(i ? ", %s" : "%s", show[i].c_str());
	printf("\n");

	while (gets(buf)) {
		VS rec = splitBy(buf, ',');
		for (int i = 0; i < (int)where.size(); i++)
			if (rec[colNo[where[i][0]]] != where[i][1]) goto fail;
		for (int i = 0; i < (int)show.size(); i++)
			printf(i ? ", %s" : "%s", rec[colNo[show[i]]].c_str());
		printf("\n");
fail:;
	}
}
