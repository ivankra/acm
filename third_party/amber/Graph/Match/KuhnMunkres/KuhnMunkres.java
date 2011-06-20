import java.util.*;

class KuhnMunkres
{
	int N, M;
	int[][] graph;
	int[] link;
	int[] labelX, labelY;
	boolean[] usedX, usedY;
	
	boolean findPath(int i)
	{
		usedX[i] = true;
		for (int j = 0; j < M; j++)
			if (!usedY[j] && labelX[i] + labelY[j] == graph[i][j])
			{
				usedY[j] = true;
				if (link[j] == -1 || findPath(link[j]))
				{
					link[j] = i;
					return true;
				}
			}
		return false;
	}
	int maxWeightMatch()
	{
		link = new int[M];
		labelX = new int[N];
		labelY = new int[M];
		usedX = new boolean[N];
		usedY = new boolean[M];
		Arrays.fill(link, -1);
		Arrays.fill(labelX, 0);
		Arrays.fill(labelY, 0);
		for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					labelX[i] = Math.max(labelX[i], graph[i][j]);
		for (int k = 0; k < N; k++)
			while (true)
			{
				Arrays.fill(usedX, false);
				Arrays.fill(usedY, false);
				if (findPath(k)) break;

				int delta = Integer.MAX_VALUE;
				for (int i = 0; i < N; i++)
					if (usedX[i])
						for (int j = 0; j < M; j++)
							if (!usedY[j])
								delta = Math.min(delta, labelX[i] + labelY[j] - graph[i][j]);
				if (delta == 0) break;
				for (int i = 0; i < N; i++)
					if (usedX[i])
						labelX[i] += delta;
				for (int i = 0; i < M; i++)
					if (usedY[i])
						labelY[i] -= delta;
			}
		int result = 0;
		for (int i = 0; i < N; i++)
			result += labelX[i];
		for (int i = 0; i < M; i++)
			result += labelY[i];
		return result;
	}
	void solve()
	{
		Scanner input = new Scanner(System.in);
		
		while (input.hasNextInt())
		{
			N = input.nextInt();
			M = input.nextInt();
			graph = new int[N][M];
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					graph[i][j] = input.nextInt();

			System.out.println(maxWeightMatch());
		}
	}
}
