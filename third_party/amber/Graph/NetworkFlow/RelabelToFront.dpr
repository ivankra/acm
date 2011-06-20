(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Relabel To Front
	Category: Network Flow - Maximum Flow - Relabel To Front
	Version: 1.0
	Date: 2006-11-16
	Remark: Preflow Push Method, Adjacency List Implementation
	Complexity: O(N^2Sqrt(M))
	Tested Problems: NOI 2006 Profit
*)
program ASSL_RelabelToFront(Input, Output);
const
	Infinity = 1000000;
	MaxNodeNum = 5000;
	MaxEdgeNum = 50000;
type
	TIndex = Longint;
	TCapacity = Longint;
	TEdge = record
		Start, Target: TIndex;
		Flow, Capa: TCapacity;
		Prev: TIndex;
	end;
	TNetwork = object
	public
		procedure Initialize(FSource, FSink, FNodeNum: TIndex);
		procedure InsertEdge(FStart, FTarget: TIndex; FCapa: TCapacity);
		procedure PreflowPush;
		function GetFlowValue: TCapacity;

	private
		NodeNum, EdgeNum: TIndex;
		Source, Sink: TIndex;
		Edge: array [1..MaxEdgeNum] of TEdge;
		
		Height: array [1..MaxNodeNum] of TIndex;
		Last, Current: array [1..MaxNodeNum] of TIndex;
		Excess: array [1..MaxNodeNum] of TCapacity;

		Head: TIndex;
		Queue: array [0..MaxNodeNum] of record
			Prev, Next: TIndex;
		end;

		function Opposite(Ptr: TIndex): TIndex;
		procedure InitPreflow;
		procedure Push(Ptr: TIndex);
		procedure Relabel(u: TIndex);
		procedure Discharge(u: TIndex);
		procedure RelabelToFront;
	end;

procedure TNetwork.InsertEdge(FStart, FTarget: TIndex; FCapa: TCapacity);
begin
	Inc(EdgeNum);
	with Edge[EdgeNum] do
	begin
		Start := FStart;
		Target := FTarget;
		Flow := 0;
		Capa := FCapa;
		Prev := Last[Start];
		Last[Start] := EdgeNum;
	end;
	Inc(EdgeNum);
	with Edge[EdgeNum] do
	begin
		Start := FTarget;
		Target := FStart;
		Flow := 0;
		Capa := 0;
		Prev := Last[Start];
		Last[Start] := EdgeNum;
	end;
end;
procedure TNetwork.Initialize(FSource, FSink, FNodeNum: TIndex);
begin
	Source := FSource;
	Sink := FSink;
	NodeNum := FNodeNum;
	EdgeNum := 0;
	FillChar(Last, SizeOf(Last), 0);
end;
function TNetwork.Opposite(Ptr: TIndex): TIndex;
begin
	if Odd(Ptr) then
		Result := Ptr + 1
	else
		Result := Ptr - 1;
end;
procedure TNetwork.InitPreflow;
var
	Ptr: TIndex;
begin
	FillChar(Height, SizeOf(Height), 0);
	FillChar(Excess, SizeOf(Excess), 0);
	Height[Source] := NodeNum;
	Ptr := Last[Source];
	while Ptr > 0 do
		with Edge[Ptr] do
		begin
			Flow := Capa;
			Edge[Opposite(Ptr)].Flow := -Capa;
			Dec(Excess[Start], Capa);
			Inc(Excess[Target], Capa);
			Ptr := Prev;
		end;
end;
procedure TNetwork.Push(Ptr: TIndex);
var
	Delta: TCapacity;
begin
	with Edge[Ptr] do
	begin
		if Excess[Start] < Capa - Flow then
			Delta := Excess[Start]
		else
			Delta := Capa - Flow;
		Inc(Flow, Delta);
		Dec(Edge[Opposite(Ptr)].Flow, Delta);
		Dec(Excess[Start], Delta);
		Inc(Excess[Target], Delta);
	end;
end;
procedure TNetwork.Relabel(u: TIndex); //There exists one edge relating u AT LEAST.
var
	Ptr: TIndex;
	Min: TIndex;
begin
	Min := -1;
	Ptr := Last[u];
	while Ptr > 0 do
		with Edge[Ptr] do
		begin
			if Flow < Capa then
				if (Min = -1) or (Min > Height[Target]) then
					Min := Height[Target];
			Ptr := Prev;
		end;
	Height[u] := Min + 1;
end;
procedure TNetwork.Discharge(u: TIndex);
var
	Ptr: TIndex;
begin
	while Excess[u] > 0 do
	begin
		Ptr := Current[u];
		if Ptr = 0 then //v is null.
		begin
			Relabel(u);
			Current[u] := Last[u];
			Continue;
		end;
		with Edge[Ptr] do
			if (Flow < Capa) and (Height[Start] = Height[Target] + 1) then
				Push(Ptr)
			else
				Current[u] := Prev;
	end;
end;
procedure TNetwork.RelabelToFront;
var
	Cur: TIndex;
	OldHeight: TIndex;
begin
	Head := 0;
	for Cur := 1 to NodeNum do
		if (Cur <> Source) and (Cur <> Sink) then
		begin
			Current[Cur] := Last[Cur];
			Queue[Cur].Prev := 0;
			Queue[Cur].Next := Head;
			Queue[Head].Prev := Cur;
			Head := Cur;
		end;
	Cur := Head;
	while Cur > 0 do
	begin
		OldHeight := Height[Cur];
		Discharge(Cur);
		if (Cur <> Head) and (Height[Cur] > OldHeight) then
		begin
			Queue[Queue[Cur].Prev].Next := Queue[Cur].Next;
			Queue[Queue[Cur].Next].Prev := Queue[Cur].Prev;
			Queue[Cur].Prev := 0;
			Queue[Cur].Next := Head;
			Queue[Head].Prev := Cur;
			Head := Cur;
		end;
		Cur := Queue[Cur].Next;
	end;
end;
procedure TNetwork.PreflowPush;
begin
	InitPreflow;
	RelabelToFront;
end;
function TNetwork.GetFlowValue: TCapacity;
begin
	Result := Excess[Sink];
end;
var
	N, M: TIndex;
	Network: TNetwork;

procedure Main;
var
	i: TIndex;
	x, y: TIndex;
	Value: TCapacity;
begin
	Readln(N, M);
	Network.Initialize(1, N, N);
	for i := 1 to M do
	begin
		Readln(x, y, Value);
		Network.InsertEdge(x, y, Value);
	end;
	Network.PreflowPush;
	Writeln(Network.GetFlowValue);
end;
begin
	Main;
end.
