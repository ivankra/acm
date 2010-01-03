#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
typedef long long int64;

struct BadBinary {
	string bin;
	int64 memo[32][1024];

	int64 go(int i, int x) {
		if (x > 1000) return 0;

		int64 &res = memo[i][x];
		if (res != -1) return res;

		if (i >= (int)bin.size())
			return res = (x == 0) ? 1 : 0;

		res = 0;
		for (int d = 0; d <= 2; d++) {
			int r = bin[i]-'0' + x - d;
			if (r < 0) continue;
			res += go(i+1, 2*r);
		}

		return res;
	}

	long long howMany(int k) {
		bin = "";
		for (int64 t = k; t > 0; t /= 2)
			bin += (char)((t%2)+'0');
		reverse(bin.begin(), bin.end());
		memset(memo, 0xff, sizeof(memo));
		return go(0,0);
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	int x0;
	sscanf(p, "%d%n", &x0, &q); p+=q;
	long z = BadBinary().howMany(x0);
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
	if(t<0||t==0) dotest("1", "1", "0");
	if(t<0||t==1) dotest("2", "2", "1");
	if(t<0||t==2) dotest("3", "1", "2");
	if(t<0||t==3) dotest("4", "3", "3");
	if(t<0||t==4) dotest("10", "5", "4");
	if(t<0||t==5) dotest("489225632", "67366", "5");
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
