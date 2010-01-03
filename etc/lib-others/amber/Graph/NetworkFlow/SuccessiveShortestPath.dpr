(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Successive shortest augmenting path algorithm
	Category: Network Flow - Minimum Cost Maximum Flow
	Version: 1.0
	Date: 2007-1-10
	Remark: Ford Fulkerson Method, Adjacency List Implementation
	Complexity: O(MF) = O(NM^2)
	Tested Problems: N/A
*)
program ASSL_SuccessiveShortestPath(Input, Output);
const
	Infinity = 1000000;
	MaxNodeNum = 5000;
	MaxEdgeNum = 50000;
	MaxQueueLen = MaxNodeNum * 2;
type
	TIndex = Longint;
	TCapacity = Longint;
	TCost = Longint;
	TEdge = record
		Start, Target: TIndex;
		Flow, Capa: TCapacity;
		Cost: TCost;
		Prev: TIndex;
	end;
	TNetwork = object
	public
		procedure Initialize(FSource, FSink, FNodeNum: TIndex);
		procedure InsertEdge(FStart, FTarget: TIndex; FCapa: TCapacity; FCost: TCost; FFlow: TCapacity = 0);
		procedure SuccessiveShortestPath;
		function GetFlowValue: TCapacity;
		function GetCostValue: TCost;

	private
		NodeNum, EdgeNum: TIndex;
		Source, Sink: TIndex;
		Edge: array [1..MaxEdgeNum] of TEdge;
		Last: array [1..MaxNodeNum] of TIndex;

		TotalFlow: TCapacity;
		TotalCost: TCost;
		Used: array [1..MaxNodeNum] of Boolean;
		Pred: array [1..MaxNodeNum] of TIndex;
		Delta: array [1..MaxNodeNum] of TCapacity;
		Queue: array [1..MaxQueueLen] of TIndex;
		Dist: array [1..MaxNodeNum] of TCost;
		Count: array [1..MaxNodeNum] of TIndex;

		function SPFA: Boolean;
		function Opposite(Ptr: TIndex): TIndex;
	end;

procedure TNetwork.InsertEdge(FStart, FTarget: TIndex; FCapa: TCapacity; FCost: TCost; FFlow: TCapacity = 0);
begin
	Inc(EdgeNum);
	with Edge[EdgeNum] do
	begin
		Start := FStart;
		Target := FTarget;
		Flow := FFlow;
		Capa := FCapa;
		Cost := FCost;
		Prev := Last[Start];
		Last[Start] := EdgeNum;
	end;
	Inc(EdgeNum);
	with Edge[EdgeNum] do
	begin
		Start := FTarget;
		Target := FStart;
		Flow := -FFlow;
		Capa := 0;
		Cost := -FCost;
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
function TNetwork.SPFA: Boolean;
var
	Pop, Push: TIndex;
	Start: TIndex;
	Ptr: TIndex;
begin
	Result := false;
	for Start := 1 to NodeNum do
	begin
		Dist[Start] := Infinity;
		Used[Start] := false;
		Count[Start] := 0;
	end;
	Pop := 1;
	Push := 2;
	Queue[1] := Source;
	Dist[Source] := 0;
	Used[Source] := true;
	Pred[Source] := 0;
	Count[Source] := 1;
	Delta[Source] := Infinity;
	while Pop <> Push do
	begin
		Start := Queue[Pop];
		Ptr := Last[Start];
		while Ptr > 0 do
		begin
			with Edge[Ptr] do
				if (Flow < Capa) and (Dist[Target] > Dist[Start] + Cost) then
				begin
					Dist[Target] := Dist[Start] + Cost;
					Pred[Target] := Ptr;
					Delta[Target] := Delta[Start];
					if Delta[Target] > Capa - Flow then
						Delta[Target] := Capa - Flow;
					if not Used[Target] then
					begin
						Inc(Count[Target]);
						if Count[Target] = NodeNum then Exit;
						Used[Target] := true;
						Queue[Push] := Target;
						Inc(Push);
						if Push > MaxQueueLen then Push := 1;
					end;
				end;
			Ptr := Edge[Ptr].Prev;
		end;
		Inc(Pop);
		if Pop > MaxQueueLen then Pop := 1;
		Used[Start] := false;
	end;
	Result := (Dist[Sink] < Infinity);
end;
procedure TNetwork.SuccessiveShortestPath;
var
	Ptr: TIndex;
	Cur: TIndex;
	CurDelta: TCapacity;
begin
	TotalFlow := 0;
	TotalCost := 0;
	while SPFA do
	begin
		Cur := Sink;
		CurDelta := Delta[Sink];
		Inc(TotalFlow, CurDelta);
		Inc(TotalCost, CurDelta * Dist[Sink]);
		repeat
			Ptr := Pred[Cur];
			with Edge[Ptr] do
			begin
				Inc(Flow, CurDelta);
				Dec(Edge[Opposite(Ptr)].Flow, CurDelta);
				Cur := Start;
			end;
		until Cur = Source;
	end;
end;
function TNetwork.GetFlowValue: TCapacity;
begin
	Result := TotalFlow;
end;
function TNetwork.GetCostValue: TCost;
begin
	Result := TotalCost;
end;
var
	N, M: TIndex;
	Network: TNetwork;

procedure Main;
var
	i: TIndex;
	x, y: TIndex;
	Value: TCapacity;
	Cost: TCost;
begin
	Readln(N, M);
	Network.Initialize(1, N, N);
	for i := 1 to M do
	begin
		Readln(x, y, Value, Cost);
		Network.InsertEdge(x, y, Value, Cost);
	end;
	Network.SuccessiveShortestPath;
	Writeln(Network.GetCostValue);
end;
begin
	Main;
end.
