#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;
typedef long long int64;

int64 count(int64 N) {
	int64 res = 0;
	for (int64 a = 1; a <= N; a++) {
		int64 b0 = a;
		int64 b1 = max(b0, N+1-a);
		int64 b2 = max(b1, N+1);

		res += a*(b1-b0) + b1*(b1-1)/2 - b0*(b0-1)/2;
		res += (N+1) * (b2-b1);
		res -= N*(N+1)/2 - (a-1)*a/2;
	}
	return res;
}

struct GirlWithMatches {
	int64 getCount(int64 K) {
		int64 left = 0, right = 22900;
		while (left < right) {
			int64 c = (left + right) / 2;
			if (count(c) >= K) right = c; else left = c + 1;
		}
		return left;
	}
};



/* Start of the testing code */
class GirlWithMatchesChecker {
public:
	void doCheck (int64 output, vector<string> answer) {
		long double answerAsLongDouble;
		int64 answerAsLong;
		istringstream iss(answer[0]);
		iss >> answerAsLongDouble;
		answerAsLong = (int64)answerAsLongDouble;
		
		int precision = cout.precision();
		cout.precision(0);
		cout << fixed;
		if (output == answerAsLong)
			cout << "Correct answer!" << endl;
		else
			cout << "Wrong answer: expected "
			     << (long double)answerAsLong << ", got " << (long double)output << endl;
		cout.precision(precision);
	}
};

/* End of the testing code */

/* Start of the testing code */
int main() {
	/* Test 1 */ {
		cout << "Test 1" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 1LL;

		string answer_data_arr[] = {"1"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 4LL;

		string answer_data_arr[] = {"3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 10LL;

		string answer_data_arr[] = {"4"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 100LL;

		string answer_data_arr[] = {"10"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}

	/* Test 5 */ {
		cout << "Test 5" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 1000000000LL;

		string answer_data_arr[] = {"2288"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}
	
	/* Test 6 */ {
		cout << "Test 6" << endl;

		GirlWithMatchesChecker __checker;
		GirlWithMatches __obj;

		int64 in_param_1 = 1000000000000LL;

		string answer_data_arr[] = {"22893"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getCount(in_param_1), answer_data);
	}
}
/* End of the testing code */
