(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Edmonds Karp
	Category: Network Flow - Maximum Flow - Edmonds Karp
	Version: 1.0
	Date: 2006-11-16
	Remark: Ford Fulkerson Method, Adjacency List Implementation
	Complexity: O(MF) = O(NM^2)
	Tested Problems: NOI 2006 Profit
*)
program ASSL_EdmondsKarp(Input, Output);
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
		procedure EdmondsKarp;
		function GetFlowValue: TCapacity;

	private
		NodeNum, EdgeNum: TIndex;
		Source, Sink: TIndex;
		Edge: array [1..MaxEdgeNum] of TEdge;
		Last: array [1..MaxNodeNum] of TIndex;

		TotalFlow: TCapacity;
		Used: array [1..MaxNodeNum] of Boolean;
		Pred: array [1..MaxNodeNum] of TIndex;
		Delta: array [1..MaxNodeNum] of TCapacity;
		Queue: array [1..MaxNodeNum] of TIndex;

		function Opposite(Ptr: TIndex): TIndex;
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
procedure TNetwork.EdmondsKarp;
var
	Pop, Push: TIndex;
	Ptr: TIndex;
	Cur: TIndex;
	CurDelta: TCapacity;
begin
	TotalFlow := 0;
	while true do
	begin
		FillChar(Used, SizeOf(Used), 0);
		FillChar(Pred, SizeOf(Pred), 0);
		FillChar(Delta, SizeOf(Delta), 0);
		Pop := 1;
		Push := 2;
		Queue[1] := Source;
		Used[Source] := true;
		Pred[Source] := 0;
		Delta[Source] := Infinity;
		while Pop < Push do
		begin
			Cur := Queue[Pop];
			Inc(Pop);
			Ptr := Last[Cur];
			while Ptr > 0 do
				with Edge[Ptr] do
				begin
					if Flow < Capa then
						if not Used[Target] then
						begin
							Queue[Push] := Target;
							Inc(Push);
							Used[Target] := true;
							Pred[Target] := Ptr;
							Delta[Target] := Delta[Start];
							if Delta[Target] > Capa - Flow then
								Delta[Target] := Capa - Flow;
							if Used[Sink] then Break;
						end;
					Ptr := Prev;
				end;
			if Used[Sink] then Break;
		end;
		if not Used[Sink] then Break;

		Cur := Sink;
		CurDelta := Delta[Sink];
		TotalFlow := TotalFlow + CurDelta;
		repeat
			Ptr := Pred[Cur];
			with Edge[Ptr] do
			begin
				Flow := Flow + CurDelta;
				Edge[Opposite(Ptr)].Flow := Edge[Opposite(Ptr)].Flow - CurDelta;
				Cur := Start;
			end;
		until Cur = Source;
	end;
end;
function TNetwork.GetFlowValue: TCapacity;
begin
	Result := TotalFlow;
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
	Network.EdmondsKarp;
	Writeln(Network.GetFlowValue);
end;
begin
	Main;
end.
