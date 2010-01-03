#include <stdio.h>
#include <assert.h>
#include <algorithm>
using namespace std;

int modinv(int a, int m)
{
	int b = m, x = 1, y = 0, t;
	for (a %= m; a != 0;) {
		t = y-(b/a)*x; y = x; x = t;
		t = b%a; b = a; a = t;
	}
	if (b != 1) return -1;
	return (y < 0) ? (m - (-y) % m) : (y % m);
}

int main()
{
	for (int m = 2; m <= 500; m++) {
		for (int a = 0; a <= 500; a++) {
			int i = modinv(a, m);
			if (__gcd(a, m) != 1) {
				assert(i == -1);
			} else {
				assert(i >= 0 && i < m && (a*i)%m == 1%m);
			}
		}
	}
	printf("passed\n");
}


#if 0
int modinv(int a, int m)
{
	int b = m;
	a %= m;

/**
A,B = original values of a,b;

Invariant:
  a < b
  a = A x1 + B x2
  b = A y1 + B y2

*/
	int x1 = 1, x2 = 0;
	int y1 = 0, y2 = 1;

int A=a, B=b;
printf("modinv a=%d m=%d\n", a, m);

//	while (a != 0) {
for(;;) {

printf("a=%-6d b=%-6d   a=%d*%d+%d*%d%s  b=%d*%d+%d*%d%s\n",
  a,b,
  x1,A,x2,B, x1*A+x2*B==a?"":"[WRONG]",
  y1,A,y2,B, y1*A+y2*B==b?"":"[WRONG]"
);
if(a==0)break;
		int q = b / a, r = b % a;
/*
    b = qa + r

    new_a = r
    new_b = a

    r = b - qa = (A y1 + B y2) - q(A x1 + B x2)
               = A(y1 - q x1) + B(y2 - q x2)
*/
		int t = x1;
		x1 = y1 - q * x1;
		y1 = t;

		t = x2;
		x2 = y2 - q * x2;
		y2 = t;

		b = a; a = r;
	}

	if (b != 1) {
		printf("inverse doesn't exist\n");
		return -1;
	}

	//  A y1 + B y2 = 1
	//  y1 = A^-1 (mod B)

	return (y1 < 0) ? (m - ((-y1) % m)) : (y1 % m);
}
#endif