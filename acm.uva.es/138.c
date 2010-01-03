int printf(const char *, ...);

int main(void)
{
	printf(
		"         6         8\n"
		"        35        49\n"
		"       204       288\n"
		"      1189      1681\n"
		"      6930      9800\n"
		"     40391     57121\n"
		"    235416    332928\n"
		"   1372105   1940449\n"
		"   7997214  11309768\n"
		"  46611179  65918161\n"
	);
	return 0;
}

/*
FullSimplify[Sum[i, {i, 1, h - 1}] - Sum[i, {i, h + 1, n}]]
Reduce[{h h - n(n + 1)/2 == 0, h > 1, n > 1}, {h, n}, Integers]
% /. C[1] -> z
Reduce[{%, z == #}, {h, n}, Integers] & /@ Range[2, 12]
*/
