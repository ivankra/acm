#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define IN(x) (2*(x))
#define OUT(x) (2*(x)+1)

struct SalesRouting {
	int howMany(vector<string> adj) {
		int G[128][128], N = adj.size();

		memset(G, 0, sizeof(G));
		for (int i = 0; i < N; i++)
			G[IN(i)][OUT(i)] = 1;

		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (adj[i][j] == '1') {
				G[OUT(i)][IN(j)] = 1;
				G[OUT(j)][IN(i)] = 1;
			}
		}

		int source = OUT(0), sink = IN(1);
		for (int flow = 0;; flow++) {
			int que[256], *qh=que, *qt=que, pred[256];

			memset(pred, 0xff, sizeof(pred));
			*qt++ = source;
			pred[source] = source;

			for (; qh < qt; qh++) {
				int x = *qh;
				for (int y = 0; y < 32; y++) {
					if (G[x][y] > 0 && pred[y] < 0) {
						pred[y] = x;
                                                *qt++ = y;
					}
				}
			}

			if (pred[sink] < 0) return flow;

			for (int y = sink; y != source; y = pred[y]) {
				int x = pred[y];
				G[x][y]--;
				G[y][x]++;
			}
		}
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
	int z = SalesRouting().howMany(x0);
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
	if(t<0||t==0) dotest("{\"001\", \"001\", \"110\"}", "1", "0");
	if(t<0||t==1) dotest("{\"0010\", \"0010\", \"1100\", \"0000\"}", "1", "1");
	if(t<0||t==2) dotest("{\"001100\", \"000001\", \"100010\", \"100010\", \"001101\", \"010010\"}", "1", "2");
	if(t<0||t==3) dotest("{\"001111\", \"001111\", \"110000\", \"110000\", \"110000\", \"110000\"}", "4", "3");
	if(t<0||t==4) dotest("{\"00000\", \"00000\", \"00000\", \"00000\", \"00000\"}", "0", "4");
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
