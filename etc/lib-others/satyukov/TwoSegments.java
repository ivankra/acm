import java.io.*;
import java.util.*;

/**
 * Пересечение двух отрезков (ненулевой длины).
 * Пересечение может быть:
 *   1. пустым
 *   2. состоять из одной точки
 *   3. быть некоторым отрезком ненулевой длины
 *   
 * Во входном файле (2segments.in) заданы координаты концов двух отрезков.
 * Координаты должны быть целыми числами, по модулю <= 10000.
 * Пример:
 *   -1 0 1 0
 *   0 -1 0 1
 * 
 * @author Roman V Satyukov
 */
public class TwoSegments implements Runnable {
    private Scanner in;
    private PrintWriter out;
    private static final String problemName = "2segments";
    
    /**
     * Проверяет что <code>x0</code> лежит между <code>x1</code> и <code>x2</code>.
     */
    private boolean bt(int x0, int x1, int x2) {
        return ((x1 <= x0) && (x0 <= x2)) || ((x2 <= x0) && (x0 <= x1));
    }
    
    private int sign(long value) {
        return (value > 0) ? 1 : (value == 0) ? 0 : -1;
    }
    
    private void printAnswer(double x, double y) {
        out.println(x + " " + y);
    }

    private void printAnswer(int x1, int y1, int x2, int y2) {
        if (x1 == x2 && y1 == y2) {
            printAnswer(x1, y1);
            return;
        }
        if (x1 > x2 || (x1 == x2) && (y1 > y2)) {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        out.println(x1 + " " + y1 + " --- " + x2 + " " + y2);
    }
    
    /**
     * Проверяет, пересекаются ли два отрезка:
     *   1. Проверяет что пересекаются ограничивающие их прямоугольники.
     *   2. Проверяет что каждый отрезок пересекает прямую, содержащую другой отрезок.
     */
    private boolean intersects(int[] x, int[] y) {
        int a1 = y[0] - y[1];
        int b1 = x[1] - x[0];
        long c1 = -a1 * x[0] - b1 * y[0];
        int a2 = y[2] - y[3];
        int b2 = x[3] - x[2];
        long c2 = -a2 * x[2] - b2 * y[2];
        
        int px1 = Math.max(Math.min(x[0], x[1]), Math.min(x[2], x[3]));
        int py1 = Math.max(Math.min(y[0], y[1]), Math.min(y[2], y[3]));
        int px2 = Math.min(Math.max(x[0], x[1]), Math.max(x[2], x[3]));
        int py2 = Math.min(Math.max(y[0], y[1]), Math.max(y[2], y[3]));
        if (px1 > px2 || py1 > py2) {
            return false;
        }
        if (sign(a1 * x[2] + b1 * y[2] + c1) * sign(a1 * x[3] + b1 * y[3] + c1) == 1) {
            return false;
        }
        if (sign(a2 * x[0] + b2 * y[0] + c2) * sign(a2 * x[1] + b2 * y[1] + c2) == 1) {
            return false;
        }
        return true;
    }

    private void solve() throws IOException {
        int[] x = new int[4];
        int[] y = new int[4];
        for (int i = 0; i < 4; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }
        if (!intersects(x, y)) {
            out.println("empty");
            return;
        }
        
        // Уравение первой прямой: a1 * x + b1 * y + c1 = 0
        int a1 = y[0] - y[1];
        int b1 = x[1] - x[0];
        long c1 = -a1 * x[0] - b1 * y[0];
        // Уравение второй прямой: a2 * x + b2 * y + c2 = 0
        int a2 = y[2] - y[3];
        int b2 = x[3] - x[2];
        long c2 = -a2 * x[2] - b2 * y[2];
        int d = a1 * b2 - a2 * b1;
        long d1 = -(c1 * b2 - c2 * b1);
        long d2 = -(a1 * c2 - a2 * c1);
        if (d != 0) {
            printAnswer(1.0 * d1 / d, 1.0 * d2 / d);
        } else {
            // Два отрезка лежат на одной прямой.
            if (bt(x[0], x[2], x[3]) && bt(y[0], y[2], y[3]) && bt(x[1], x[2], x[3]) && bt(y[1], y[2], y[3])) {
                printAnswer(x[0], y[0], x[1], y[1]);
            } else if (bt(x[2], x[0], x[1]) && bt(y[2], y[0], y[1]) && bt(x[3], x[0], x[1]) && bt(y[3], y[0], y[1])) {
                printAnswer(x[2], y[2], x[3], y[3]);
            } else {
                int x1 = 0, y1 = 0;
                int x2 = 0, y2 = 0;
                for (int i = 0; i < 2; i++) {
                    if (bt(x[i], x[2], x[3]) && bt(y[i], y[2], y[3])) {
                        x1 = x[i];
                        y1 = y[i];
                    }
                }
                for (int i = 2; i < 4; i++) {
                    if (bt(x[i], x[0], x[1]) && bt(y[i], y[0], y[1])) {
                        x2 = x[i];
                        y2 = y[i];
                    }
                }
                printAnswer(x1, y1, x2, y2);
            }
        }
    }

    public static void main(String[] args) {
        new Thread(new TwoSegments()).start();
    }
    
    public void run() {
        try {
            in = new Scanner(new File(problemName + ".in"));
            out = new PrintWriter(new File(problemName + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
