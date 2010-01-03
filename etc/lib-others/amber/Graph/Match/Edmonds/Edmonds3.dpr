(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Edmonds Blossom-Contraction Algorithm
	Category: Match - General Unweighted - Edmonds Blossom-Contraction Algorithm
	Version: 3.0
	Date: 2007-1-9
	Remark:
		Maximum Cardinality Matching Problem in General Graph by Edmonds Blossom-Contraction Algorithm
		Adjacency List Implementation
	Complexity: O(NM), O(M) for each augmenting
	Tested Problems: Ural 1099
*)
program ASSL_Edmonds(Input, Output);
const
	MaxN = 300;
	MaxM = MaxN * MaxN;
type
	TIndex = Longint;
	TEdge = record
		Target: TIndex;
		Prev: TIndex;
	end;
	TLast = array [1..MaxN] of TIndex;
	TEdgeSet = array [1..MaxM] of TEdge;
	TExist = array [1..MaxN] of Boolean;
	TLink = array [1..MaxN] of TIndex;
	TQueue = array [1..MaxN] of TIndex;
var
	N, M: TIndex;
	Last: TLast;
	Edge: TEdgeSet;
	Match: TLink;
	InQueue, InPath, InTree: TExist;

	Head, Tail: TIndex;
	Queue: TQueue;
	PathLen, TreeSize: TIndex;
	Path, Tree: TQueue;

	Start, Finish: TIndex;
	NewBase: TIndex;
	Father, Base: TLink;
	Count: TIndex;

procedure CreateGraph;
var
	u, v: TIndex;
begin
	FillChar(Last, SizeOf(Last), 0);
	Readln(N);
	M := 0;
	while not SeekEof do
	begin
		Readln(u, v);
		Inc(M);
		Edge[M].Target := v;
		Edge[M].Prev := Last[u];
		Last[u] := M;
		Inc(M);
		Edge[M].Target := u;
		Edge[M].Prev := Last[v];
		Last[v] := M;
	end;
end;
procedure PushToTree(u: TIndex);
begin
	if InTree[u] then Exit;
	InTree[u] := true;
	Inc(TreeSize);
	Tree[TreeSize] := u;
end;
procedure ClearTree;
var
	u: TIndex;
begin
	while TreeSize > 0 do
	begin
		u := Tree[TreeSize];
		Dec(TreeSize);
		InTree[u] := false;
		InQueue[u] := false;
		Base[u] := u;
		Father[u] := 0;
	end;
end;
procedure Push(u: TIndex);
begin
	Queue[Tail] := u;
	Inc(Tail);
	InQueue[u] := true;
	PushToTree(u);
end;
function Pop: TIndex;
begin
	Result := Queue[Head];
	Inc(Head);
end;
function FindBase(u: TIndex): TIndex;
begin
	if Base[u] <> u then
		Base[u] := FindBase(Base[u]);
	Result := Base[u]
end;
function FindCommonAncestor(u, v: TIndex): TIndex;
begin
	while true do
	begin
		u := FindBase(u);
		Inc(PathLen);
		Path[PathLen] := u;
		InPath[u] := true;
		if u = Start then Break;
		u := Father[Match[u]];
	end;
	while true do
	begin
		v := FindBase(v);
		if InPath[v] then Break;
		v := Father[Match[v]];
	end;
	Result := v;
	while PathLen > 0 do
	begin
		u := Path[PathLen];
		Dec(PathLen);
		InPath[u] := false;
	end;
end;
procedure ResetTrace(u: TIndex);
var
	v: TIndex;
begin
	while FindBase(u) <> NewBase do
	begin
		v := Match[u];
		if not InQueue[v] then Push(v);
		if Base[u] = u then Base[u] := NewBase;
		if Base[v] = v then Base[v] := NewBase;
		u := Father[v];
		if FindBase(u) <> NewBase then Father[u] := v;
	end;
end;
procedure BlossomContract(u, v: TIndex);
begin
	NewBase := FindCommonAncestor(u, v);
	if FindBase(u) <> NewBase then Father[u] := v;
	if FindBase(v) <> NewBase then Father[v] := u;
	ResetTrace(u);
	ResetTrace(v);
end;
function FindAugmentingPath: Boolean;
var
	u, v: TIndex;
	Ptr: TIndex;
begin
	Head := 1;
	Tail := 1;
	Push(Start);
	Result := true;
	while Head < Tail do
	begin
		u := Pop;
		Ptr := Last[u];
		while Ptr > 0 do
			with Edge[Ptr] do
			begin
				v := Target;
				if (FindBase(u) <> FindBase(v)) and (Match[u] <> v) then
					if (Match[v] > 0) and (Father[Match[v]] > 0) then 
						BlossomContract(u, v)
					else if Father[v] = 0 then
					begin
						Father[v] := u;
						PushToTree(v);
						if Match[v] > 0 then
							Push(Match[v])
						else
						begin
							Finish := v;
							Exit;
						end;
					end;
				Ptr := Prev;
			end;
	end;
	Result := false;
end;
procedure AugmentPath;
var
	u, v, w: TIndex;
begin
	u := Finish;
	while u > 0 do
	begin
		v := Father[u];
		w := Match[v];
		Match[v] := u;
		Match[u] := v;
		u := w;
	end;
end;
procedure Edmonds;
var
	u: TIndex;
begin
	FillChar(Match, SizeOf(TLink), 0);
	FillChar(Father, SizeOf(TLink), 0);
	FillChar(InQueue, SizeOf(TExist), 0);
	FillChar(InPath, SizeOf(TExist), 0);
	FillChar(InTree, SizeOf(TExist), 0);
	PathLen := 0;
	TreeSize := 0;
	for u := 1 to N do
		Base[u] := u;
	for u := 1 to N do
		if Match[u] = 0 then
		begin
			Start := u;
			if FindAugmentingPath then AugmentPath;
			ClearTree;
		end;
end;
procedure PrintMatch;
var
	u: TIndex;
begin
	Count := 0;
	for u := 1 to N do
		if Match[u] > 0 then
			Inc(Count);
	Writeln(Count);
	for u := 1 to N do
		if u < Match[u] then
			Writeln(u, ' ', Match[u]);
end;
procedure Main;
begin
	CreateGraph;
	Edmonds;
	PrintMatch;
end;
begin
	Main;
end.