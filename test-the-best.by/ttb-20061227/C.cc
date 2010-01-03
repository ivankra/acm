#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long int64;

struct Point {
	int x, y;
};

Point D[1024];
int N;

int check(int x, int y) {
	int res = 0;
	for (int i = 0; i < N; i++)
		res += max(abs(x-D[i].x), abs(y-D[i].y)) & 1;
	return res;
}

struct NewYearSnowfall {
	int getMaximumIntensivity(vector<string> devices) {
		N = devices.size();
		for (int i = 0; i < N; i++)
			sscanf(devices[i].c_str(), "%d %d", &D[i].x, &D[i].y);

		int res = 1;
		for (int i = 0; i < N; i++)
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
					res >?= check(D[i].x+dx, D[i].y+dy);

		srand(time(NULL));
		for (int i = 0; i < 3000; i++)
			res >?= check(rand(), rand());
		return res;
	}
};



/* Start of the testing code */
class NewYearSnowfallChecker {
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

		NewYearSnowfallChecker __checker;
		NewYearSnowfall __obj;

		string in_param_1_arr[] = {"0 0"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 1);

		string answer_data_arr[] = {"1"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumIntensivity(in_param_1), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		NewYearSnowfallChecker __checker;
		NewYearSnowfall __obj;

		string in_param_1_arr[] = {"1 1", "4 4", "3 4"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 3);

		string answer_data_arr[] = {"3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumIntensivity(in_param_1), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		NewYearSnowfallChecker __checker;
		NewYearSnowfall __obj;

		string in_param_1_arr[] = {"3 3", "8 10", "10 9", "4 10", "9 5", "9 6", "10 1", "4 2", "10 8", "2 2"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 10);

		string answer_data_arr[] = {"8"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumIntensivity(in_param_1), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		NewYearSnowfallChecker __checker;
		NewYearSnowfall __obj;

		string in_param_1_arr[] = {"-948 -102", "618 -320", "-57 668", "-935 121", "-904 821", "-44 154", "-20 -993", "601 177", "-667 160", "-698 -595"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 10);

		string answer_data_arr[] = {"7"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumIntensivity(in_param_1), answer_data);
	}
}
/* End of the testing code */
