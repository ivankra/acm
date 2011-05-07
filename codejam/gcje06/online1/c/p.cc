#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

vector<int> &operator +=(vector<int> &dst, const vector<int> &src) {
	for (int i = 0; i < (int)src.size(); i++)
		dst.push_back(src[i]);
	return dst;
}

void sort(vector<int> &v) { sort(v.begin(), v.end()); }

int solve(vector<int> st1, vector<int> st2, vector<int> wa) {
	sort(st1); sort(st2); sort(wa);

	vector<int> goal;
	goal += st1;
	goal += st2;
	goal += wa;
	sort(goal);

	while (goal.size() > 0 && wa.size() > 0 && goal.back() == wa.back()) {
		goal.pop_back();
		wa.pop_back();
	}

	if (st1.size() == 0 && st2.size() == 0)
		return 0;

	if (st1.size() == 0 || (st2.size() > 0 && st1.back() < st2.back()))
		swap(st1, st2);

	if (st1.size() > 0 && st2.size() > 0 && st1.back() == st2.back()) {
		st1.pop_back();
		int res = solve(st1, wa, st2) + (1 << (st1.size() + st2.size() + wa.size()));

		st1.push_back(st2.back());
		swap(st1, st2);

		st1.pop_back();
		res <?= solve(st1, wa, st2) + (1 << (st1.size() + st2.size() + wa.size()));
		return res;
	}

	st1.pop_back();
	return solve(st1, wa, st2) + (1 << (st1.size() + st2.size() + wa.size()));
}

struct CraneWork {
	int moves(vector<int> stack1, vector<int> stack2, vector<int> warehouse) {
		return min(solve(stack1, stack2, warehouse),
		           solve(stack2, stack1, warehouse));
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
	vector<int> x2;
	while (*p==' '||*p==',') p++;
	while(*p && *p++!='{');
	for(;;){int t;while(*p==','||*p==' ')p++;
	  if(sscanf(p,"%d%n",&t,&q)>0){x2.push_back(t);p+=q;}else break;}
	while(*p && *p++!='}');
	int z = CraneWork().moves(x0,x1,x2);
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
	if(t<0||t==0) dotest("{3, 50}, {}, {1, 2, 50, 50, 50}", "12", "0");
	if(t<0||t==1) dotest("{50}, {50}, {10, 20, 30}", "17", "1");
	if(t<0||t==2) dotest("{}, {}, {2, 5, 6, 7}", "0", "2");
	if(t<0||t==3) dotest("{1, 2, 3}, {}, {}", "7", "3");
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
