{$R+,Q+,D+}
program Dijsktra;
uses
	Base, GraphGen, BinaryHeap, FibonacciHeap, PairHeap, Windows;
type
	TDist = array[1..MaxN] of TKey;
	TCheck = array[1..MaxN] of Boolean;
var
	Dist: TDist;
	Check: TCheck;

function Dijkstra: TKey;
var
	i: TIndex;
	Cur, Ptr: TIndex;
	Node: PFibonacciNode;
	Heap: TFibonacciHeap;
begin
	Heap.Create(N);
	for i := 1 to N do
	begin
		Check[i] := false;
		Heap.Insert(i, InfiniteValue);
		Dist[i] := InfiniteValue;
	end;
	Heap.DecreaseKey(S, 0);
	Dist[S] := 0;
	while not Check[T] do
	begin
		Node := Heap.Minimum;
		if Node = nil then Break;
		Cur := Node^.Index;

		Check[Cur] := true;
		Heap.DeleteMin;

		Ptr := Last[Cur];
		while Ptr > 0 do
		begin
			with Edge[Ptr] do
				if not Check[Adj] and (Dist[Adj] > Dist[Cur] + Weight) then
				begin
					Dist[Adj] := Dist[Cur] + Weight;
					Heap.DecreaseKey(Adj, Dist[Adj]);
				end;
			Ptr := Edge[Ptr].Prev;
		end;
	end;
	Result := Dist[T];
	Heap.Destory;
end;

function Dijkstra2: TKey;
var
	i: TIndex;
	Cur, Ptr: TIndex;
	Node: PBinaryNode;
	Heap: TBinaryHeap;
begin
	Heap.Create(N);
	for i := 1 to N do
	begin
		Check[i] := false;
		Heap.Insert(i, InfiniteValue);
		Dist[i] := InfiniteValue;
	end;
	Heap.DecreaseKey(S, 0);
	Dist[S] := 0;
	while not Check[T] do
	begin
		Node := Heap.Minimum;
		if Node = nil then Break;
		Cur := Node^.Index;

		Check[Cur] := true;
		Heap.DeleteMin;

		Ptr := Last[Cur];
		while Ptr > 0 do
		begin
			with Edge[Ptr] do
				if not Check[Adj] and (Dist[Adj] > Dist[Cur] + Weight) then
				begin
					Dist[Adj] := Dist[Cur] + Weight;
					Heap.DecreaseKey(Adj, Dist[Adj]);
				end;
			Ptr := Edge[Ptr].Prev;
		end;
	end;
	Result := Dist[T];
	Heap.Destory;
end;

function Dijkstra3: TKey;
var
	i: TIndex;
	Cur, Ptr: TIndex;
	Node: PPairNode;
	Heap: TPairHeap;
begin
	Heap.Create(N);
	for i := 1 to N do
	begin
		Check[i] := false;
		Heap.Insert(i, InfiniteValue);
		Dist[i] := InfiniteValue;
	end;
	Heap.DecreaseKey(S, 0);
	Dist[S] := 0;
	while not Check[T] do
	begin
		Node := Heap.Minimum;
		if Node = nil then Break;
		Cur := Node^.Index;

		Check[Cur] := true;
		Heap.DeleteMin;

		Ptr := Last[Cur];
		while Ptr > 0 do
		begin
			with Edge[Ptr] do
				if not Check[Adj] and (Dist[Adj] > Dist[Cur] + Weight) then
				begin
					Dist[Adj] := Dist[Cur] + Weight;
					Heap.DecreaseKey(Adj, Dist[Adj]);
				end;
			Ptr := Edge[Ptr].Prev;
		end;
	end;
	Result := Dist[T];
	Heap.Destory;
end;

procedure Main;
var
	Start: Int64;
begin
	Randomize;
	GenerateRandomSparse;
	Start := GetTickCount;
	Writeln(Dijkstra);
	Writeln(GetTickCount - Start);
	Start := GetTickCount;
	Writeln(Dijkstra2);
	Writeln(GetTickCount - Start);
	Start := GetTickCount;
	Writeln(Dijkstra3);
	Writeln(GetTickCount - Start);
end;
begin
	Main;
end.

