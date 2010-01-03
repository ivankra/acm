int phi[2048];

void make_phi() {
	unsigned long long r = rdtsc();

	for (int i = 0; i < 2048; i++)
		phi[i] = 1;

	for (int p = 2; p < 2048; p++) {
		if (phi[p] != 1) continue;

		for (int q = p; q < 2048; q += p)
			phi[q] *= p - 1;

		for (int r = p*p; r < 2048; r *= p)
			for (int q = r; q < 2048; q += r)
				phi[q] *= p;
	}
}
