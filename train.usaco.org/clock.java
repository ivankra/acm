/*
ID: infnty1
PROB: clock
LANG: JAVA
*/
import java.io.*;
import java.util.*;
import java.util.regex.*;

class clock {
	static String spell(int n) {
		String[] a = { "zero", "one", "two", "three", "four", "five",
			"six", "seven", "eight", "nine", "ten", "eleven",
			"twelve", "thirteen", "fourteen", "fifteen", "sixteen",
			"seventeen", "eighteen", "nineteen" };
		String[] b = { "zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty" };

		if (n < 20)
			return a[n];
		else if ((n % 10) == 0)
			return b[n / 10];
		else
			return b[n / 10] + "-" + a[n % 10];
	}

	static String cap(String s) {
		return (s.substring(0, 1).toUpperCase() + s.substring(1));
	}

	static String time(int h, int m) {
		if (m == 0)
			return cap(spell(h)) + " o'clock";
		else if (m == 15)
			return "Quarter past " + spell(h);
		else if (m == 30)
			return cap(spell(h)) + " thirty";
		else if (m == 45)
			return "Quarter to " + spell(1 + (h % 12));
		else if (m < 45)
			return cap(spell(h)) + " " + spell(m);
		else
			return cap(spell(60 - m)) + " to " + spell(1 + (h % 12));
	}

	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(new FileReader("clock.in"));
		PrintWriter out = new PrintWriter(new FileWriter("clock.out"));
		int h, m;

		in.useDelimiter("[ \t\r\n:]+");
		h = in.nextInt();
		m = in.nextInt();

		out.printf("%s\n", time(h, m));

		out.close();
		System.exit(0);
	}
}

