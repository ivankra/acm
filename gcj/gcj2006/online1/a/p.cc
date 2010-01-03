#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
typedef long long int64;

struct Frac {
	int64 num, den;

	Frac(int64 n) : num(n), den(1) {}
	Frac(int64 n, int64 d) {
		if (d < 0) { n=-n; d=-d; }
		int64 g = __gcd(n<0?-n:n, d);
		num = n/g;
		den = d/g;
	}

	Frac operator -(const Frac &b) const { return Frac(num*b.den-den*b.num, den*b.den); }
	bool operator <(const Frac &b) const { return num*b.den < den*b.num; }
};

Frac abs(const Frac &f) { return Frac(f.num<0?-f.num:f.num, f.den); }

struct NearFrac {
	string near(string frac, int maxDenom) {
		int64 p, q;
		sscanf(frac.c_str(), "%lld / %lld", &p, &q);

		Frac f = Frac(p, q), best = 0, bestDiff = 0;
		bool first = true;

		for (int64 d = 1; d <= maxDenom; d++) {
			int64 n = p*d/q - 10;
			for (int k = 0; k < 20; k++, n++) {
				Frac approx = Frac(n,d);
				Frac diff = abs(approx - f);
				if (first || diff < bestDiff) {
					best = approx;
					bestDiff = diff;
					first = false;
				}
			}		
		}

		char buf[100];
		sprintf(buf, "%lld/%lld", best.num, best.den);
		return string(buf);
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
	string z = NearFrac().near(x0,x1);
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
	if(t<0||t==0) dotest("\"31416/10000\", 10", "\"22/7\"", "0");
	if(t<0||t==1) dotest("\"-3142/1000\", 1000", "\"-1571/500\"", "1");
	if(t<0||t==2) dotest("\"-7/2\", 1", "\"-4/1\"", "2");
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
