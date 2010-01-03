(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Edmonds Blossom-Contraction Algorithm
	Category: Match - General Unweighted - Edmonds Blossom-Contraction Algorithm
	Version: 2.0
	Date: 2006-1-9
	Remark:
		Maximum Cardinality Matching Problem in General Graph by Edmonds Blossom-Contraction Algorithm
		Adjointing Matrix Implementation
	Complexity: O(NM)
	Tested Problems: Ural 1099
*)
program ASSL_Edmonds(Input, Output);
const
	MaxN = 300;
type
	TIndex = Longint;
	TGraph = array [1..MaxN, 1..MaxN] of Boolean;
	TExist = array [1..MaxN] of Boolean;
	TLink = array [1..MaxN] of TIndex;
	TQueue = array [1..MaxN] of TIndex;
var
	N: TIndex;
	Graph: TGraph;
	Match: TLink;
	InQueue, InPath: TExist;

	Head, Tail: TIndex;
	Queue: TQueue;

	Start, Finish: TIndex;
	NewBase: TIndex;
	Father, Base: TLink;
	Count: TIndex;

procedure CreateGraph;
var
	u, v: TIndex;
begin
	FillChar(Graph, SizeOf(Graph), false);
	Readln(N);
	while not SeekEof do
	begin
		Readln(u, v);
		Graph[u, v] := true;
		Graph[v, u] := true;
	end;
end;
procedure Push(u: TIndex);
begin
	Queue[Tail] := u;
	Inc(Tail);
	InQueue[u] := true;
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
	FillChar(InPath, SizeOf(InPath), false);
	while true do
	begin
		u := FindBase(u);
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
begin
	FillChar(InQueue, SizeOf(InQueue), false);
	FillChar(Father, SizeOf(Father), 0);
	for u := 1 to N do
		Base[u] := u;
	Head := 1;
	Tail := 1;
	Push(Start);
	Result := true;
	while Head < Tail do
	begin
		u := Pop;
		for v := 1 to N do
			if Graph[u, v] and (FindBase(u) <> FindBase(v)) and (Match[u] <> v) then
				if (Match[v] > 0) and (Father[Match[v]] > 0) then 
					BlossomContract(u, v)
				else if Father[v] = 0 then
				begin
					Father[v] := u;
					if Match[v] > 0 then
						Push(Match[v])
					else
					begin
						Finish := v;
						Exit;
					end;
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
	FillChar(Match, SizeOf(Match), 0);
	for u := 1 to N do
		if Match[u] = 0 then
		begin
			Start := u;
			if FindAugmentingPath then AugmentPath;
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