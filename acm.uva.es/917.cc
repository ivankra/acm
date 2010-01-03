#include <cstdio>
#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Game {
	int team1, team2;
	int goals1, goals2;
	Game(int t1, int t2, int g1, int g2) : team1(t1), team2(t2), goals1(g1), goals2(g2) {}
};

vector<Game> games;

struct Team {
	int id, place;
	string name;

	int p[4];

	bool operator <(const Team &b) const {
		for (int i = 0; i < 4; i++)
			if (p[i] != b.p[i]) return p[i] > b.p[i];
		return name < b.name;
	}

	bool same(const Team &b) const {
		for (int i = 0; i < 4; i++)
			if (p[i] != b.p[i]) return false;
		return true;
	}

	Team(string s) : name(s) {}
};

vector<Team> teams;
int loc[100000];

void Sort(int a, int b, int level = 0) {
	if (a > b) return;

	if (a == b) {
		teams[a].place = a;
		return;
	}

	for (int i = a; i <= b; i++) {
		Team &t = teams[i];
		loc[t.id] = i;
		t.p[0] = t.p[1] = t.p[2] = t.p[3] = 0;
	}

	for (int k = 0; k < (int)games.size(); k++) {
		const Game &G = games[k];
		if (loc[G.team1] < 0 || loc[G.team2] < 0) continue;

		Team &a = teams[loc[G.team1]];
		Team &b = teams[loc[G.team2]];

		a.p[1] += G.goals1 - G.goals2;
		a.p[3] += G.goals1;

		b.p[1] += G.goals2 - G.goals1;
		b.p[3] += G.goals2;

		if (G.goals1 > G.goals2) {
			a.p[0] += 3;
			a.p[2]++;
		} else if (G.goals1 == G.goals2) {
			a.p[0]++;
			b.p[0]++;
		} else {
			b.p[0] += 3;
			b.p[2]++;
		}
	}

	for (int i = a; i <= b; i++)
		loc[teams[i].id] = -1;

	sort(teams.begin()+a, teams.begin()+b+1);

	int s = 4;
	for (int i = a; i < b; i++) {
		int j;
		for (j = 0; j < s && teams[i].p[j] == teams[i+1].p[j]; j++);
		if (j < s) s = j;
	}

#if 0
	cout << string(level,' ') << "Sort(a=" << a << ", b=" << b << "):" << endl;
	for (int i = a; i <= b; i++) {
		Team &t = teams[i];
		cout << string(level, ' ') << t.name;
		cout << " pt=" << t.p[0] << " diff=" << t.p[1] << " wins=" << t.p[2] << " scored=" << t.p[3] << endl;
	}
	cout << string(level, ' ') << "s=" << s << endl;
#endif

	if (s == 4) {
		for (int i = a; i <= b; i++)
			teams[i].place = a;
	} else if (s == 0) {
		for (int i = a, j; i <= b; i = j) {
			for (j = i+1; j <= b && teams[i].p[s] == teams[j].p[s]; j++);
			Sort(i, j-1, level+2);
		}
	} else {
		for (int i = a, j; i <= b; i = j) {
			for (j = i; j <= b && teams[i].same(teams[j]); j++)
				teams[j].place = i;
		}
	}
}

int main()
{
	int T, G;
	memset(loc, 0xff, sizeof(loc));
	for (scanf("%d", &T); T-- > 0;) {
		assert(scanf("%d", &G) == 1 && G >= 1);

		map<string, int> nm;

		games.clear();
		teams.clear();

		for (int i = 0; i < G; i++) {
			char name1[100], name2[100];
			int goals1, goals2;

			assert(scanf(" %s %s %d %d", name1, name2, &goals1, &goals2) == 4);

			if (nm.count(name1) == 0) {
				nm[name1] = teams.size();
				teams.push_back(Team(name1));
				teams.back().id = teams.size()-1;
			}

			if (nm.count(name2) == 0) {
				nm[name2] = teams.size();
				teams.push_back(Team(name2));
				teams.back().id = teams.size()-1;
			}

			games.push_back(Game(nm[name1], nm[name2], goals1, goals2));
		}

		int N = teams.size();
		Sort(0, N-1);

		for (int i = 0; i < N; i++) {
			Team &t = teams[i];
			printf("%d %s\n", t.place+1, t.name.c_str());
		}
		if (T > 0) printf("\n");
	}
}
