(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Geometry 3D Base
	Category: Geometry - Geometry 3D Base
	Version: 1.0
	Date: 2006-10-31
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_Geometry3DBase(Input, Output);
const
	MaxN = 100;
	Precision = 1E-8;
type
	TIndex = Longint;
	TData = Extended;
	TPoint = record
		x, y, z: TData;
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
	if IsEqual(Result, 0) then Result := A.z - B.z;
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
function Point(const x, y, z: TData): TPoint;
begin
	Result.x := x;
	Result.y := y;
	Result.z := z;
end;
function Vector(const A, B: TPoint): TPoint;
begin
	Result.x := B.x - A.x;
	Result.y := B.y - A.y;
	Result.z := B.z - A.z;
end;
function Det(const A, B: TPoint): TPoint; overload;
begin
	Result.x := A.y * B.z - A.z * B.y;
	Result.y := A.z * B.x - A.x * B.z;
	Result.z := A.x * B.y - A.y * B.x;
end;
function Dot(const A, B: TPoint): TData; overload;
begin
	Result := A.x * B.x + A.y * B.y + A.z * B.z;
end;
function Det(const A, B, C: TPoint): TPoint; overload;
begin
	Result := Det(Vector(A, B), Vector(A, C));
end;
function Dot(const A, B, C: TPoint): TData; overload;
begin
	Result := Dot(Vector(A, B), Vector(A, C));
end;
function IsEqualPoint(const A, B: TPoint): Boolean;
begin
	Result := IsEqual(A.x, B.x) and IsEqual(A.y, B.y) and IsEqual(A.z, B.z);
end;
function GetLengthSqr(const A: TPoint): TData;
begin
	Result := Sqr(A.x) + Sqr(A.y) + Sqr(A.z);
end;
function GetLength(const A: TPoint): TData;
begin
	Result := Sqrt(Sqr(A.x) + Sqr(A.y) + Sqr(A.z));
end;
function GetDist(const A, B: TPoint): TData;
begin
	Result := Sqrt(Sqr(A.x - B.x) + Sqr(A.y - B.y) + Sqr(A.z - B.z));
end;
begin
end.
