(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Edmonds Blossom-Contraction Algorithm
	Category: Match - General Unweighted - Edmonds Blossom-Contraction Algorithm
	Version: 1.0
	Date: 2006-11-16
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
	InQueue, InPath, InBlossom: TExist;

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
function FindCommonAncestor(u, v: TIndex): TIndex;
begin
	FillChar(InPath, SizeOf(InPath), false);
	while true do
	begin
		u := Base[u];
		InPath[u] := true;
		if u = Start then Break;
		u := Father[Match[u]];
	end;
	while true do
	begin
		v := Base[v];
		if InPath[v] then Break;
		v := Father[Match[v]];
	end;
	Result := v;
end;
procedure ResetTrace(u: TIndex);
var
	v: TIndex;
begin
	while Base[u] <> NewBase do
	begin
		v := Match[u];
		InBlossom[Base[u]] := true;
		InBlossom[Base[v]] := true;
		u := Father[v];
		if Base[u] <> NewBase then Father[u] := v;
	end;
end;
procedure BlossomContract(u, v: TIndex);
begin
	NewBase := FindCommonAncestor(u, v);
	FillChar(InBlossom, SizeOf(InBlossom), false);
	ResetTrace(u);
	ResetTrace(v);
	if Base[u] <> NewBase then Father[u] := v;
	if Base[v] <> NewBase then Father[v] := u;
	for u := 1 to N do
		if InBlossom[Base[u]] then
		begin
			Base[u] := NewBase;
			if not InQueue[u] then Push(u);
		end;
end;
procedure FindAugmentingPath;
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
	Finish := 0;
	while Head < Tail do
	begin
		u := Pop;
		for v := 1 to N do
			if Graph[u, v] and (Base[u] <> Base[v]) and (Match[u] <> v) then
				if (v = Start) or ((Match[v] > 0) and (Father[Match[v]] > 0)) then 
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
			FindAugmentingPath;
			if Finish > 0 then AugmentPath;
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