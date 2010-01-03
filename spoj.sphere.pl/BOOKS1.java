// binary search + greedy
import java.io.*;
import java.util.*;

public class Main {
    boolean check(long maxWork, long[] a, int K, boolean print) {
        int N = a.length;
        int[] clerkId = new int[N];

        long s = 0;
        for (int i = N-1; i >= 0; i--) {
            if (a[i] > maxWork) return false;

            if (s + a[i] > maxWork || i+1 < K) {
                s = 0;
                if (--K <= 0) return false;
            }

            clerkId[i] = K;
            s += a[i];
        }

        if (print) {
            for (int i = 0; i < N; i++) {
                if (i != 0) {
                    if (clerkId[i-1] != clerkId[i])
                        System.out.print(" / ");
                    else
                        System.out.print(" ");
                }
                System.out.print(a[i]);
            }
            System.out.println();
        }

        return true;
    }

    public void run() throws IOException {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        for (int cs = 1; cs <= T; cs++) {
            int N = in.nextInt();
            int K = in.nextInt();

            long[] a = new long[N];
            for (int i = 0; i < N; i++)
                a[i] = in.nextLong();

            long left = 0, right = 6000000000L;
            while (right - left > 1) {
                long mid = (left + right) / 2;
                if (check(mid, a, K, false))
                    right = mid;
                else
                    left = mid;
            }

            check(right, a, K, true);
        }
    }

    public static void main(String args[]) throws IOException {
        new Main().run();
    }
}
