#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <cctype>
using namespace std;

struct Tile {
	char s[64][64];
	Tile() { memset(s, '-', sizeof(s)); }

	void rot90() {
		char next[64][64];
		memset(next, '-', sizeof(next));
		for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
			next[j][63-i] = s[i][j];
		memcpy(s, next, sizeof(next));
	}

	void trans_can() {
		int mrow = 64, mcol = 64, cnt = 0;
		for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++) {
			if (s[i][j] == '-') continue;
			mrow <?= i;
			mcol <?= j;
			cnt++;
		}
		if (cnt == 0) return;

		char next[64][64];
		memset(next, '-', sizeof(next));
		for (int i = mrow; i < 64; i++)
		for (int j = mcol; j < 64; j++)
			next[i-mrow][j-mcol] = s[i][j];

		memcpy(s, next, sizeof(next));
	}

	void rot_can() {
		char best[64][64];
		trans_can();
		memcpy(best, s, sizeof(s));
		for (int i = 0; i < 4; i++) {
			rot90();
			trans_can();
			if (memcmp(s, best, sizeof(s)) < 0)
				memcpy(best, s, sizeof(s));
		}
		memcpy(s, best, sizeof(s));
	}

	bool operator <(const Tile &b) const { return memcmp(s, b.s, sizeof(s)) < 0; }
};

void dfs(vector<string> &lay, Tile &out, int i, int j) {
	if (i < 0 || j < 0 || i >= lay.size() || j >= lay[0].size()) return;
	if (lay[i][j] == '-') return;
	out.s[i][j] = lay[i][j];
	lay[i][j] = '-';
	dfs(lay, out, i-1, j);
	dfs(lay, out, i+1, j);
	dfs(lay, out, i, j-1);
	dfs(lay, out, i, j+1);
}

struct Distinct {
	int count(vector<string> layout) {
		set<Tile> S;

		for (int i = 0; i < (int)layout.size(); i++)
		for (int j = 0; j < (int)layout[0].size(); j++) {
			if (layout[i][j] == '-') continue;

			Tile T;
			dfs(layout, T, i, j);

			T.rot_can();

			S.insert(T);
		}

		return S.size();
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	vector<string> x0;
	while(*p && *p++!='{');
	while(*p && *p!='}') { string t=""; if(*p!='\"'&&*p!='}'){p++;continue;} p++;
	  while(*p && *p!='\"') {if(*p=='\\') {t+=p[1];p+=2;} else {t+=p[0];p++;}} p++;
	  x0.push_back(t); } while(*p && *p++!='}');
	int z = Distinct().count(x0);
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
	if(t<0||t==0) dotest("{\"B-A-A-\", \"AB--BA\", \"-A-A-B\", \"A-AB--\", \"--B---\"}", "3", "0");
	if(t<0||t==1) dotest("{\"A-B-C-D---\"}", "4", "1");
	if(t<0||t==2) dotest("{\"AB-BA-AB-BA-ABBA\"}", "2", "2");
	if(t<0||t==3) dotest("{\"C---DC\", \"DCD-C-\", \"--C-DC\", \"------\", \"DCD---\", \"C-C--C\", \"---DCD\", \"--C--C\", \"DCD---\", \"C---CD\", \"-----C\", \"D---CD\", \"CDC---\", \"--D---\"}", "5", "3");
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
