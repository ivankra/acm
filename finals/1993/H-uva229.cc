#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Sensor {
	struct Cell *cell[16];
	int n;
	void add(struct Cell *c) { assert(n+1 <= 15); cell[n++] = c; }

	int sum;
	int curSum, curLeft;
	int id;
	int checkFlag;
};

struct Cell {
	int value;
	int n;
	Sensor *s[5];
};

Sensor sensors[100];
Cell cells[16][16];
int iterations;

Sensor *checklist[1000];
int ncheck;

int answers;
char picture[16][16];

void rec(int row, int col)
{
	Cell *cell;
	Sensor *s;

	if (answers >= 2) return;

	while (true) {
		if (col == 15) { ++row; col = 0; }
		if (row == 10) {
			answers++;
			for (int r = 0; r < 10; r++)
				for (int c=  0; c < 15; c++)
					picture[r][c] = cells[r][c].value == 0 ? '.' : '#';
			return;
		}
		cell = &cells[row][col];
		if (cell->value == -1) break;
		++col;
	}

	++iterations;

	while (ncheck != 0) {
		s = checklist[--ncheck];
		s->checkFlag = 0;
		if (s->curLeft != 0 && (s->curSum == s->sum || s->curSum + s->curLeft == s->sum)) {
			for (int j = 0; s->cell[j] != NULL; j++) {
				if (s->cell[j]->value == -1) {
					cell = s->cell[j];
					goto label1;
				}
			}
		}
	}
label1:

	for (cell->value = 0; cell->value <= 1; ++cell->value) {
		bool ok = true;
		for (int i = 0; cell->s[i] != NULL; i++) {
			s = cell->s[i];
			s->curSum += cell->value;
			--s->curLeft;
			if (s->curSum > s->sum || s->curSum + s->curLeft < s->sum) ok = false;
		}

		if (ok) {
			for (int i = 0; cell->s[i] != NULL; i++) {
				s = cell->s[i];
				if (s->checkFlag == 0) {
					if (s->curSum == s->sum || s->curSum + s->curLeft == s->sum) {
						s->checkFlag = 1;
						checklist[ncheck++] = s;
					}
				}
			}
			rec(row, col);
		}

		for (int i = 0; cell->s[i] != NULL; i++) {
			s = cell->s[i];
			s->curSum -= cell->value;
			++s->curLeft;
		}
	}
	cell->value = -1;
}

void InitLayout()
{
	int k = 0;
	memset(sensors, 0, sizeof(sensors));

	for (int r = 0; r < 10; r++) {
		Sensor *s = &sensors[k++];
		for (int c = 0; c < 15; c++)
			s->add(&cells[r][c]);
	}

	for (int z = 0; z <= 9+14; z++) {
		Sensor *s = &sensors[k++];
		for (int r = 0; r < 10; r++)
		for (int c = 0; c < 15; c++)
			if (r + c == z)
				s->add(&cells[r][c]);
	}

	for (int c = 0; c < 15; c++) {
		Sensor *s = &sensors[k++];
		for (int r = 0; r < 10; r++)
			s->add(&cells[r][c]);
	}

	for (int z = 9; z >= -14; z--) {
		Sensor *s = &sensors[k++];
		for (int r = 0; r < 10; r++)
		for (int c = 0; c < 15; c++)
			if (r - c == z)
				s->add(&cells[r][c]);
	}

	assert(k == 73);

	memset(cells, 0, sizeof(cells));
	for (int i = 0; i < 73; i++) {
		Sensor *s = &sensors[i];
		for (int j = 0; j < s->n; j++) {
			assert(s->cell[j]->n + 1 <= 4);
			s->cell[j]->s[s->cell[j]->n] = s;
			++(s->cell[j]->n);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	InitLayout();

	for (int cs = 1; cs <= T; cs++) {
		for (int i = 0; i < 73; i++) {
			Sensor *s = &sensors[i];
			scanf("%d", &s->sum);
			s->curSum = 0;
			s->curLeft = s->n;
			s->id = i;
		}

		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 15; c++) {
				cells[r][c].value = -1;
			}
		}

		iterations = 0;

		for (int i = 0; i < 73; i++) {
			checklist[i] = &sensors[i];
			sensors[i].checkFlag = 1;
		}
		ncheck = 73;

		answers = 0;
		rec(0, 0);

		if (answers != 1)  memset(picture, '.', sizeof(picture));

		if (cs != 1) printf("\n");
		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 15; c++)
				putchar(picture[r][c]);
			printf("\n");
		}
//		printf("[%d]\n", iterations);
	}

	return 0;
}
