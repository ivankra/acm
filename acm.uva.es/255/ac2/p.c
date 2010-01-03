
int write(int, const char *, int);
int read(int, char *, int);

static int between[8][8][8], isdig[256];
static char inbuf[65536], *inp, *inmax;
static char outbuf[65536], *outp;
static int k, q, p;

#define BETWEEN(x,a,b) \
             (((a)<(b)) ? (((a)<(x)) && ((x)<(b))) : (((b)<(x)) && ((x)<(a))))

int main()
{
	register int i;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

	for (i = 0; i < 8; i++) {
		int j, m;
		for (j = 0; j < 8; j++) {
			for (m = 0; m < 8; m++)
				between[i][j][m] = BETWEEN(i,j,m);
		}
	}

#define GET(var, eofcode) { \
	for (var = 0, i = 0;;) { \
		if (inp >= inmax) { \
			inmax = inbuf + read(0, inp=inbuf, sizeof(inbuf)); \
                        if (inmax <= inbuf) { \
				inmax = inbuf; \
				break; \
			} \
		} \
		if (isdig[(unsigned)*inp]){ \
			var = var * 10 + *inp++ - '0'; \
			i++; \
	        } else if (i > 0) { \
			break; \
		} else { \
		        inp++; \
                } \
	} \
	if (i == 0) eofcode \
}

#define PUT(s) { register char *p = s; while (*p) *outp++ = *p++; }

	for (outp = outbuf, inmax = inbuf, inp = inbuf;;) {
		if ((outp + 1024) > &outbuf[sizeof(outbuf)]) {
			write(1, outbuf, outp - outbuf);
			outp = outbuf;
		}

		GET(k, { goto ex; })
		GET(q, { goto ex; })
		GET(p, { goto ex; })

		if (k == q) {
			PUT("Illegal state\n")
			continue;
		}

		if (p == k || p == q) {
			PUT("Illegal move\n")
			continue;
		}

		if ((q >> 3) == (p >> 3)) {
			if ((k >> 3) == (p >> 3) &&
			    between[k & 7][p & 7][q & 7]) {
				PUT("Illegal move\n")
				continue;
			}
		} else if ((q & 7) == (p & 7)) {
			if ((k & 7) == (p & 7) &&
			    between[k >> 3][p >> 3][q >> 3]) {
				PUT("Illegal move\n")
				continue;
			}
		} else {
			PUT("Illegal move\n")
			continue;
		}

		if (((k & 7) != 7 && (k + 1) == p) ||
		    ((k & 7) != 0 && (k - 1) == p) ||
		    (k + 8) == p || (k - 8) == p)
			PUT("Move not allowed\n")
		else if ((k ==  0 && p ==  9) || (k ==  7 && p == 14) ||
			 (k == 56 && p == 49) || (k == 63 && p == 54))
			PUT("Stop\n")
		else
			PUT("Continue\n")
	}

ex:
	if (outp != outbuf)
		write(1, outbuf, outp - outbuf);

	return 0;
}
