#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int base, denom, used, P[50], Q[50], PN, QN;
string result;
int firstDigits;
char theDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void formatSolution()
{
	static char buf[100];
	sprintf(buf, "%d %d ", base, denom);
	result = buf;
	for (int i = PN-1; i >= 0; i--) result += theDigits[P[i]];
	result += "/";
	for (int i = QN-1; i >= 0; i--) result += theDigits[Q[i]];
}

int rec(int n, int carry)
{
	if ((firstDigits & ~used) == 0 && n < PN) return 0;

	if (n == PN) {
		if (QN > PN) {
			if (used & (1 << carry)) return 0;
			Q[n] = carry;
		} else if (carry != 0) {
			return 0;
		}

		formatSolution();
		return 1;		
	}

static int sequence[]={
2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,25,26,27,1,
0};
//	for (int digit = 1; digit < base; digit++) {
	for (int i = 0; sequence[i] != 0; i++) {
		int digit = sequence[i];
		if (digit >= base) continue;

		if (used & (1 << digit)) continue;

		int t = digit * denom + carry;
		P[n] = digit;
		Q[n] = t % base;
		t /= base;
		if ((used & (1 << Q[n])) != 0 || Q[n] == P[n]) continue;

		used |= 1 << digit;
		used |= 1 << Q[n];
		if (rec(n+1, t)) return 1;
		used &= ~((1 << digit) | (1 << Q[n]));
	}

	return 0;
}

string solve(int b, int den)
{
	assert(2 <= b && b <= 27);
	assert(2 <= den && den <= b-1);

	base = b;
	denom = den;
	used = 1 << 0;
	PN = (base - 1) / 2;
	QN = base / 2;
	assert(PN+QN == base-1);
	result = "";

	firstDigits = 0;
	for (int d = 1; d <= base-1; d++) {
		if (PN == QN) {
			if (d*denom >= base) continue;
		} else {
			if (d == 1) continue;    // 1*base + [0..base-1] ==> leading digit of Q is 1.
			if (d*denom+base-1 < base) continue;
		}
		firstDigits |= 1 << d;
//		printf("{%d}", d);fflush(stdout);
	}
//	printf(" PN=%d QN=%d\n",PN,QN);

	if (rec(0, 0)) {
		return result;
	}

	return "";
}

int main()
{
	int b = 27, n = 26;

/*	for (;;) {
		if (b < 2) { b = 2; continue; }
		if (b > 27) break;
		if (n < 2) { n = 2; continue; }
		if (n >= b) { b++; n = 2; continue; }
//if (n % 2 != 1 && n != 26) { n++; continue; }

		printf("base=%d n=%d\n", b, n);
		string s = solve(b, n);
		printf("[%s]\n", s.c_str());

		n++;
	}
*/
#if 1
string cache[32][32];
cache[ 3][ 2] = "3 2 1/2";
cache[ 4][ 2] = "4 2 3/12";
cache[ 4][ 3] = "4 3 3/21";
cache[ 5][ 2] = "NO SOLUTION";
cache[ 5][ 3] = "";
cache[ 5][ 4] = "";
cache[ 6][ 2] = "";
cache[ 6][ 3] = "";
cache[ 6][ 4] = "6 4 51/324";
cache[ 6][ 5] = "6 5 41/325";
cache[ 7][ 2] = "7 2 162/354";
cache[ 7][ 3] = "";
cache[ 7][ 4] = "7 4 126/543";
cache[ 7][ 5] = "";
cache[ 7][ 6] = "";
cache[ 8][ 2] = "8 2 572/1364";
cache[ 8][ 3] = "8 3 671/2453";
cache[ 8][ 4] = "8 4 563/2714";
cache[ 8][ 5] = "8 5 671/4235";
cache[ 8][ 6] = "8 6 521/3746";
cache[ 8][ 7] = "8 7 421/3567";
cache[ 9][ 2] = "9 2 1658/3427";
cache[ 9][ 3] = "9 3 2751/8463";
cache[ 9][ 4] = "9 4 1542/6378";
cache[ 9][ 5] = "9 5 1625/8437";
cache[ 9][ 6] = "9 6 1425/8763";
cache[ 9][ 7] = "";
cache[ 9][ 8] = "";
cache[10][ 2] = "10 2 7932/15864";
cache[10][ 3] = "10 3 5832/17496";
cache[10][ 4] = "10 4 3942/15768";
cache[10][ 5] = "10 5 9723/48615";
cache[10][ 6] = "10 6 2943/17658";
cache[10][ 7] = "10 7 7614/53298";
cache[10][ 8] = "10 8 9321/74568";
cache[10][ 9] = "10 9 8361/75249";
cache[11][ 2] = "11 2 48751/963A2";
cache[11][ 3] = "";
cache[11][ 4] = "11 4 27651/A8394";
cache[11][ 5] = "";
cache[11][ 6] = "11 6 15A63/92847";
cache[11][ 7] = "";
cache[11][ 8] = "";
cache[11][ 9] = "";
cache[11][10] = "";
cache[12][ 2] = "12 2 98B32/175A64";
cache[12][ 3] = "12 3 A56B1/274893";
cache[12][ 4] = "12 4 6AB51/237984";
cache[12][ 5] = "12 5 96421/3B78A5";
cache[12][ 6] = "12 6 B8923/5A4716";
cache[12][ 7] = "12 7 8AB31/524697";
cache[12][ 8] = "12 8 9AB21/673548";
cache[12][ 9] = "12 9 AB471/826539";
cache[12][10] = "12 10 B4321/95678A";
cache[12][11] = "12 11 74821/6935AB";
cache[13][ 2] = "13 2 3B6541/79CA82";
cache[13][ 3] = "";
cache[13][ 4] = "13 4 28B531/A967C4";
cache[13][ 5] = "13 5 243C71/B86A95";
cache[13][ 6] = "13 6 19B6C3/A74285";
cache[13][ 7] = "";
cache[13][ 8] = "13 8 15C462/B879A3";
cache[13][ 9] = "13 9 13C485/B972A6";
cache[13][10] = "13 10 134B56/C79A28";
cache[13][11] = "";
cache[13][12] = "";
cache[14][ 2] = "";
cache[14][ 3] = "14 3 B79354/268DA1C";
cache[14][ 4] = "14 4 CD5621/39B7A84";
cache[14][ 5] = "14 5 9D6821/37B4CA5";
cache[14][ 6] = "14 6 A93B51/47D8C26";
cache[14][ 7] = "";
cache[14][ 8] = "14 8 4CD631/2B597A8";
cache[14][ 9] = "14 9 CB7621/835AD49";
cache[14][10] = "14 10 C47D21/8B3956A";
cache[14][11] = "14 11 C2D561/98473AB";
cache[14][12] = "14 12 D54321/B6789AC";
cache[14][13] = "14 13 739421/6A58BCD";
cache[15][ 2] = "15 2 4DBA731/9C85E62";
cache[15][ 3] = "";
cache[15][ 4] = "15 4 2DC8761/BA53E94";
cache[15][ 5] = "";
cache[15][ 6] = "15 6 258BC41/E37AD96";
cache[15][ 7] = "";
cache[15][ 8] = "15 8 18BD763/CA52E49";
cache[15][ 9] = "";
cache[15][10] = "15 10 13AE6D2/C7498B5";
cache[15][11] = "";
cache[15][12] = "15 12 1248A73/DC9E5B6";
cache[15][13] = "";
cache[15][14] = "";
cache[16][ 2] = "16 2 E9C7B52/1D38F6A4";
cache[16][ 3] = "16 3 DE78C51/29B6A4F3";
cache[16][ 4] = "16 4 FAD6721/3EB59C84";
cache[16][ 5] = "16 5 B8F7621/39CD4EA5";
cache[16][ 6] = "16 6 9EA5421/3B7DF8C6";
cache[16][ 7] = "16 7 AF68321/4CBD95E7";
cache[16][ 8] = "16 8 FCD4B23/7E6A5918";
cache[16][ 9] = "16 9 DE28431/7CF6A5B9";
cache[16][10] = "16 10 D7EBC21/86F3594A";
cache[16][11] = "16 11 79E8421/53CFAD6B";
cache[16][12] = "16 12 E9B3521/AF467D8C";
cache[16][13] = "16 13 5EB9321/4CF678AD";
cache[16][14] = "16 14 F654321/D789ABCE";
cache[16][15] = "16 15 B7D3821/AC5649EF";
cache[17][ 2] = "17 2 4F3E8651/9D7BGCA2";
cache[17][ 3] = "17 3 59ADE421/GBF78C63";
cache[17][ 4] = "17 4 2B9G8361/AC5EFD74";
cache[17][ 5] = "17 5 368C7D21/GF9B4EA5";
cache[17][ 6] = "17 6 23CGA841/D59EBF76";
cache[17][ 7] = "17 7 23DGA841/F9CE56B7";
cache[17][ 8] = "17 8 15D9F832/AC6B4E7G";
cache[17][ 9] = "17 9 196B2753/DG8F4ECA";
cache[17][10] = "17 10 19D5G642/FCE8AB73";
cache[17][11] = "17 11 168EA942/F3C7DGB5";
cache[17][12] = "17 12 16AC8D42/GB9E35F7";
cache[17][13] = "17 13 1478EB52/G6CD3AF9";
cache[17][14] = "17 14 13968472/GFC5DAEB";
cache[17][15] = "";
cache[17][16] = "";
cache[18][ 2] = "";
cache[18][ 3] = "18 3 GBE98541/2DH7A6FC3";
cache[18][ 4] = "18 4 D6EG8731/2H95BFAC4";
cache[18][ 5] = "18 5 DHC69821/3FG7EB4A5";
cache[18][ 6] = "18 6 BGE98451/3HAF2D7C6";
cache[18][ 7] = "18 7 HDBC8421/6G59F3AE7";
cache[18][ 8] = "18 8 HA9BF321/7EC54D6G8";
cache[18][ 9] = "";
cache[18][10] = "18 10 G85FE631/92B4DH7CA";
cache[18][11] = "18 11 E3HFA621/8C7G95D4B";
cache[18][12] = "18 12 HFAE5421/BG7398D6C";
cache[18][13] = "18 13 AG693421/7FECB5H8D";
cache[18][14] = "18 14 BG5DH321/94C8F67AE";
cache[18][15] = "18 15 7HD9G321/6BE548ACF";
cache[18][16] = "18 16 H7654321/F89ABCDEG";
cache[18][17] = "18 17 95C7B421/8E6D3AFGH";
cache[19][ 2] = "19 2 5HFED9431/BGCA7I862";
cache[19][ 3] = "";
cache[19][ 4] = "19 4 3AFIDC721/E56HGB984";
cache[19][ 5] = "";
cache[19][ 6] = "19 6 28BAF9431/EDC7GH5I6";
cache[19][ 7] = "";
cache[19][ 8] = "19 8 24CFB6931/HI7AEDG58";
cache[19][ 9] = "";
cache[19][10] = "19 10 1G96E2753/ICHA84FDB";
cache[19][11] = "";
cache[19][12] = "19 12 14BD8F632/EH79ACGI5";
cache[19][13] = "";
cache[19][14] = "19 14 14F7IBE32/HA6GDC859";
cache[19][15] = "";
cache[19][16] = "19 16 138B6G792/IH4AEF5CD";
cache[19][17] = "";
cache[19][18] = "";
cache[20][ 2] = "20 2 IFDG9E532/1HB7CJ8A64";
cache[20][ 3] = "20 3 FEGCA8D61/2749HB5JI3";
cache[20][ 4] = "20 4 IHDC67J21/3FAE95BG84";
cache[20][ 5] = "20 5 DIHCJ6721/39E84GBFA5";
cache[20][ 6] = "20 6 D4FG9B521/3J8EIH7AC6";
cache[20][ 7] = "20 7 JBIDFC421/6H3AG958E7";
cache[20][ 8] = "20 8 HIFDJ6421/73A5BE9CG8";
cache[20][ 9] = "20 9 AGJ5E6321/4HCDB8F7I9";
cache[20][10] = "20 10 FIGDE9523/7J86H4CB1A";
cache[20][11] = "20 11 I8FE67431/A2GCH9J5DB";
cache[20][12] = "20 12 8JAGB6321/57E9IFDH4C";
cache[20][13] = "20 13 5HBJ4A721/3G8F9IEC6D";
cache[20][14] = "20 14 9FBJA5421/6GI7D3CH8E";
cache[20][15] = "20 15 GJ89D5321/CEB74IH6AF";
cache[20][16] = "20 16 J45IBD321/F78EH6A9CG";
cache[20][17] = "20 17 7GJ9F4321/6D8B5IACEH";
cache[20][18] = "20 18 J87654321/H9ABCDEFGI";
cache[20][19] = "20 19 A3C6B7521/9D8E4FHGIJ";
cache[21][ 2] = "21 2 9GI5HA7431/JCFBDKE862";
cache[21][ 3] = "";
cache[21][ 4] = "21 4 3D7JIH9521/EBAGC6FK84";
cache[21][ 5] = "21 5 3BE7J9F421/HG8ID6CKA5";
cache[21][ 6] = "21 6 38IEGDA521/KB74FHJ9C6";
cache[21][ 7] = "";
cache[21][ 8] = "21 8 25EGKCA641/I3D9HFJ7B8";
cache[21][ 9] = "21 9 25B8DHF431/K7IEJCAG69";
cache[21][10] = "21 10 1DHI4FB632/GCAE587J9K";
cache[21][11] = "";
cache[21][12] = "21 12 1CGF9I8542/J6BHDAEK73";
cache[21][13] = "21 13 1C8IGF6432/KEAD79HBJ5";
cache[21][14] = "21 14 13JKHB8542/GD6IECA9F7";
cache[21][15] = "";
cache[21][16] = "21 16 14AHCKF632/J958IGDE7B";
cache[21][17] = "21 17 14CI9E5732/KF8JHB6GAD";
cache[21][18] = "21 18 137H8B5C42/KIEJ6DG9AF";
cache[21][19] = "";
cache[21][20] = "";
cache[22][ 2] = "22 2 KGDHAF9732/1JB5CL8IE64";
cache[22][ 3] = "22 3 GIDHAE7541/26BJ89KLFC3";
cache[22][ 4] = "22 4 KJ9FDE5721/3HBGIACL684";
cache[22][ 5] = "22 5 LGJBC76321/4KI9DHE8FA5";
cache[22][ 6] = "22 6 HADE975321/4GJFKBL8IC6";
cache[22][ 7] = "22 7 K8BI4C5321/6AFGH9JDLE7";
cache[22][ 8] = "22 8 HL3KI75421/6BF9CEDJAG8";
cache[22][ 9] = "22 9 GEBC4D8321/6HKFLJA75I9";
cache[22][10] = "22 10 F7GH5E4321/6LBDIC9J8KA";
cache[22][11] = "22 11 LIHGF69523/AK8J7E4DC1B";
cache[22][12] = "22 12 KLFH2G6431/B9ID7AJ85EC";
cache[22][13] = "22 13 LJAFE68321/CKB759GHI4D";
cache[22][14] = "22 14 HFAJ8C4321/B5IK79GDL6E";
cache[22][15] = "22 15 EJCIL95421/A37GKD6BH8F";
cache[22][16] = "22 16 BLJIH67321/8FK9ECD45AG";
cache[22][17] = "22 17 JIAK4G5321/F769DEBL8CH";
cache[22][18] = "22 18 F9G5JA4321/CDL6HK78BEI";
cache[22][19] = "22 19 FL7K654321/DH9IB8ACEGJ";
cache[22][20] = "22 20 L987654321/JABCDEFGHIK";
cache[22][21] = "22 21 D7I5BF8421/CGA963EHJKL";
cache[23][ 2] = "23 2 9LHGI7EB431/JKCADF5M862";
cache[23][ 3] = "";
cache[23][ 4] = "23 4 5FKGA97B321/MHDJIE6LC84";
cache[23][ 5] = "";
cache[23][ 6] = "23 6 3DAHGJKF521/LBIE948M7C6";
cache[23][ 7] = "";
cache[23][ 8] = "23 8 2ADGLE76541/JFHKBMC3I98";
cache[23][ 9] = "";
cache[23][10] = "23 10 25CLK8D6431/M9EBJGHFI7A";
cache[23][11] = "";
cache[23][12] = "23 12 1KIEB8A2753/MJGCL964HFD";
cache[23][13] = "";
cache[23][14] = "23 14 1CFJ8M76432/LGEIAD9HBK5";
cache[23][15] = "";
cache[23][16] = "23 16 13LMACB8542/IH6E7FKGDJ9";
cache[23][17] = "";
cache[23][18] = "23 18 14MEAC8H632/LKG75FJBI9D";
cache[23][19] = "";
cache[23][20] = "23 20 135D9BLGE42/MIJF68KA7CH";
cache[23][21] = "";
cache[23][22] = "";
cache[24][ 2] = "24 2 MKFDJBG9652/1LH73EN8ICA4";
cache[24][ 3] = "24 3 IHLFKEB7A41/285GNDJ9M6C3";
cache[24][ 4] = "24 4 KMFDGNA7921/3BIE6JLH5C84";
cache[24][ 5] = "24 5 MCDN6I87321/4GELK9JHBFA5";
cache[24][ 6] = "24 6 MLFKGDAB721/5H9N438EJIC6";
cache[24][ 7] = "24 7 NC4MJG85321/6KDAFHI9BLE7";
cache[24][ 8] = "24 8 AMHLIEBC751/3FDN64JK29G8";
cache[24][ 9] = "24 9 LHFBKD65421/83EJAGN7MCI9";
cache[24][10] = "24 10 DM8GCNB4321/5J7EL9IFH6KA";
cache[24][11] = "24 11 EKIFNA54321/6JCD7HG8L9MB";
cache[24][12] = "24 12 JMKFIDB8543/9NA7L6HG2E1C";
cache[24][13] = "24 13 HCLAIG76431/9BNEK2JM85FD";
cache[24][14] = "24 14 MHGLB985321/D67KCFAINJ4E";
cache[24][15] = "24 15 KAHE5974321/CIGNL8JBDM6F";
cache[24][16] = "24 16 KFJ7MB95421/DICL6NE3AH8G";
cache[24][17] = "24 17 CG7LKM65321/8NDEBJI9F4AH";
cache[24][18] = "24 18 N4BEAD65321/H98GJLMFK7CI";
cache[24][19] = "24 19 M7DGLI84321/HFNK95CB6AEJ";
cache[24][20] = "24 20 F6ME9B54321/CHIJNL87ADGK";
cache[24][21] = "24 21 8AMK6B54321/79DNHFJCEGIL";
cache[24][22] = "24 22 NA987654321/LBCDEFGHIJKM";
cache[24][23] = "24 23 D6I3J5E7421/CHB9FA8GKLMN";
cache[25][ 2] = "25 2 BMEL7JC98531/NK4HFDOIGA62";
cache[25][ 3] = "25 3 5BMJNDE87421/GAI9KFHOLC63";
cache[25][ 4] = "25 4 5ANGKFM96321/LIJH7DEBOC84";
cache[25][ 5] = "25 5 4NJDCL879321/OIMHE6GBKFA5";
cache[25][ 6] = "25 6 3EJF5KA78421/LDHG9MBINOC6";
cache[25][ 7] = "";
cache[25][ 8] = "25 8 2DHNBLEA5431/K9ICJMF6G7O8";
cache[25][ 9] = "25 9 23DIGAF87541/J6NHMKCOELB9";
cache[25][10] = "25 10 28KHBE9C7431/ND6OFIJMLG5A";
cache[25][11] = "25 11 25LGIMFA6431/OED97NJCHK8B";
cache[25][12] = "25 12 1G8HK7E95632/JL4DIFMACNBO";
cache[25][13] = "25 13 1CMKBD8A2753/JHLFON964IGE";
cache[25][14] = "25 14 1DEOGHCA6542/LF9K8JNIBM73";
cache[25][15] = "";
cache[25][16] = "25 16 1ABIDJG56432/MHCLKE98NFO7";
cache[25][17] = "25 17 1A6ILDB87542/NOEKG3HFMCJ9";
cache[25][18] = "25 18 17JMILDG6432/NF89ECKHAO5B";
cache[25][19] = "25 19 179LNA4E6532/OFCGJIBKHM8D";
cache[25][20] = "25 20 15KDC9H86432/OGAJMILEN7BF";
cache[25][21] = "25 21 14FJGB8L9532/OM6CKDANI7EH";
cache[25][22] = "25 22 136ANIHC7542/OLGFMB9K8DEJ";
cache[25][23] = "";
cache[25][24] = "";
cache[26][ 2] = "26 2 OKJLCHB97532/1NFDGP8MIEA64";
cache[26][ 3] = "26 3 ENLKMH5B8432/1IJDAFPG7OC96";
cache[26][ 4] = "26 4 APIENB9L5432/1HOM7FJD6KGC8";
cache[26][ 5] = "26 5 7DNJMGOC5432/1BHEL96I8PKFA";
cache[26][ 6] = "26 6 P1EBGL7F6432/5K98HMNJDAOIC";
cache[26][ 7] = "26 7 4NOFPDKA6532/18BG7MICJH9LE";
cache[26][ 8] = "26 8 MNKL9IBC5432/718AEPHDJF6OG";
cache[26][ 9] = "26 9 JPDAFE875432/6NLGH9OMCKB1I";
cache[26][10] = "26 10 MBHJINEA6532/8GCLF71DO9P4K";
cache[26][11] = "26 11 DBAPKE986432/5HLGNI1OCFJ7M";
cache[26][12] = "26 12 PGHMKEF75432/BLI6DCJ189NAO";
cache[26][13] = "26 13 LJOHBKC97523/AMP8IN64GFE1D";
cache[26][14] = "26 14 MAJFLIB97643/C1KEDHO2PN85G";
cache[26][15] = "26 15 CNP9I1D86532/7BLGFAMHJEOK4";
cache[26][16] = "26 16 E5MGPH197432/8JFOBKCLIADN6";
cache[26][17] = "26 17 KCNO6PJ75342/DABGMELFI91H8";
cache[26][18] = "26 18 JHN13FM86542/DG9OKCPBI7ELA";
cache[26][19] = "26 19 EHFODB984532/AIMGNL7KP1J6C";
cache[26][20] = "26 20 B4DLPI7A6532/8FCGNK1HMJO9E";
cache[26][21] = "26 21 JH5BEOD76432/FMNA91KILP8CG";
cache[26][22] = "26 22 MKGE1HD85432/J7BPNAL6O9CFI";
cache[26][23] = "26 23 9LBNFJ765432/8HPDMO1ACEGIK";
cache[26][24] = "26 24 OPBA98765432/N1CDEFGHIJKLM";
cache[26][25] = "26 25 E8JBLCG65742/DKAI9H3FP1MNO";
cache[27][ 2] = "27 2 7PNLJHEDB9532/FOKGC81QMIA64";
cache[27][ 4] = "27 4 1QINFJ2AB6543/7PLD8M9EHOKGC";
cache[27][ 6] = "27 6 1KMNCFQJB7643/AH25LEP8DG9OI";
cache[27][ 8] = "27 8 1INGJEAC98643/DFQPL72HKBM5O";
cache[27][10] = "27 10 2G3NEFKI98654/PQBJAMHLC17OD";
cache[27][12] = "27 12 1GQOBCLA86543/JEPN2IDFHK7M9";
cache[27][14] = "27 14 1GNO2QBC49753/MKADEIP86LJHF";
cache[27][16] = "27 16 1E7JPQG985643/OCFMAKIDN2HBL";
cache[27][18] = "27 18 1CP9JNH8A7534/QGOD6KEFMLB2I";
cache[27][20] = "27 20 18OIBMFD9A453/QG7HKJCNPE2L6";
cache[27][22] = "27 22 15KBPDOAE6743/QIHJL8NFG2M9C";
cache[27][24] = "27 24 12MPGJCL76543/QEAKN89OBDFHI";
// base=27 n=3,5,7,...,25, 26 -?

	while (scanf("%d %d", &b, &n) == 2 && b > 0) {
		if (cache[b][n] == "") abort();
		printf("%s\n", cache[b][n].c_str());
	}
#endif
}
