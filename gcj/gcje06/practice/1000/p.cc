#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

struct Point {
	double x, y, a;
	bool operator <(const Point &q) const { return a < q.a; }
};

struct VectorSet {
	double maxLength(vector<int> xv, vector<int> yv) {
		int n = xv.size();
		Point p[64];

		for (int i = 0; i < n; i++)
			p[i] = (Point){xv[i],yv[i],atan2(yv[i],xv[i])};
		sort(p, p+n);

		double best = 0;
		for (int left = 0; left < n; left++) {
			double sx=0, sy=0;
			for (int k = 0; k < n; k++) {
				sx += p[(left+k)%n].x; sy += p[(left+k)%n].y;
				best >?= sx*sx+sy*sy;
			}
		}
		return sqrt(best);
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	vector<int> x0;
	while(*p && *p++!='{');
	for(;;){int t;while(*p==','||*p==' ')p++;
	  if(sscanf(p,"%d%n",&t,&q)>0){x0.push_back(t);p+=q;}else break;}
	while(*p && *p++!='}');
	vector<int> x1;
	while (*p==' '||*p==',') p++;
	while(*p && *p++!='{');
	for(;;){int t;while(*p==','||*p==' ')p++;
	  if(sscanf(p,"%d%n",&t,&q)>0){x1.push_back(t);p+=q;}else break;}
	while(*p && *p++!='}');
	double z = VectorSet().maxLength(x0,x1);
	ostringstream os;
	os.precision(18);
	os << z;
	if(os.str() == e) {
		if (id != "") printf("TEST %s: ", id.c_str());
		printf("\033[01;32mOK\033[0m  got %s\n", os.str().c_str());
	} else {
		printf("\n");
		if (id != "") printf("TEST %s:\n", id.c_str());
		printf("Got: %s\n", os.str().c_str());
		double E; sscanf(e.c_str(),"%lf",&E);
		if (fabs(E-z) < 1e-9)
			printf("\033[01;32mExp\033[0m: %s\n\n", e.c_str());
		else
			printf("\033[01;31mExp\033[0m: %s\n\n", e.c_str());
	}
	free(P);
}

void doex(int t=-1) {
	if(t<0||t==0) dotest("{0, 0}, {1, -1}", "1.0", "0");
	if(t<0||t==1) dotest("{0, 0}, {1, 1}", "2.0", "1");
	if(t<0||t==2) dotest("{0, 0, 1, -1}, {1, -1, 0, 0}", "1.4142135623730951", "2");
	if(t<0||t==3) dotest("{0, 0, 0, 0}, {1, 2, -1, -2}", "3.0", "3");
	if(t<0||t==4) dotest("{17, 8, -5, -8, -8, -11, -3, 2, 19, 4, 22, 15, 20, 13, -7, 15, -23, 17, -9, -10, 17, 24, 20, -22, -1, -7, -19, 18, -17}, {7, -5, -2, 18, -9, -24, 14, 9, -21, 14, -23, 7, 14, 23, 23, 17, 17, 22, -3, -21, -10, 1, 24, -17, 25, 12, -21, 12, 13}", "289.4563870430224", "4");
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
