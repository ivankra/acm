#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;  typedef vector<VVI> VVVI;

#define MAX 5

// Returns some longest common subsequence of two strings.  O(n^2).
string lcs(const string &s, const string &t) {
	static int f[MAX+1][MAX+1];
	int n = s.size(), m = t.size();
	for (int i = 0; i <= n; i++) f[i][m] = 0;
	for (int j = 0; j <= m; j++) f[n][j] = 0;

	for (int i = n-1; i >= 0; i--)
		for (int j = m-1; j >= 0; j--)
			if (s[i] == t[j])
				f[i][j] = 1 + f[i+1][j+1];
			else
				f[i][j] = max(f[i+1][j], f[i][j+1]);

	string r = "";
	for (int i = 0, j = 0; i < n && j < m;)
		if (s[i] == t[j])
			r += s[i], i++, j++;
		else if (f[i+1][j] >= f[i][j+1])
			i++;
		else
			j++;
	return r;
}

// Returns some longest common subsequence of three strings.  O(n^3).
string lcs(const string &s, const string &t, const string &u) {
	static int f[MAX+1][MAX+1][MAX+1];
	int n = s.size(), m = t.size(), k = u.size();
	for (int x = 0; x <= n; x++) f[x][m][k] = 0;
	for (int y = 0; y <= m; y++) f[n][y][k] = 0;
	for (int z = 0; z <= k; z++) f[n][m][z] = 0;

	for (int x = n-1; x >= 0; x--)
	for (int y = m-1; y >= 0; y--)
	for (int z = k-1; z >= 0; z--)
		if (s[x] == t[y] && s[x] == u[z])
			f[x][y][z] = 1 + f[x+1][y+1][z+1];
		else
			f[x][y][z] = max(f[x+1][y][z],
					max(f[x][y+1][z], f[x][y][z+1]));

	string r = "";
	for (int x = 0, y = 0, z = 0; x < n && y < m && z < k;)
		if (s[x] == t[y] && s[x] == u[z])
			r += s[x], x++, y++, z++;
		else if (f[x][y][z] == f[x+1][y][z])
			x++;
		else if (f[x][y][z] == f[x][y+1][z])
			y++;
		else
			z++;

	return r;
}

// Checks whether `s' is a subsequence of `of'.
bool is_subseq(const string &s, const string &of) {
	int n = s.size(), m = of.size(), i, j;
	for (i = 0, j = 0; i < n && j < m; j++)
		if (of[j] == s[i]) i++;
	return (i == n);
}

struct AllLCS {
	string s, t, alpha;
	int n, m, A;
	vector<string> res;
	VVVI lenx;
	VVI len;
	string pref;

	void rec(int i0, int j0, int x) {
		int L = (x < 0 ? len[i0][j0] : lenx[i0][j0][x]);
		if (L <= 0) { res.push_back(pref); return; }

		for (int ci = 0; ci < A; ci++) {
			if (ci == x) continue;
			int c = alpha[ci];

			int i = i0, j = j0, k = 0;
			while (i < n && j < m) {
				if (s[i] != c) { i++; continue; }
				if (t[j] != c) { j++; continue; }
				pref += c; k++; i++; j++;
				if (lenx[i][j][ci] == L-k) rec(i, j, ci);
			}
			if (k > 0) pref.resize(pref.size() - k);
		}
	}

	vector<string> main(const string &ss, const string &tt) {
		s = ss; t = tt;
		n = s.size(); m = t.size();

		alpha = s + t;
		sort(alpha.begin(), alpha.end());
		alpha.erase(unique(alpha.begin(), alpha.end()), alpha.end());
		A = alpha.size();

		res.clear();
		len = VVI(n+1, VI(m+1, 0));
		lenx = VVVI(n+1, VVI(m+1, VI(A+1, 0)));

		// lenx[i][j][x] = length of longest common subsequence of
		// s[i..n-1] and t[j..n-1] which doesn't begins with letter
		// alpha[x].

		for (int i = n-1; i >= 0; i--)
		for (int j = m-1; j >= 0; j--) {
			len[i][j] = s[i]==t[j] ? len[i+1][j+1]+1 : max(len[i+1][j], len[i][j+1]);

			for (int x = 0; x < A; x++)
				if (s[i] == t[j])
					lenx[i][j][x] = (s[i]!=alpha[x]) ? 1+len[i+1][j+1] : 0;
				else
					lenx[i][j][x] = max(lenx[i+1][j][x], lenx[i][j+1][x]);
		}

		pref = "";
		rec(0, 0, -1);

		return res;
	}
};

// Returns all distinct longest common subsequences of two strings.
// O(n^3 + k), where n=max(|s|,|t|), k = size of output.
vector<string> all_lcs(const string &s, const string &t) {
	return AllLCS().main(s, t);
}

string gen(int n, char z) {
	string res(n, 'a');
	for (int i = 0; i < n; i++) res[i] = 'a' + rand() % (z - 'a' + 1);
	return res;
}

// unit tests for all_lcs();
void all_lcs_test() {
	assert(all_lcs("abc", "abc").size() == 1);
	assert(all_lcs("abc", "cba").size() == 3);
	assert(all_lcs("zabcdefz", "zfedcbaz").size() == 6);
	assert(all_lcs("a", "a").size() == 1);
	assert(all_lcs("a", "b").size() == 1);
	assert(all_lcs("a", "b")[0].size() == 0);
	assert(all_lcs("abc", "").size() == 1);
	assert(all_lcs("", "").size() == 1);
	assert(all_lcs("aaaabbbbcc", "aaabccc").size() == 1);
	assert(all_lcs("abc", "acb").size() == 2);
	assert(all_lcs("n", "yrn").size() == 1);

	for (int cs = 0; ; cs++) {
		string s = gen(2 + rand()%8, 'z');
		string t = gen(2 + rand()%8, 'z');

if (cs == 0) { s = "bhwahtvt"; t = "ehvhjo"; }
  
		printf("%s %s ", s.c_str(), t.c_str());
		fflush(stdout);

		vector<string> all = all_lcs(s, t);
		assert(all.size() >= 1);

		int L = lcs(s, t).size();
		for (int i = 0; i < (int)all.size(); i++)
			assert((int)all[i].size() == L);

		vector<string> my;
		for (int m = 0; m < (1 << (int)s.size()); m++) {
			string u = "";
			for (int i = 0; i < (int)s.size(); i++)
				if (m & (1 << i)) u += s[i];
			assert(is_subseq(u, s));
			if (!is_subseq(u, t)) continue;
			assert((int)u.size() <= L);
			if ((int)u.size() != L) continue;
			my.push_back(u);
		}
		sort(my.begin(), my.end());
		my.erase(unique(my.begin(), my.end()), my.end());

		sort(all.begin(), all.end());

		if (my != all) {
			printf("FAILED (my!=all)\n");
			printf("all={");
			for(int i = 0; i < (int)all.size(); i++)
				printf("%s ", all[i].c_str());
			printf("}\n");
			printf("my={");
			for(int i = 0; i < (int)my.size(); i++)
				printf("%s ", my[i].c_str());
			printf("}\n");
		}

		assert(my == all);

		printf("ok\n");
	}
}

string lcs3_bad(const string &s, const string &t, const string &u) {
	string res = "";

	for (int k = 0; k < 3; k++) {
		vector<string> v; string w;
		if (k == 0) { v = all_lcs(s, t); w = u; }
		if (k == 1) { v = all_lcs(s, u); w = t; }
		if (k == 2) { v = all_lcs(t, u); w = s; }
		for (int i = 0; i < (int)v.size(); i++) {
			string t = lcs(v[i], w);
			if (t.size() > res.size()) res = t;
		}
	}

	return res;
}

int main() {
	srand(time(NULL));
	for (int cs = 0; ; cs++) {
		string a = gen(MAX, 'e');
		string b = gen(MAX, 'e');
		string c = gen(MAX, 'e');

		string r = lcs(a, b, c);
		string f = lcs3_bad(a, b, c);

		assert(is_subseq(r, a) && is_subseq(r, b) && is_subseq(r, c));
		assert(is_subseq(f, a) && is_subseq(f, b) && is_subseq(f, c));

		if (r.size() != f.size()) {
			printf("\na=%s\nb=%s\nc=%s\n", a.c_str(), b.c_str(), c.c_str());
			printf("r=%s\nf=%s\n\n", r.c_str(), f.c_str());
			exit(0);
		}

		putchar('.');
		fflush(stdout);
	}
}


