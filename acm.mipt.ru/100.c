main() {
	int x=0, k, n;
	for (scanf("%d", &k); k-- && scanf("%d", &n); x^=n);
	printf("%s wins.\n",x?"First":"Second");
	return 0;
}

