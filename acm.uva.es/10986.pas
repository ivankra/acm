Const
	MaxN = 20000;
	MaxM = 100000;
	INF = $7FFFFFFF;

Var
	N, HeapSize: LongInt;
	Dist, Heap, Pos: Array[1..MaxN] of LongInt;
	{ Invariant: Heap[Pos[x]] = x, for all x in heap }

	{ Adjacency lists }
	Head: Array[1..MaxN] of LongInt;
	Adj: Array[1..MaxM] of Record
		v, cost: LongInt;
		next: LongInt;    { index of next record, or 0 if last }
	End;

Procedure HeapSwap(i, j: integer);
Var
	t: integer;
Begin
	t := Heap[i]; Heap[i] := Heap[j]; Heap[j] := t;
	Pos[Heap[i]] := i;
	Pos[Heap[j]] := j;
End;

Procedure HeapUp(i: LongInt);
Begin
	While (i > 1) And (Dist[Heap[i]] < Dist[Heap[i Div 2]]) Do
	Begin
		HeapSwap(i, i Div 2);
		i := i Div 2;
	End;
End;

Procedure HeapDown(i: LongInt);
Var
	j: LongInt;
Begin
	While 2*i <= HeapSize Do
	Begin
		j := i;
		If Dist[Heap[2*i]] < Dist[Heap[j]] Then j := 2*i;
		If 2*i+1 <= HeapSize Then
			If Dist[Heap[2*i+1]] < Dist[Heap[j]] Then j := 2*i+1;
		If i = j Then Break;
		HeapSwap(i, j);
		i := j;
	End;
End;

Procedure HeapUpdate(x: LongInt);
Begin
	If Pos[x] = 0 Then Begin
		Inc(HeapSize);
		Heap[HeapSize] := x;
		Pos[x] := HeapSize;
	End;

	HeapUp(Pos[x]);
End;

Function HeapExtractMin: LongInt;
Begin
	HeapSwap(1, HeapSize);
	Dec(HeapSize);
	HeapDown(1);
	HeapExtractMin := Heap[HeapSize + 1];
End;

Function Dijkstra(s, t: LongInt): LongInt;
Var
	i, u, v: LongInt;
Begin
	HeapSize := 0;
	For i := 1 To N Do Begin
		Pos[i] := 0;
		Dist[i] := INF;
	End;

	Dist[s] := 0;
	HeapUpdate(s);

	While HeapSize <> 0 Do Begin
		u := HeapExtractMin;
		If u = t Then Break;

		i := Head[u];
		While i <> 0 Do Begin
			v := Adj[i].v;
			If Dist[u] + Adj[i].cost < Dist[v] Then Begin
				Dist[v] := Dist[u] + Adj[i].cost;
				HeapUpdate(v);
			End;
			i := Adj[i].next;
		End;
	End;

	Dijkstra := Dist[t];
End;

Var
	i, m, src, dst, u, v, c, cs, T: LongInt;
Begin
	ReadLn(T);
	For cs := 1 To T Do Begin
		ReadLn(N, m, src, dst);
		Inc(src); Inc(dst);

		For i := 1 To N Do
			Head[i] := 0;

		For i := 1 To m Do Begin
			ReadLn(u, v, c);
			Inc(u); Inc(v);

			Adj[2*i-1].v := v;
			Adj[2*i-1].cost := c;
			Adj[2*i-1].next := Head[u];
			Head[u] := 2*i-1;

			Adj[2*i].v := u;
			Adj[2*i].cost := c;
			Adj[2*i].next := Head[v];
			Head[v] := 2*i;
		End;

		c := Dijkstra(src, dst);
		If c = INF Then
			WriteLn('Case #', cs, ': unreachable')
		Else
			WriteLn('Case #', cs, ': ', c);
	End;
End.

