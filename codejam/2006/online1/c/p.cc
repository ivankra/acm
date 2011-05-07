#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
using namespace std;
typedef long long int64;

int dig[100], N, INF=0x3fffffff;
map<int64, int> memo[100];

int go(int pos, int64 x) {
	if (pos >= N) return (x==1) ? 0 : INF;

	if (memo[pos].count(x) > 0) return memo[pos][x];
	int &res = memo[pos][x];

	res = INF;

	if (dig[pos] > 0 && (x % dig[pos]) == 0)
		res = go(pos+1, x/dig[pos]);

	for (int d = 1; d <= 9; d++)
		if ((x % d) == 0) res <?= 1 + go(pos+1, x/d);
	return res;
}

struct DigitProduct {
	int minChanges(string digits, string value) {
		sort(digits.begin(), digits.end());
		N = digits.size();
		for (int i = 0; i < N; i++) dig[i] = digits[i]-'0';

		int64 val;
		sscanf(value.c_str(), "%lld", &val);

		if (val == 0)
			return dig[0]==0 ? 0 : 1;

		int64 t = val;
		for (int d = 2; d <= 9; d++)
			while ((t % d) == 0) t /= d;
		if (t != 1) return -1;

		for (int i = 0; i < N; i++) memo[i].clear();

		int res = go(0, val);
		return res<=N ? res : -1;
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	string x0;
	while(*p&&*p!='\"')p++; if(*p)p++;
	while(*p&&*p!='\"'){if(*p=='\\'){x0+=p[1];p+=2;}else{x0+=p[0];p++;}} if(*p)p++;
	string x1;
	while (*p==' '||*p==',') p++;
	while(*p&&*p!='\"')p++; if(*p)p++;
	while(*p&&*p!='\"'){if(*p=='\\'){x1+=p[1];p+=2;}else{x1+=p[0];p++;}} if(*p)p++;
	int z = DigitProduct().minChanges(x0,x1);
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
	if(t<0||t==0) dotest("\"00123450\", \"0\"", "0", "0");
	if(t<0||t==1) dotest("\"00123450\", \"120\"", "3", "1");
	if(t<0||t==2) dotest("\"3411\", \"10\"", "2", "2");
	if(t<0||t==3) dotest("\"2424\", \"1024\"", "2", "3");
	if(t<0||t==4) dotest("\"824\", \"8\"", "1", "4");
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
