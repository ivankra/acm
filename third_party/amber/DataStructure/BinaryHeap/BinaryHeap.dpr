(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Binary Heap
	Category: Data Structure
	Version: 1.0
	Remark: N/A
	Tested Problems: USACO NOV06 Plank
	Date: 2006-11-16
*)
program ASSL_BinaryHeap(Input, Output);
const
	MaxHeapSize = 1000;
type
	TIndex = Longint;
	TData = Longint;
	
	THeap = object
	private
		Size: TIndex;
		Data: array [1..MaxHeapSize] of TData;
		function Compare(const A, B: TData): TData;
		procedure Swap(var A, B: TData);
	public
		procedure Push(const Key: TData);
		function Pop: TData;
	end;

function THeap.Compare(const A, B: TData): TData;
begin
	Result := A - B;
end;
procedure THeap.Swap(var A, B: TData);
var
	T: TData;
begin
	T := A;
	A := B;
	B := T;
end;
procedure THeap.Push(const Key: TData);
var
	i: TIndex;
begin
	Inc(Size);
	Data[Size] := Key;
	i := Size;
	while i > 1 do
	begin
		if Compare(Data[i shr 1], Data[i]) <= 0 then Break;
		Swap(Data[i shr 1], Data[i]);
		i := i shr 1;
	end;
end;
function THeap.Pop: TData;
var
	i, j: TIndex;
begin
	Swap(Data[1], Data[Size]);
	Result := Data[Size];
	Dec(Size);
	i := 1;
	while i shl 1 <= Size do
	begin
		j := i shl 1;
		if (j < Size) and (Compare(Data[j + 1], Data[j]) < 0) then Inc(j);
		if Compare(Data[i], Data[j]) <= 0 then Break;
		Swap(Data[i], Data[j]);
		i := j;
	end;
end;
begin
end.
