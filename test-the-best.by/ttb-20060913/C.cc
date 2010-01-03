#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
using namespace std;
typedef long long int64;

struct Frac {
	int64 p, q;

	Frac(int64 P=0, int64 Q=1) {
		if (Q < 0) { Q = -Q; P = -P; }
		int64 g = __gcd(P<0?-P:P,Q);
		p = P/g; q = Q/g;
	}

	inline bool operator ==(const Frac &b) const { return p*b.q == q*b.p; }
	inline bool operator <(const Frac &b) const { return p*b.q < q*b.p; }
	inline bool operator <=(const Frac &b) const { return p*b.q <= q*b.p; }
	inline int sign() const { return p==0 ? 0 : (p>0 ? 1 : -1); }
	inline bool operator ==(int n) const { return p==n && q==1; }

	Frac operator *(const Frac &b) const { return Frac(p*b.p, q*b.q); }
	Frac operator /(const Frac &b) const { return Frac(p*b.q, q*b.p); }
	Frac operator +(const Frac &b) const { return Frac(p*b.q+b.p*q, q*b.q); }
	Frac operator -(const Frac &b) const { return Frac(p*b.q-b.p*q, q*b.q); }
};

struct Point {
	Frac x, y;
	Point(Frac X=0, Frac Y=0) : x(X), y(Y) {}
	inline bool operator ==(const Point &b) const { return x==b.x && y==b.y; }
	inline bool operator <(const Point &b) const { return x<b.x || (x==b.x && y<b.y); }
	Point operator +(const Point &b) const { return Point(x+b.x, y+b.y); }
	Point operator -(const Point &b) const { return Point(x-b.x, y-b.y); }
};

int cross(const Point &o, const Point &a, const Point &b) {
	return ((a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x)).sign();
}

struct FunnyBear {
	vector<Point> V;
	vector< vector<int> > adj;
	Point cmp_o;

	bool cmp(int i, int j) {
		Point A = V[i] - cmp_o, B = V[j] - cmp_o;


	}

	int regionsCount(vector<int> x, vector<int> y) {
		vector<Point> P;
		int N = x.size();
		for (int i = 0; i < N; i++)
			P.push_back(Point(Frac(x[i],1), Frac(y[i],1)));

		V = P;
		for (int i = 0; i < N-1; i++) {
			for (int j = i+2; j < N-1; j++) {
				Point &A = P[i], &B = P[i+1];
				Point &C = P[j], &D = P[j+1];

				Point a=B-A, b=C-D, c=C-A;
				Frac det = a.x*b.y-b.x*c.y;
				if (det == 0) continue;

				Frac t = (c.x*b.y-c.y*b.x)/det;
				Frac s = (a.x*c.y-a.y*c.x)/det;

				if (t.sign() <= 0 || s.sign() <= 0) continue;
				if (Frac(1,0) <= t || Frac(1,0) <= s) continue;

				V.push_back(Point(A.x+a.x*t, A.y+a.y*t));
			}
		}
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()), V.end());

		adj.assign(V.size(), vector<int>());

		for (int i = 0; i < N-1; i++) {
			Point &A = P[i], &B = P[i+1];

			vector<int> l;
			for (int j = 0; j < (int)V.size(); j++) {
				if (cross(V[j], A, B) != 0) continue;
				if (V[j].x < min(A.x, B.x) || V[j].x > max(A.x, B.x)) continue;
				if (V[j].y < min(A.y, B.y) || V[j].y > max(A.y, B.y)) continue;
				l.push_back(j);
			}

			for (int k = 0; k+1 < (int)l.size(); k++) {
				adj[l[k]].push_back(l[k+1]);
				adj[l[k+1]].push_back(l[k]);
			}
		}

		for (int i = 0; i < (int)V.size(); i++) {
			cmp_o = V[i];
			sort(adj[i].begin(), adj[i].end(), cmp);
		}

		int res = 0;
		for (int s = 0; s < (int)V.size(); s++) {
			

		}		
		return 0;
	}
};


/* Start of the testing code */
class FunnyBearChecker {
public:
	void doCheck (int output, vector<string> answer) {
		int answerAsInt;
		istringstream iss(answer[0]);
		iss >> answerAsInt;
		
		if (output == answerAsInt)
			cout << "Correct answer!" << endl;
		else
			cout << "Wrong answer: expected "
			     << answerAsInt << ", got " << output << endl;
	}
};

/* End of the testing code */

/* Start of the testing code */
int main() {
	/* Test 1 */ {
		cout << "Test 1" << endl;

		FunnyBearChecker __checker;
		FunnyBear __obj;

		int in_param_1_arr[] = {0, 0, 4, 4, 0};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 5);
		int in_param_2_arr[] = {0, 4, 4, 0, 0};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 5);

		string answer_data_arr[] = {"1"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.regionsCount(in_param_1, in_param_2), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		FunnyBearChecker __checker;
		FunnyBear __obj;

		int in_param_1_arr[] = {0, 4, 0, 4, 0};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 5);
		int in_param_2_arr[] = {0, 4, 4, 0, 0};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 5);

		string answer_data_arr[] = {"2"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.regionsCount(in_param_1, in_param_2), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		FunnyBearChecker __checker;
		FunnyBear __obj;

		int in_param_1_arr[] = {0, 0, 4, 4, 4, 4, 4, 0, 0};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 9);
		int in_param_2_arr[] = {0, 4, 0, 4, 4, 4, 0, 4, 0};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 9);

		string answer_data_arr[] = {"0"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.regionsCount(in_param_1, in_param_2), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		FunnyBearChecker __checker;
		FunnyBear __obj;

		int in_param_1_arr[] = {0, 0, 4, 4, 0, 0, 4, 4, 2, 2};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 10);
		int in_param_2_arr[] = {0, 4, 4, 0, 0, 2, 2, 4, 4, 0};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 10);

		string answer_data_arr[] = {"4"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.regionsCount(in_param_1, in_param_2), answer_data);
	}

	/* Test 5 */ {
		cout << "Test 5" << endl;

		FunnyBearChecker __checker;
		FunnyBear __obj;

		int in_param_1_arr[] = {3, -2, 2, 5, 3, 4, 1, -2, 3, 4};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 10);
		int in_param_2_arr[] = {2, -1, -3, 4, 0, -2, 3, 1, -2, 5};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 10);

		string answer_data_arr[] = {"9"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.regionsCount(in_param_1, in_param_2), answer_data);
	}
}
/* End of the testing code */

