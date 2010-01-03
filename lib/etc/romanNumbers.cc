
int romanToDecimal(const char *s) {
	static int val[256]={-1};
	if (val[0] < 0) {
		int a[] = {1, 5, 10, 50, 100, 500, 1000 };
		for (int i = 0; i < 256; i++) val[i] = 0;
		for (int i = 0; i < 7; i++) val["IVXLCDM"[i]] = a[i];
	}

	int res = 0;
	for (; *s; s++) {
		res += val[*s];
		for (char *t = s+1; *t; t++) {
			if (val[*t] > val[*s]) {
				res -= 2*val[*s];
				break;
			}
		}
	}
	return res;
}
