#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

char ispal[2510][2510];

struct MaximalPalindromeSubstrings {
	int countMaximalPalindromeSubstrings(vector<string> vstr) {
		string text = "";
		for (int i = 0; i < (int)vstr.size(); i++)
			text += vstr[i];

		int n = text.size();
		memset(ispal, 0, sizeof(ispal));

		for (int i = 0; i < n; i++)
			ispal[0][i] = ispal[1][i] = 1;

		for (int len = 2; len <= n; len++)
		for (int offs = 0; offs+len <= n; offs++)
			ispal[len][offs] = ispal[len-2][offs+1] && text[offs] == text[offs+len-1];

		int ext[2510];
		for (int i = 0; i < n; i++) {
			ext[i] = 0;
			for (int m = 1; i+m <= n; m++)
				if (ispal[m][i]) ext[i] = m;
		}

		int res = 0, cov = 0;
		for (int i = 0; i < n; i++) {
			if (i+ext[i] <= cov) continue;
			cov = i + ext[i];
			res++;
		}
		return res;
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
	int z = MaximalPalindromeSubstrings().countMaximalPalindromeSubstrings(x0);
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
	if(t<0||t==0) dotest("{\"acdadc\"}", "2", "0");
	if(t<0||t==1) dotest("{\"ababab\"}", "2", "1");
	if(t<0||t==2) dotest("{\"aaaa\", \"bbb\", \"axxx\"}", "3", "2");
	if(t<0||t==3) dotest("{\"abacabbacaacdbdcacxcbbbbcabababacccbazhhaahh\"}", "14", "3");
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
