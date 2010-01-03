#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int N, got[65536], mat[32][32], memo[65536];

int f(int r, int m) {
	int &res = memo[m];
	if (got[m]) return res;
	got[m] = 1;
	if (m == 0) return res = 1;
	res = 0;
	for (int i = 0; i < N; i++)
		if (m & (1 << i))
			res = (res + mat[r][i] * f(r-1, m^(1<<i))) % 10000;
	return res;
}

struct PermanentComputation {
	int compute(vector<string> matrix) {
		N = matrix.size();
		for (int i = 0; i < N; i++) {
			istringstream is(matrix[i]);
			for (int j = 0; j < N; j++) {
				is >> mat[i][j];
				mat[i][j] %= 10000;
			}
		}
		memset(got, 0, sizeof(got));
		return f(N-1, (1<<N)-1) % 10000;
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
	int z = PermanentComputation().compute(x0);
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
	if(t<0||t==0) dotest("{\"1 1\", \"1 1\"}", "2", "0");
	if(t<0||t==1) dotest("{\"1 2 3\", \"4 5 6\", \"7 8 9\"}", "450", "1");
	if(t<0||t==2) dotest("{\"1 2 3 4\", \"2 3 4 5\", \"3 4 5 6\", \"4 5 6 7\"}", "4276", "2");
	if(t<0||t==3) dotest("{\"1 1 1\", \"2 2 2\", \"3 3 3\"}", "36", "3");
	if(t<0||t==4) dotest("{\"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\", \"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\"}", "8000", "4");
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
