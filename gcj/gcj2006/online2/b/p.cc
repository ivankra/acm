#include <algorithm>
#include <vector>
#include <sstream>
typedef long long int64;
using namespace std;

int pw[100], mod, memo[51][65536], N;
int dig[100];

int go(int i, int r) {
	int &res = memo[i][r];
	if (res >= 0) return res;

	if (i == N) return res = (r==0 ? 0 : (1<<20));

	res = 1<<20;
	for (int d = 0; d <= 9; d++)
		res <?= (d == dig[i] ? 0 : 1) + go(i+1, (r+d*pw[i])%mod);
	return res;
}

struct DigitCorrections {
	int getMin(string totalParts, int numBins) {
		mod = numBins;
		pw[0] = 1 % mod;
		for (int k = 1; k < 100; k++) pw[k] = (pw[k-1] * 10) % mod;

		N = totalParts.size();
		for (int i = 0, j =N-1; i < N; i++, j--) dig[j] = totalParts[i]-'0';

		memset(memo, 0xff, sizeof(memo));
		return go(0, 0);
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	string x0;
	while(*p&&*p!='\"')p++; if(*p)p++;
	while(*p&&*p!='\"'){if(*p=='\\'){x0+=p[1];p+=2;}else{x0+=p[0];p++;}} if(*p)p++;
	int x1;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x1, &q); p+=q;
	int z = DigitCorrections().getMin(x0,x1);
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
	if(t<0||t==0) dotest("\"22\", 100", "2", "0");
	if(t<0||t==1) dotest("\"1004\", 25", "1", "1");
	if(t<0||t==2) dotest("\"203\", 107", "2", "2");
	if(t<0||t==3) dotest("\"882349823048203948203948230948230498\", 49999", "3", "3");
	if(t<0||t==4) dotest("\"12345678901234567890123456789012345678901234567890\", 50000", "4", "4");
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
