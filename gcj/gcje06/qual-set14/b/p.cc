#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
typedef unsigned long long u64;

struct WeakPoints {
	long long count(int N, int W) {
		long long f[64][64];
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		f[1][0] = 2;
		for (int n = 2; n <= 60; n++)
		for (int w = 0; w < n; w++)
			f[n][w] = f[n-1][w] + (w == 0 ? 0 : f[n-1][w-1]);

		long long g[64][64];
		memset(g, 0, sizeof(g));
		g[0][0] = 1;
		g[1][0] = 2;
		g[2][0] = 2;
		for (int n = 3; n <= 60; n++)
		for (int w = 0; w < n; w++) {
			g[n][w] = g[n-2][w] + (w-2 >= 0 ? g[n-2][w-2] : 0);
		}

		printf("N=%d W=%d:\n", N, W);
		u64 ret = 0;
		for (int w = 0; w <= W; w++) {
			ret += ((u64)f[N][w] + (u64)g[N][w]) >> 1;
			printf("  w=%d:  f=%lld g=%lld  ret=%llu\n", w, f[N][w], g[N][w], ret);
		}
		return ret;
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	int x0;
	sscanf(p, "%d%n", &x0, &q); p+=q;
	int x1;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x1, &q); p+=q;
	long z = WeakPoints().count(x0,x1);
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
	if(t<0||t==0) dotest("3, 8", "6", "0");
	if(t<0||t==1) dotest("3, 1", "4", "1");
	if(t<0||t==2) dotest("50, 50", "562949970198528", "2");
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
