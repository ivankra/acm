(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Geometry 2D Base
	Category: Geometry - Geometry 2D Base
	Version: 1.0
	Date: 2006-10-31
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_Geometry2DBase(Input, Output);
const
	MaxN = 100;
	Precision = 1E-8;
type
	TIndex = Longint;
	TData = Extended;
	TPoint = record
		x, y: TData;
	end;
	TPointSet = array [1..MaxN] of TPoint;

function IsEqual(const A, B: TData): Boolean;
begin
	Result := (Abs(A - B) < Precision);
end;
function Compare(const A, B: TPoint): TData;
begin
	Result := A.x - B.x;
	if IsEqual(Result, 0) then Result := A.y - B.y;
end;
procedure QuickSort(var P: TPointSet; const l, r: TIndex);
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
	if l < j then QuickSort(P, l, j);
	if i < r then QuickSort(P, i, r);
end;
function Det(const A, B, C: TPoint): TData; overload;
begin
	Result := (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
end;
function Dot(const A, B, C: TPoint): TData; overload;
begin
	Result := (B.x - A.x) * (C.x - A.x) + (B.y - A.y) * (C.y - A.y);
end;
function Det(const A, B: TPoint): TData; overload;
begin
	Result := A.x * B.y - A.y * B.x;
end;
function Dot(const A, B: TPoint): TData; overload;
begin
	Result := A.x * B.x + A.y * B.y;
end;
function Point(const x, y: TData): TPoint;
begin
	Result.x := x;
	Result.y := y;
end;
function Vector(const A, B: TPoint): TPoint;
begin
	Result.x := B.x - A.x;
	Result.y := B.y - A.y;
end;
function IsEqualPoint(const A, B: TPoint): Boolean;
begin
	Result := IsEqual(A.x, B.x) and IsEqual(A.y, B.y);
end;
function Rotate(const Base, Angle: TPoint): TPoint; //Base is a vector, Angle is complex number as (cosA + i*sinA)
begin
	Result.x := Base.x * Angle.x - Base.y * Angle.y;
	Result.y := Base.x * Angle.y + Base.y * Angle.x;
end;
function GetLengthSqr(const A: TPoint): TData;
begin
	Result := Sqr(A.x) + Sqr(A.y);
end;
function GetLength(const A: TPoint): TData;
begin
	Result := Sqrt(Sqr(A.x) + Sqr(A.y));
end;
function GetDist(const A, B: TPoint): TData;
begin
	Result := Sqrt(Sqr(A.x - B.x) + Sqr(A.y - B.y));
end;
function Intersect(const A, B, C, D: TPoint; var E: TPoint): Boolean;
var
	SA, SB: TData;
begin
	Result := false;
	SA := Det(A, B, D);
	SB := Det(A, B, C);
	if (SA * SB >= 0) or (SA = SB) then Exit;
	E.x := (C.x * SA - D.x * SB) / (SA - SB);
	E.y := (C.y * SA - D.y * SB) / (SA - SB);
	Result := true;
end;
begin
end.
