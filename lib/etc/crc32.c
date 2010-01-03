/* A simple utilty which computes CRC32 checksum of files given to it
   as command-line arguments. */
#include <stdio.h>

#define POLYNOMIAL  0xEDB88320UL
#define BUFFER_SIZE 65536

unsigned long table[256];

/* Generates CRC lookup table for given polynomial. */
void make_table()
{
	int i, n;
	for (n = 0; n < 256; n++) {
		unsigned long t = n;
		for (i = 0; i < 8; i++)
			t = (t >> 1) ^ ((t & 1) == 0 ? 0 : POLYNOMIAL);
		table[n] = t;
	}
}

/* Processes a chunk of data. */
unsigned long update(unsigned long sum, unsigned char *buffer, size_t len)
{
	while (len != 0) {
		len--;
		sum = (sum >> 8) ^ table[(sum ^ (*buffer++)) & 0xff];
	}
	return sum;
}

/* Processes a single file. */
int do_file(const char *path)
{
	static unsigned char buf[BUFFER_SIZE];
	int n;
	unsigned long sum;
	FILE *fp;
	
	fp = fopen(path, "rb");
	if (fp == NULL) {
		fprintf(stderr, "%s: ", path);
		perror("fopen");
		return 1;
	}

	sum = 0xFFFFFFFFUL;
	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
		sum = update(sum, buf, n);
	sum ^= 0xFFFFFFFFUL;

	fclose(fp);

	printf("%s %.8lX\n", path, (unsigned long)sum);

	return 0;
}

int main(int argc, char *argv[])
{
	int i, e;

	if (argc == 1) {
		printf("Usage: %s file1 [file2] ...\n", argv[0]);
		return 1;
	}

	make_table();

	e = 0;
	for (i = 1; i < argc; i++)
		e += do_file(argv[i]);

	return e;
}
