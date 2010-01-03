#include <stdio.h>
#include <sys/time.h>

long long usec() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000LL + tv.tv_usec;
}

static inline unsigned long long rdtsc() {
	unsigned long long r;
	asm("rdtsc" : "=A"(r));
	return r;
}



int main() {
	printf("usec: %lld\n", usec());
	printf("rdtsc: %lld\n", rdtsc());

	long long t = usec() + 100000;
	unsigned long long r = rdtsc();
	while (usec() < t);
	printf("cpu ~ %llumhz\n", (rdtsc()-r)/1000000*10);
}
