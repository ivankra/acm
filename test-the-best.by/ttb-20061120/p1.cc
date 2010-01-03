#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

struct Record {
	int x, y;
	Record(string s) { sscanf(s.c_str(), "%d:%d", &x, &y); }
	bool operator <(const Record &rec) const {
		return x+y < rec.x+rec.y;
	}
};

struct FootballMatch {
	int maximumDrawsCount(vector<string> scores) {
		vector<Record> rec;
		rec.push_back(Record("0:0"));
		for (int i = 0; i < (int)scores.size(); i++)
			rec.push_back(Record(scores[i]));
		sort(rec.begin(), rec.end());

		int res = 0;
		for (int t = 0; t <= 9; t++) {
			for (int i = 1; i < (int)rec.size(); i++) {
				if (rec[i-1].x <= t && t <= rec[i].x &&
				    rec[i-1].y <= t && t <= rec[i].y) {
					res++;
					break;
				}
			}
		}
		return res;
	}
};
