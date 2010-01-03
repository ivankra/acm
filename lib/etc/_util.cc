#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define all(v) (v).begin(), (v).end()
#define foreach(it,v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

vector<string> split(const string &s, const char *by = " \t\r\n") {
	vector<string> res;
	int i, j, n = s.size();
	for (i = 0; i <= n; i = j + 1) {
		for (j = i; j < n && strchr(by, s[j]) == NULL;) j++;
		res.push_back(s.substr(i, j-i));
	}
	return res;
}

vector<int> compress(vector<int> a)
{
	vector<int> b = a;
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	map<int, int> mp;
	for (int i = 0; i < (int)b.size(); i++)
		mp[b[i]] = i;

	for (int i = 0; i < (int)a.size(); i++)
		a[i] = mp[a[i]];

	return a;
}


template<typename T> ostream &operator <<(ostream &o, const vector<T> &v) {
	o << '{';
	for (int i = 0; i < (int)v.size(); i++) {
		if (i > 0) o << ", ";
		o << v[i];
	}
	o << '}';
	return o;
}

int main()
{

}
