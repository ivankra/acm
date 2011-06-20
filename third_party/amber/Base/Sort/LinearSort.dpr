(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Linear Sort
	Category: Base algorithm - Sort
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_LinearSort(Input, Output);
const
	MaxSize = 1000;
type
	TIndex = Longint;
	TData = Longint;
	TElement = TData;
	TArray = array [1..MaxSize] of TElement;
var
	D: TArray;

procedure CountSort;
procedure RadixSort;
procedure BucketSort;
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
	InsertSort(l, r);
	Print(l, r);
	SelectSort(l, r);
	Print(l, r);
	BubbleSort(l, r);
	Print(l, r);
	QuickSort(l, r);
	Print(l, r);
	MergeSort(l, r);
	Print(l, r);
	HeapSort(r);
	Print(l, r);
end;
begin
	Test;
end.

