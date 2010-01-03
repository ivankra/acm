(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Comparing Sort
	Category: Base algorithm - Sort
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_ComparingSort(Input, Output);
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
procedure InsertSort(l, r: TIndex);
var
	i, j: TIndex;
	Tmp: TElement;
begin
	for i := l + 1 to r do
	begin
		Tmp := D[i];
		j := i - 1;
		while (j >= l) and (Compare(D[j], Tmp) > 0) do
		begin
			D[j + 1] := D[j];
			Dec(j);
		end;
		D[j + 1] := Tmp;
	end;
end;
procedure SelectSort(l, r: TIndex);
var
	i, j, k: TIndex;
	Tmp: TElement;
begin
	for i := l to r do
	begin
		k := i;
		for j := i + 1 to r do
			if Compare(D[j], D[k]) < 0 then
				k := j;
		Tmp := D[i];
		D[i] := D[k];
		D[k] := Tmp;
	end;
end;
procedure BubbleSort(l, r: TIndex);
var
	i, j: TIndex;
	Tmp: TElement;
begin
	for i := l + 1 to r do
		for j := r downto i do
			if Compare(D[j - 1], D[j]) > 0 then
			begin
				Tmp := D[j - 1];
				D[j - 1] := D[j];
				D[j] := Tmp;
			end;
end;
procedure QuickSort(l, r: TIndex);
var
	i, j: TIndex;
	Mid, Tmp: TElement;
begin
	i := l;
	j := r;
	Mid := D[(i + j) div 2];
	repeat
		while Compare(D[i], Mid) < 0 do Inc(i);
		while Compare(Mid, D[j]) < 0 do Dec(j);
		if i <= j then
		begin
			Tmp := D[i];
			D[i] := D[j];
			D[j] := Tmp;
			Inc(i);
			Dec(j);
		end;
	until i > j;
	if l < j then QuickSort(l, j);
	if i < r then QuickSort(i, r);
end;
var
	Tmp: TArray;
procedure MergeSort(l, r: TIndex);
var
	m: TIndex;
	i, j, k: TIndex;
begin
	if l = r then Exit;
	m := (l + r) div 2;
	MergeSort(l, m);
	MergeSort(m + 1, r);
	i := l;
	j := m + 1;
	k := 0;
	while (i <= m) and (j <= r) do
		if Compare(D[i], D[j]) < 0 then
		begin
			Inc(k);
			Tmp[k] := D[i];
			Inc(i);
		end
		else
		begin
			Inc(k);
			Tmp[k] := D[j];
			Inc(j);
		end;
	while i <= m do
	begin
		Inc(k);
		Tmp[k] := D[i];
		Inc(i);
	end;
	while j <= r do
	begin
		Inc(k);
		Tmp[k] := D[j];
		Inc(j);
	end;
	while k > 0 do
	begin
		D[l + k - 1] := Tmp[k];
		Dec(k);
	end;
end;
procedure Sink(Cur, Size: TIndex);
var
	Child: TIndex;
	Tmp: TElement;
begin
	Tmp := D[Cur];
	while Cur * 2 <= Size do
	begin
		Child := Cur * 2;
		if (Child + 1 <= Size) and (Compare(D[Child + 1], D[Child]) > 0) then Inc(Child);
		if Compare(Tmp, D[Child]) >= 0 then Break;
		D[Cur] := D[Child];
		Cur := Child;
	end;
	D[Cur] := Tmp;
end;
procedure HeapSort(N: TIndex);
var
	i: TIndex;
	Tmp: TElement;
begin
	for i := N div 2 downto 1 do
		Sink(i, N);
	for i := N downto 1 do
	begin
		Tmp := D[1];
		D[1] := D[i];
		D[i] := Tmp;
		Sink(1, i - 1);
	end;
end;
procedure Print(l, r: TIndex);
var
	i: TIndex;
begin
	for i := l to r do
		Write(D[i], ' ');
	Writeln;
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

