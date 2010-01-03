import java.io.*;
import java.util.*;

/**
 * Пересечение двух окружностей. Пересечение может быть:
 *   1. пустым
 *   2. состоять из одной точки
 *   3. состоять из двух точек
 *   4. состоять из окружности
 *   
 * Во входном файле (2circles.in) заданы координаты центров и радиусы окружностей.
 * Координаты должны быть примерно одного порядка и не содержать много значащих цифр.
 * Все вычисления проводятся в типе <code>double</code>.
 * Пример:
 *   0 0 1
 *   1 0 1
 * 
 * @author Roman V Satyukov
 */
public class TwoCirclesIntersection implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	private static final double eps = 1e-9;
	private static final String problemName = "2circles";

	private void solve() throws IOException {
		Locale.setDefault(Locale.US);
		in = new BufferedReader(new FileReader(new File(problemName + ".in")));
		out = new PrintWriter(new File(problemName + ".out"));
		
		StringTokenizer st = new StringTokenizer(in.readLine());
		// Уравнение первой окружности: (x - x1)^2 + (y - y1)^2 = r1^2
		double x1 = Double.parseDouble(st.nextToken());
		double y1 = Double.parseDouble(st.nextToken());
		double r1 = Double.parseDouble(st.nextToken());
		
		// Уравнение второй окружности: (x - x2)^2 + (y - y2)^2 = r2^2
		st = new StringTokenizer(in.readLine());
		double x2 = Double.parseDouble(st.nextToken());
		double y2 = Double.parseDouble(st.nextToken());
		double r2 = Double.parseDouble(st.nextToken());
		
		// Вычитаем из первого уравнения второе: получается ax + by + c = 0 
		double a = -2 * (x1 - x2);
		double b = -2 * (y1 - y2);
		double c = x1 * x1 + y1 * y1 - r1 * r1 - x2 * x2 - y2 * y2 + r2 * r2;
		
		if (Math.abs(a) < eps && Math.abs(b) < eps) {
			// Концентрические окружности: x1 = x2, y1 = y2
			if (Math.abs(r1 - r2) < eps) {
				out.println("Circles coincide");
			} else {
				out.println("NONE");
			}
			in.close();
			out.close();
			return;
		}
		
		// Нормируем: делим a,b,c на sqrt(a^2 + b^2)
		double d = Math.sqrt(a * a + b * b);
		a /= d;
		b /= d;
		c /= d;
		
		// (x0,y0) - точка на прямой
		double x0 = -a * c;
		double y0 = -b * c;
		
		// Поставляем параметрическое представление прямой в первое уравнение
		// Получается уравнение t^2 + 2 * p * t + q = 0
		double p = -2 * b * (x0 - x1) + 2 * a * (y0 - y1);
		double q = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) - r1 * r1;
		d = p * p - q;
		if (d < -eps) {
			// Отрицательный дискриминант: нет решений
			out.println("NONE");
		} else if (Math.abs(d) < eps) {
			// Равный нулю дискриминант: одно решение
			out.println((x0 + b * p) + " " + (y0 - a * p));
		} else {
			// Больший нуля дискриминант: два решения
			double t1 = -p + Math.sqrt(d);
			double t2 = -p - Math.sqrt(d);
			out.println((x0 - b * t1) + " " + (y0 + a * t1));
			out.println((x0 - b * t2) + " " + (y0 + a * t2));
		}
		
		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new TwoCirclesIntersection()).start();
	}
	
	public void run() {
		try {
			solve();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
