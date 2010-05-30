#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct SquareCounting {
	int howMany(vector<string> grid) {
		int N = grid.size(), M = grid[0].size();
		int sq[32][32];

		memset(sq, 0, sizeof(sq));
		for (int y = N-1; y >= 0; y--) {
			for (int x = M-1; x >= 0; x--) {
				sq[y][x] = 1;
				if (y<N-1 && x<M-1 &&
				    grid[y][x] == grid[y+1][x] &&
				    grid[y][x] == grid[y+1][x+1] &&
				    grid[y][x] == grid[y][x+1]) {
					sq[y][x] = 1 + min(sq[y+1][x], min(sq[y+1][x+1], sq[y][x+1]));
				}
			}
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++)
				printf("%d%c ", sq[y][x], grid[y][x]);
			printf("\n");
		}

		for (int y = N-1; y >= 0; y--) {
			for (int x = M-1; x >= 0; x--) {
				int s = sq[y][x];
				if (s <= 0) continue;

				for (int dx = 0; dx < s; dx++)
				for (int dy = 0; dy < s; dy++)
					if ((dx>0||dy>0) && sq[y+dy][x+dx] == s-max(dx,dy))
						sq[y+dy][x+dx] = 0;
			}
		}

		printf("\n");
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++)
				printf("%d%c ", sq[y][x], grid[y][x]);
			printf("\n");
		}

		int res = 0;
		for (int y = N-1; y >= 0; y--)
			for (int x = M-1; x >= 0; x--)
				if (sq[y][x] > 0) res++;
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
	int z = SquareCounting().howMany(x0);
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
	if(t<0||t==0) dotest("{\"AB\", \"CD\"}", "4", "0");
	if(t<0||t==1) dotest("{\"AAB\", \"AAB\", \"BBB\"}", "6", "1");
	if(t<0||t==2) dotest("{\"AA\", \"AA\", \"AA\"}", "2", "2");
	if(t<0||t==3) dotest("{\"AAA\", \"AAA\", \"AAA\"}", "1", "3");
	if(t<0||t==4) dotest("{\"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\", \"AAAAAAAAAA\"}", "1", "4");
	if(t<0||t==5) dotest("{\"AAAAAABBB\", \"AAAAAABBB\", \"AAAAAABBB\", \"AAAAAABBB\", \"AAAAAABBB\", \"BBBAAAAAA\", \"BBBAAAAAA\", \"BBBAAAAAA\", \"BBBAAAAAA\", \"BBBAAAAAA\"}", "12", "5");
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
