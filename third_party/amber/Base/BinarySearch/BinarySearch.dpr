(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Binary Search
	Category: Base algorithm
	Version: 1.0
	Remark: N/A
	Tested Problems: N/A
	Date: 2006-10-24
*)
program ASSL_BinarySearch(Input, Output);
const
	MaxSize = 1000;
type
	TIndex = Longint;
	TData = Longint;
	TElement = TData;
	TArray = array [1..MaxSize] of TElement;
var
	D: TArray;

function Compare(const A, B: TElement): TData;
begin
	Result := A - B;
end;
function BinarySearch(Left, Right: TIndex; const Key: TElement): TIndex;
var
	Mid: TIndex;
begin
	while Left <= Right do
	begin
		Mid := (Left + Right) div 2;
		if Compare(Key, D[Mid]) < 0 then
			Right := Mid - 1
		else if Compare(Key, D[Mid]) > 0 then
			Left := Mid + 1
		else
		begin
			Result := Mid;
			Exit;
		end;
	end;
	Result := 0;
end;
function LowerBound(Left, Right: TIndex; const Key: TElement): TIndex;
var
	Mid: TIndex;
begin
	while Left < Right do
	begin
		Mid := (Left + Right) div 2;
		if Compare(D[Mid], Key) <= 0 then
			Right := Mid
		else
			Left := Mid + 1;
	end;
	Result := Left;
end;
function UpperBound(Left, Right: TIndex; const Key: TElement): TIndex;
var
	Mid: TIndex;
begin
	while Left < Right do
	begin
		Mid := (Left + Right + 1) div 2;
		if Compare(D[Mid], Key) <= 0 then
			Left := Mid
		else
			Right := Mid - 1;
	end;
	Result := Left;
end;
procedure Test;
var
	i: TIndex;
	l, r: TIndex;
	N: TIndex;
begin
	Randomize;
	N := 10;
	for i := 1 to N do
		D[i] := Random(343);
	l := 1;
	r := 9;
	Writeln(BinarySearch(l, r, Random(343)));
	Writeln(LowerBound(l, r, Random(343)));
	Writeln(UpperBound(l, r, Random(343)));
end;
begin
	Test;
end.

