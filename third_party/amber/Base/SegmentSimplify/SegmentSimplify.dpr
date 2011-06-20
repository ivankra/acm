(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Segment Simplify
	Category: Base algorithm
	Version: 1.0
	Date: 2006-10-25
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_SegmentSimplify(Input, Output);
const
	MaxN = 100;
type
	TIndex = Longint;
	TSegment = record
		Left, Right: TIndex;
	end;
	TSegmentSet = array [1..MaxN] of TSegment;
var
	N: TIndex;
	Num: TIndex;
	S: TSegmentSet;

function Compare(const A, B: TSegment): TIndex;
begin
	Result := A.Left - B.Left;
	if Result = 0 then Result := B.Right - A.Right;
end;
procedure QuickSort(const l, r: TIndex);
var
	i, j: TIndex;
	Mid, Tmp: TSegment;
begin
	i := l;
	j := r;
	Mid := S[(i + j) div 2];
	repeat
		while Compare(S[i], Mid) < 0 do Inc(i);
		while Compare(Mid, S[j]) < 0 do Dec(j);
		if i <= j then
		begin
			Tmp := S[i];
			S[i] := S[j];
			S[j] := Tmp;
			Inc(i);
			Dec(j);
		end;
	until i > j;
	if l < j then QuickSort(l, j);
	if i < r then QuickSort(i, r);
end;
procedure SimplifyContaining; //Remove the segments which contains others.
var
	i: TIndex;
begin
	QuickSort(1, N);
	Num := 0;
	for i := 1 to N do
	begin
		while (Num > 0) and (S[Num].Left <= S[i].Left) and (S[i].Right <= S[Num].Right) do
			Dec(Num);
		Inc(Num);
		S[Num] := S[i];
	end;
end;
procedure SimplifyContained; //Remove the segments which is contained by others.
var
	i: TIndex;
begin
	QuickSort(1, N);
	Num := 0;
	for i := 1 to N do
	begin
		if (Num > 0) and (S[Num].Left <= S[i].Left) and (S[i].Right <= S[Num].Right) then Continue;
		Inc(Num);
		S[Num] := S[i];
	end;
end;
procedure Init;
var
	i: TIndex;
begin
	Readln(N);
	for i := 1 to N do
		Readln(S[i].Left, S[i].Right); //Satisfy S[i].Left <= S[i].Right
end;
procedure Print;
var
	i: TIndex;
begin
	Writeln(Num);
	for i := 1 to Num do
		Writeln(S[i].Left, ' ', S[i].Right);
end;
procedure Test;
begin
	Init;
	SimplifyContained;
	Print;
end;
begin
	Test;
end.
