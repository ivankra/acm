#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long int64;

struct BeaverGame {
	int getMaxProduct(int N) {
		char num[20];
		sprintf(num, "%d", N);

		int len = strlen(num);

		vector<int64> f(100, 0);
		f[len] = 1;

		for (int i = len-1; i >= 0; i--) {
			f[i] = 0;

			int64 q = 1;
			for (int k = i+1; k < len; k++) q *= 9;

			if (num[i] != '0')
				f[i] = q * (num[i]-'0'-1);
			f[i] >?= (num[i]-'0') * f[i+1];

			if (i == 0)
				f[i] >?= q;
		}

		return f[0];
	}
};


/* Start of the testing code */
class BeaverGameChecker {
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

		BeaverGameChecker __checker;
		BeaverGame __obj;

		int in_param_1 = 1;

		string answer_data_arr[] = {"1"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaxProduct(in_param_1), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		BeaverGameChecker __checker;
		BeaverGame __obj;

		int in_param_1 = 101090000;

		string answer_data_arr[] = {"43046721"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaxProduct(in_param_1), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		BeaverGameChecker __checker;
		BeaverGame __obj;

		int in_param_1 = 28994;

		string answer_data_arr[] = {"10368"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaxProduct(in_param_1), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		BeaverGameChecker __checker;
		BeaverGame __obj;

		int in_param_1 = 4876;

		string answer_data_arr[] = {"2268"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaxProduct(in_param_1), answer_data);
	}

	/* Test 5 */ {
		cout << "Test 5" << endl;

		BeaverGameChecker __checker;
		BeaverGame __obj;

		int in_param_1 = 2789;

		string answer_data_arr[] = {"1008"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaxProduct(in_param_1), answer_data);
	}
}
/* End of the testing code */
