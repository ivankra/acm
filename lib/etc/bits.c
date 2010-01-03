
unsigned signed_to_unsigned(int x)
{
	return (x < 0) ? (1 + ~(unsigned)(-x)) : (unsigned)x;
}

int unsigned_to_signed(unsigned x)
{
	return (x & 0x80000000) ? -(1 + ~x) : x;
}
