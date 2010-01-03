#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int a[16][16], b;

void go(int row, int col) {
	if (row < 0 || col < 0 || a[row][col] >= 0) return;
	go(row-1, col);
	go(row, col-1);
	a[row][col] = b++;
}

struct MatrixConstructor {
	vector<string> construct(int n, int m, int row, int col) {
		memset(a, 0xff, sizeof(a));
		b = 0;
		go(row, col);
		for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			go(r, c);

		vector<string> ret;
		for (int r = 0; r < n; r++) {
			ostringstream os;
			for (int c = 0;c < m; c++)
				os << (c ? " " : "") << a[r][c];
			ret.push_back(os.str());
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
	int x2;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x2, &q); p+=q;
	int x3;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x3, &q); p+=q;
	vector<string> z = MatrixConstructor().construct(x0,x1,x2,x3);
	ostringstream os;
	os << '{';
	for(vector<string>::const_iterator it=z.begin(); it!=z.end(); it++)
		os << (it == z.begin() ? "" : ", ") << '\"' << (*it) << '\"';
	os << '}';
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
	if(t<0||t==0) dotest("4, 5, 3, 3", "{\"0 1 2 3 16\", \"4 5 6 7 17\", \"8 9 10 11 18\", \"12 13 14 15 19\"}", "0");
	if(t<0||t==1) dotest("4, 5, 2, 1", "{\"0 1 6 7 8\", \"2 3 9 10 11\", \"4 5 12 13 14\", \"15 16 17 18 19\"}", "1");
	if(t<0||t==2) dotest("1, 1, 0, 0", "{\"0\"}", "2");
	if(t<0||t==3) dotest("10, 10, 9, 9", "{\"0 1 2 3 4 5 6 7 8 9\", \"10 11 12 13 14 15 16 17 18 19\", \"20 21 22 23 24 25 26 27 28 29\", \"30 31 32 33 34 35 36 37 38 39\", \"40 41 42 43 44 45 46 47 48 49\", \"50 51 52 53 54 55 56 57 58 59\", \"60 61 62 63 64 65 66 67 68 69\", \"70 71 72 73 74 75 76 77 78 79\", \"80 81 82 83 84 85 86 87 88 89\", \"90 91 92 93 94 95 96 97 98 99\"}", "3");
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
