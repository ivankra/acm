// ICPC Finals 2003 - Problem F - Combining Images
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <string>
using namespace std;

struct Node {
	int kind;    // -1, 0,1
	Node *p[4];
};

Node _ZERO = { 0, { &_ZERO, &_ZERO, &_ZERO, &_ZERO } };
Node _ONE = { 1, { &_ONE, &_ONE, &_ONE, &_ONE } };
Node *ZERO = &_ZERO;
Node *ONE = &_ONE;

Node *createHetero() {
	Node *p = new Node();
	p->kind = -1;
	for (int i = 0; i < 4; i++) p->p[i] = NULL;
	return p;
}

void destroy(Node *p) {
	if (p == ONE || p == ZERO) return;
	assert(p->kind == -1);
	for (int i = 0; i < 4; i++)
		destroy(p->p[i]);
	delete p;
}

string decodeHex(const char *s)
{
	string bin = "";
	for (; *s; s++) {
		int d;
		if (isdigit(*s)) d = *s - '0'; else d = tolower(*s) - 'a' + 10;
		for (int i = 3; i >= 0; i--) 
			bin += (char)('0' + ((d >> i) & 1));
	}

	int i;
	for (i = 0; i < (int)bin.size() && bin[i] != '1'; i++);
	assert(i < (int)bin.size());
	return bin.substr(i + 1);
}

Node *parse(const string &s, int &pos)
{
	assert(pos < (int)s.size());
	if (s[pos] == '1') {
		++pos;
		assert(pos < (int)s.size());
		int c = s[pos] - '0';
		++pos;
		return c == 0 ? ZERO : ONE;
	} else {
		Node *res = createHetero();
		++pos;
		for (int i = 0; i < 4; i++) {
			res->p[i] = parse(s, pos);
		}
		return res;
	}
}

Node *decode(const char *hex)
{
	string bin = decodeHex(hex);
	int pos = 0;
	Node *res = parse(bin, pos);
	return res;
}

Node *process(Node *A, Node *B)
{
	if (A->kind == -1 || B->kind == -1) {
		Node *q[4];
		for (int i = 0; i < 4; i++)
			q[i] = process(A->p[i], B->p[i]);

		if (q[0] == ZERO && q[1] == ZERO && q[2] == ZERO && q[3] == ZERO) return ZERO;
		if (q[0] == ONE && q[1] == ONE && q[2] == ONE && q[3] == ONE) return ONE;

		Node *res = createHetero();
		for (int i = 0; i < 4; i++)
			res->p[i] = q[i];
		return res;
	} else {
		if (A->kind == 1 && B->kind == 1)
			return ONE;
		else
			return ZERO;
	}
}

string resultBin;

void traverse(Node *p) {
	if (p == ZERO) {
		resultBin += "10";
	} else if (p == ONE) {
		resultBin += "11";
	} else {
		assert(p->kind == -1);
		resultBin += "0";
		traverse(p->p[0]);
		traverse(p->p[1]);
		traverse(p->p[2]);
		traverse(p->p[3]);
	}
}

int main()
{
	char s1[1000], s2[1000];
	for (int cs = 1; ; cs++) {
		if (scanf(" %s %s", s1, s2) != 2) break;
		if (strcmp(s1, "0") == 0 && strcmp(s2, "0") == 0) break;

		Node *A = decode(s1);
		Node *B = decode(s2);
		Node *C = process(A, B);
		resultBin = "1";
		traverse(C);
		destroy(A); destroy(B); destroy(C);

		while (resultBin.size() % 4 != 0) resultBin = "0" + resultBin;

		if (cs > 1) printf("\n");
		printf("Image %d:\n", cs);
		for (int i = 0; i < (int)resultBin.size(); i += 4) {
			int d = 0;
			for (int j = 0; j < 4; j++)
				d = d * 2 + resultBin[i+j] - '0';
			putchar("0123456789ABCDEF"[d]);
		}
		printf("\n");
	}
	printf("\n");
}
