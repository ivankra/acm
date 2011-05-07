#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

struct Fraction {
	long long p, q;
	Fraction(long long P, long long Q=1) {
		if (Q < 0) { P = -P; Q = -Q; }
		long long g = (Q > 0) ? __gcd(P, Q) : 1;
		p = P/g; q = Q/g;
	}
	Fraction operator +(const Fraction &b) { return Fraction(p*b.q+b.p*q, b.q*q); }
	Fraction operator -(const Fraction &b) { return Fraction(p*b.q+b.p*q, b.q*q); }
	Fraction operator *(const Fraction &b) { return Fraction(p*b.p, q*b.q); }
};
bool operator ==(const Fraction &a, const Fraction &b) { return a.p*b.q == b.p*a.q; }
bool operator <(const Fraction &a, const Fraction &b) { return a.p*b.q < b.p*a.q; }

struct Point {
	Fraction x, y;
	Point(const Fraction &xx, const Fraction &yy) : x(xx), y(yy) {}
	bool operator <(const Point &q) const {
		return x < q.x || (x == q.x && y < q.y);
	}
};

Fraction cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

int sgn_cross(const Point &o, const Point &a, const Point &b) {
	Fraction f = cross(o, a, b);
	return (f.p < 0) ? -1 : (f.p == 0 ? 0 : 1);
}


VVI G;

struct CrazyPainter {
	int minimumDraws(vector<string> segments) {
		struct Segment { int x1, y1, x2, y2; } ss[51];
		int nseg = segments.size();
		for (int i = 0; i < nseg; i++)
			sscanf(segments[i].c_str(), " %d , %d - %d , %d",
				&ss[i].x1, &ss[i].y1, &ss[i].x2, &ss[i].y2);

		set<Point> pts;
		for (int i = 0; i < nseg; i++) {
			pts.insert(Point(ss[i].x1, ss[i].y1));
			pts.insert(Point(ss[i].x2, ss[i].y2));
		}

		for (int i = 0; i < nseg; i++) {
			Point A(ss[i].x1, ss[i].y1);
			Point B(ss[i].x2, ss[i].y2);
			for (int j = i+1; j < nseg; j++) {
				Point C(ss[j].x1, ss[j].y1);
				Point D(ss[j].x2, ss[j].y2);
				if (sgn_cross(A,B,C)*sgn_cross(A,B,D) >= 0) continue;
				if (sgn_cross(C,D,A)*sgn_cross(C,D,B) >= 0) continue;



			}
		}

		printf("|pts|=%d\n", pts.size());

		G = VVI(pts.size(), VI(pts.size(), 0));

		return 42;
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
	int z = CrazyPainter().minimumDraws(x0);
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
	if(t<0||t==0) dotest("{\"1,1-1,11 11,11-1,11 11,1-11,11 11,1-1,1 11,5-21,5\"}", "1", "0");
	if(t<0||t==1) dotest("{\"1,1-11,11\", \"8,4-11,1\", \"1,11-4,8\"}", "3", "1");
	if(t<0||t==2) dotest("{\"1,1-1,1\", \"2,2-2,2\", \"2,2-2,2\", \"11,11-22,22\", \"15,15-16,16\", \"20,20-20,20\"}", "3", "2");
	if(t<0||t==3) dotest("{\"1,1-1,11 11,11-1,11 11,1-11,11 11,1-1,1\", \"5,5-5,15 15,15-5,15 15,5-15,15 15,5-5,5\"}", "1", "3");
	if(t<0||t==4) dotest("{\"89,27-63,45 24,88-81,1 37,34-22,80\", \"95,1-1,60 29,74-2,19 72,63-3,13 97,63-65,82\", \"3,13-24,88 72,63-81,1 78,42-3,5\"}", "6", "4");
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
