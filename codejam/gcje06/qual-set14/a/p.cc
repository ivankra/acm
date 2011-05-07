#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct Hardwood {
	bool valid(int w, int h) {
		return 1 <= w && 1 <= h && max(w,h) <= 2*min(w,h);
	}

	int f(int width, int height) {
		if (height > width) swap(height, width);
		int ret = 0;
		for (int w = 1; w < width; w++)
			if (valid(w, height) && valid(width-w, height)) ret++;
		for (int h = 1; h < height; h++)
			if (valid(h, width) && valid(height-h, width)) ret++;
//printf("f(%d,%d)=%d\n", width, height, ret);
		return (ret == 0) ? 0 : 1;
	}

	int hwCount(int width, int height) {
		if (height > width) swap(height, width);
		// height <= width

		if (height == 1) {
			if (width < 3) return 0;
			int ret = 0;
			for (int L = 0; L <= 4; L++)
			for (int R = 0; R <= 4; R++) {
				if (L+R >= width || L+R < 2 || L+R > 4) continue;
				if (max(L,R)>2 && min(L,R) != 0) continue;
				ret++;
			}
			return ret;
		}

		int ret = 0;
		for (int w = 1; w < width; w++)
		for (int h = 1; h < height; h++) {
			int a1 = width - w, b1 = h;
			int a2 = width, b2 = height - h;

			if (valid(a1,b1) && valid(a2,b2)) {
				ret++;
				continue;
			}

			a1 = width - w; b1 = height;
			a2 = w; b2 = height - h;

			if (valid(a1,b1) && valid(a2,b2)) {
				ret++;
				continue;
			}
		}
		ret *= 4;

		for (int w = 1; w < width; w++) {
			ret += 2 * f(width-w, height);
			for (int x = 1; x+w < width-1; x++)
				ret += f(x, height) * f(width-x-w, height);
		}

		for (int h = 1; h < height; h++) {
			ret += 2 * f(height-h, width);
			for (int x = 1; x+h < height-1; x++)
				ret += f(x, width) * f(height-x-h, width);
		}

		return ret;
	}
};

//-----------------------------------------------------------------------------
void dotest(string a, string e="?", string id="") {
	char *P=strdup(a.c_str()), *p=P; int q;q=0;
	while (*p == '[') p++;
	int x0;
	sscanf(p, "%d%n", &x0, &q); p+=q;
	int x1;
	while (*p==' '||*p==',') p++;
	sscanf(p, "%d%n", &x1, &q); p+=q;
	int z = Hardwood().hwCount(x0,x1);
	ostringstream os;
	os << z;
	if(os.str() == e) {
		if (id != "") printf("TEST %s: ", id.c_str());
		printf("\033[01;32mOK\033[0m  got %s\n", os.str().c_str());
	} else {
		printf("\n");
		if (id != "") printf("TEST %s:\n", id.c_str());
		printf("Got: %s\n", os.str().c_str());
		printf("\033[01;31mExp\033[0m: %s\n\n", e.c_str());
	}
	free(P);
}

void doex(int t=-1) {
	if(t<0||t==0) dotest("1, 2", "0", "0");
	if(t<0||t==1) dotest("1, 3", "3", "1");
	if(t<0||t==2) dotest("92, 2", "32", "2");
	if(t<0||t==3) dotest("80, 90", "10501", "3");
	if(t<0||t==4) dotest("25, 12", "557", "4");
	if(t<0||t==5) dotest("3, 4", "28", "5");
	if(t<0||t==6) dotest("3, 5", "29", "6");
	if(t<0||t==7) dotest("77, 77", "8336", "7");
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		doex(-1);
	} else if (argc >= 2 && strcmp(argv[1], "-") == 0) {
		if (argc == 2) {
			string s=""; char buf[65536];
			while(gets(buf))s+=string(buf); dotest(s,"?");
		} else {
			string s="";
			for(int i=2; i<argc; i++) s+=string(argv[i])+" ";
			printf("Args: %s\n", s.c_str());
			dotest(s,"?");
		}
	} else {
		for (int i=1; i<argc; i++) doex(atoi(argv[i]));
	}
}
