(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Shrink Strongly Connected
	Category: Graph - Connected - Shrink Strongly Connected
	Version: 1.0
	Date: 2006-10-31
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_ShrinkStronglyConnected(Input, Output);
const
	MaxNodeNum = 100;
	MaxEdgeNum = 10000;
type
	TIndex = Longint;
	TEdge = record
		Start, Target, Prev: TIndex;
	end;
	TQueue = array [1..MaxNodeNum] of TIndex;
	TLast = array [1..MaxNodeNum] of TIndex;
	TEdgeSet = array [1..MaxEdgeNum] of TEdge;
	TNode = record
		Order, Low: TIndex;
		Used, Alive: Boolean;
	end;
	TNodeSet = array [1..MaxNodeNum] of TNode;
	TBelong = array [1..MaxNodeNum] of TIndex;
	TStack = array [1..MaxNodeNum] of TIndex;
var
	N, M: TIndex;
	NodeNum, EdgeNum: TIndex;
	Node: TNodeSet;
	Last: TLast;
	Edge: TEdgeSet;
	Belong: TBelong;
	Count: TIndex;
	Top: TIndex;
	Stack: TStack;
	
procedure Shrink(Start: TIndex);
var
	Ptr: TIndex;
begin
	Inc(Count);
	Node[Start].Order := Count;
	Node[Start].Low := Count;
	Node[Start].Used := true;
	Node[Start].Alive := true;
	Inc(Top);
	Stack[Top] := Start;

	Ptr := Last[Start];
	while Ptr > 0 do
		with Edge[Ptr] do
		begin
			if not Node[Target].Used then
			begin
				Shrink(Target);
				if Node[Start].Low > Node[Target].Low then
					Node[Start].Low := Node[Target].Low;
			end;
			if Node[Target].Alive and (Node[Start].Low > Node[Target].Order) then
				Node[Start].Low := Node[Target].Order;
			Ptr := Prev;
		end;
	
	if Node[Start].Order = Node[Start].Low then
	begin
		while Stack[Top] <> Start do
		begin
			Belong[Stack[Top]] := Start;
			Node[Stack[Top]].Alive := false;
			Dec(Top);
		end;
		Belong[Start] := Start;
		Dec(Top);
		Node[Start].Alive := false;
	end;
end;
procedure AddEdge(i, j: TIndex);
begin
	Inc(EdgeNum);
	Edge[EdgeNum].Start := i;
	Edge[EdgeNum].Target := j;
	Edge[EdgeNum].Prev := Last[i];
	Last[i] := EdgeNum;
end;
procedure Main;
var
	i, j: TIndex;
	OldEdgeNum: TIndex;
begin
	//Bulid graph
	FillChar(Last, SizeOf(Last), 0);
	Readln(N, M);
	NodeNum := N;
	EdgeNum := 0;
	while M > 0 do
	begin
		Dec(M);
		Readln(i, j);
		AddEdge(i, j);
	end;

	//Shrink
	FillChar(Node, SizeOf(Node), 0);
	Count := 0;
	Top := 0;
	for i := 1 to NodeNum do
		if not Node[i].Used then
			Shrink(i);

	//Rebulid graph
	FillChar(Last, SizeOf(Last), 0);
	OldEdgeNum := EdgeNum;
	EdgeNum := 0;
	for i := 1 to OldEdgeNum do
		with Edge[i] do
			if Belong[Start] <> Belong[Target] then
				AddEdge(Belong[Start], Belong[Target]);
end;
begin
	Main;
end.
