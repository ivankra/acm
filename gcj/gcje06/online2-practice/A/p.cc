#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct SwapSort {
	string sort(const string &s) {
		char t[1000];
		strcpy(t, s.c_str());
		std::sort(t, t+strlen(t));
		return string(t);
	}

	string swaps(string seq) {
		string out = sort(seq);
		int n = seq.size();

		string res = "";
		for (;;) {
			vector<int> c(n, -1);
			int ncyc = 0;

			for (int i = 0; i < n; i++) {
				if (c[i] >= 0) continue;
				for (int x = i; c[x] < 0;) {
					c[x] = ncyc;
					int y;
					for (y = 0; y < n && seq[y] != out[x]; y++);
					if (y >= n) break;
					x = y;
				}
				ncyc++;
			}

			if (ncyc == n) break;

			int a = -1, b = -1;
			for (int i = 0; i < n; i++)
				if (seq[i] != out[i] &&
				    (a < 0 || seq[i] < seq[a])) a = i;
			for (int i = 0; i < n; i++)
				if (c[a] == c[i] && i != a &&
				    (b < 0 || seq[i] < seq[b])) b = i;

			if (res != "") res += ',';
			res += seq[a];
			res += seq[b];

			swap(seq[a], seq[b]);
		}
		return res;
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	string x0;
	while(*p&&*p!='\"')p++; if(*p)p++;
	while(*p&&*p!='\"'){if(*p=='\\'){x0+=p[1];p+=2;}else{x0+=p[0];p++;}} if(*p)p++;
	string z = SwapSort().swaps(x0);
	ostringstream os;
	os << '\"' << z << '\"';
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
	if(t<0||t==0) dotest("\"ABCED\"", "\"DE\"", "0");
	if(t<0||t==1) dotest("\"axrA\"", "\"Aa,ax\"", "1");
	if(t<0||t==2) dotest("\"problematic\"", "\"ac,ap,be,bi,br,co,il,pt\"", "2");
	if(t<0||t==3) dotest("\"abcdefABCDEF\"", "\"Aa,Bb,Cc,Dd,Ee,Ff\"", "3");
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
