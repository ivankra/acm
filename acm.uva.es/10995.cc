#include <cstdio>

bool read(double &x) {
	int h, m, s;
	if (scanf(" %d : %d : %d", &h, &m, &s) != 3 || h < 0) return false;
	x = h*3600 + m*60 + s;
	return true;
}

int main() {
	double t1, t2, t3, t4, t5;
	while (read(t1)) {
		read(t2); read(t3); read(t4); read(t5);

		double a = (t2-t5)*(t1-t3)/(t2-t3)/(t1-t4);
		double t = (a*t4-t5)/(a-1);
		int s = (int)(t+0.5);

		printf("%.2d:%.2d:%.2d\n", s/3600, (s/60)%60, s%60);
	}
}
