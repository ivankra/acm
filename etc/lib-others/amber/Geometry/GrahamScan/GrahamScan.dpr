(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Convex Hull by Graham Scan
	Category: Geometry - Convex Hull by Graham Scan
	Version: 1.0
	Date: 2006-10-24
	Remark: Sort by Level Order
	Tested Problems: N/A
*)
program ASSL_GrahamScan(Input, Output);
const
	MaxN = 10000;
type
	TIndex = Longint;
	TData = Longint;
	TPoint = record
		x, y: TData;
	end;
	TPointSet = array [1..MaxN] of TPoint;
	TStack = array [1..MaxN + 1] of TIndex;
var
	N: TIndex;
	P: TPointSet;

	Top: TIndex;
	Limit: TIndex;
	S: TStack;

function Compare(const A, B: TPoint): TData;
begin
	Result := A.x - B.x;
	if Result = 0 then Result := A.y - B.y;
end;
procedure QuickSort(const l, r: TIndex);
var
	i, j: TIndex;
	Mid, Tmp: TPoint;
begin
	i := l;
	j := r;
	Mid := P[(i + j) shr 1];
	repeat
		while Compare(P[i], Mid) < 0 do Inc(i);
		while Compare(Mid, P[j]) < 0 do Dec(j);
		if i <= j then
		begin
			Tmp := P[i];
			P[i] := P[j];
			P[j] := Tmp;
			Inc(i);
			Dec(j);
		end;
	until i > j;
	if l < j then QuickSort(l, j);
	if i < r then QuickSort(i, r);
end;
function Det(const A, B, C: TPoint): TData;
begin
	Result := (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
end;
procedure Update(i: TIndex);
begin
	while (Top > Limit) and (Det(P[S[Top - 1]], P[S[Top]], P[i]) <= 0) do //Here "=" is very important
		Dec(Top);
	Inc(Top);
	S[Top] := i;
end;
procedure GrahamScan;
var
	i: TIndex;
begin
	Top := 0;
	Limit := 1;
	for i := 1 to N do
		Update(i);
	Limit := Top;
	for i := N - 1 downto 1 do
		Update(i);
	Dec(Top); //Now S[Top] = S[1] = 1, So dec
end;
procedure Main;
var
	i: TIndex;
begin
	Readln(N);
	for i := 1 to N do
		Readln(P[i].x, P[i].y);
	QuickSort(1, N);
	GrahamScan;
	for i := 1 to Top do
		Writeln(P[S[i]].x, ' ', P[S[i]].y);
end;
begin
	Main;
end.
