#include <algorithm>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;

struct FirstError {
	bool checkNum(string s, bool denom = false) {
		if (s.size() < 1) return false;
		if (s[0] == '0') return (!denom && s.size() == 1);

		if (s.size() > 10) return false;

		long long x;
		sscanf(s.c_str(), "%lld", &x);
		return 1 <= x && x <= 0x7fffffffLL;
	}

	bool check(string s, bool whole = false) {
		int k = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			if (!isdigit(s[i]) && s[i] != '/') return false;
			if (s[i] == '/') k++;
		}
		if (k >= 2) return false;

		if (k == 0) return !whole && checkNum(s);

		for (k = 0; s[k] != '/'; k++);
		if (k == (int)s.size()-1)
			return !whole && s.size() >= 2 && checkNum(s.substr(0, s.size()-1));

		string a = s.substr(0, k);
		string b = s.substr(k+1, s.size()-(k+1));

		return checkNum(a) && checkNum(b, 1);
	}

	int firstBad(string frac) {
		for (int i = 1; i <= (int)frac.size(); i++)
			if (!check(frac.substr(0, i))) return i-1;
		return check(frac, true) ? -1 : (int)frac.size();
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	string x0;
	while(*p&&*p!='\"')p++; if(*p)p++;
	while(*p&&*p!='\"'){if(*p=='\\'){x0+=p[1];p+=2;}else{x0+=p[0];p++;}} if(*p)p++;
	int z = FirstError().firstBad(x0);
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
	if(t<0||t==0) dotest("\"31416/10000\"", "-1", "0");
	if(t<0||t==1) dotest("\"3142/1000 a\"", "9", "1");
	if(t<0||t==2) dotest("\"7/23/5\"", "4", "2");
	if(t<0||t==3) dotest("\"4/9876543210\"", "11", "3");
	if(t<0||t==4) dotest("\"2/03\"", "2", "4");
	if(t<0||t==5) dotest("\"111\"", "3", "5");
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
