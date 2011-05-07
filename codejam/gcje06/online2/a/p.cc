#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct SwapSort {
	string sortit(string s) {
		int N = s.size();
		char out[1000];
		strcpy(out, s.c_str());
		sort(out, out+N);
		return string(out);
	}

	string swaps(string in) {
		string res = "", out = sortit(in);
		printf("in:  %s\nout: %s\n", in.c_str(), out.c_str());

		int N = in.size();
		for (;;) {
			int s = -1;
			for (int i = 0; i < N; i++)
				if (in[i] != ' ' && (s < 0 || in[i] < in[s]))
					s = i;
			if (s < 0) break;

			string cyc = "";
			for (int x = s;;) {
				cyc += in[x];
				in[x] = ' ';

				int y;
				for (y = 0; y < N && in[y] != out[x]; y++);
				if (y >= N) break;

				x = y;
			}
			printf("cycle: %s\n", cyc.c_str());

			if (cyc.size() <= 1) continue;

			string sol1 = "";
			for (int i = 1; i < (int)cyc.size(); i++) {
				if (i > 1) sol1 += ',';
				sol1 += cyc[0];
				sol1 += cyc[i];
			}

			string sol2 = "";
			for (int i = cyc.size()-1; i >= 1; i--) {
				if (sol2.size() > 0) sol2 += ',';
				sol2 += cyc[0];
				sol2 += cyc[i];
			}

			if (res.size() > 0) res += ',';
			if (sol1 < sol2) res += sol1; else res += sol2;
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
	if(t<0||t==2) dotest("\"problematic\"", "\"ao,ac,ap,be,bl,bi,br,pt\"", "2");
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
