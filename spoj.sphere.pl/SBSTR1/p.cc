#include <stdio.h>

int p = 0;

void put(char *s) { while (*s) putchar(*s++); }

void go(int x) { while (p > x) put("<"), p--; while (p < x) put(">"), p++; }
void clr(int x) { go(x); put("[-]"); }

void move(int x, int y) {
	clr(y); go(x); put("[-"); go(y); put("+"); go(x); put("]");
}

void move2(int x, int y1, int y2) {
	clr(y1); clr(y2);
	go(x); put("[-"); go(y1); put("+"); go(y2); put("+"); go(x); put("]");
}

void copy(int x, int y, int z=0) {
	move2(x, y, z);
	move(z, x);
}

void set(int x, int y) { clr(x); while (y--) put("+"); }

/*
   0       copy's temporary
   1..10   source string
   11..15  pattern

   16      NOT output value
   17      st-loop terminator flag / output temporary

   18      do_st-loop has no mismatch?
   19      do_st-loop's copy /terminator temporary
   20      source chars are copied here;  subtraction performed here
   21      pattern chars are copied here
   22      temporary

   23      test cases counter
*/

void do_st(int st)
{
	set(18,1); 
	for (int i = 0; i < 5; i++) {
		go(18); put("[");

		copy(st+i, 20, 19);
		copy(11+i, 21, 19);

		set(22, 0);
		go(21);	put("[-<->>+<]");

		go(20); put("["); set(18,0); go(22); put("[-<+<+>>]");
			                                     clr(20); put("]");

		go(22); put("[-<+<+>>]");

		move(18,22); go(18);
		put("]");
		move(22,18);
	}

	go(18); put("["); set(16,0); clr(18); put("]");
}

int main()
{
	set(23, 24);
	go(23);
	put("[-");

	for (int i = 1; i <= 10; i++) go(i), put(",");

	go(11); put(",");
	for (int i = 11; i <= 15; i++) go(i), put(",");

	go(16); put(",");

	clr(16); put("+");

	for (int st = 1; st <= 6; st++) {
		go(16); put("[");

		do_st(st);

		move(16,17); go(16); put("]");
		move(17,16);
	}

	clr(17);
	for (int i = 0; i < 49; i++) putchar('+');
	go(16); put("[-"); go(17); put("-"); go(16); put("]");
	go(17);
	put(".");

	clr(17);
	for (int i = 0; i < 10; i++) putchar('+');
	put(".");

	for (int i = 1; i <= 22; i++) clr(i);

	go(23);
	put("]");
}
