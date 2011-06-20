(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Prime Filter
	Category: Math - Numberic - Prime - Prime Filter
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_PrimeFilter(Input, Output);
const
	MaxRange = 10000;
	MaxPrimeNum = 2000;
type
	TIndex = Longint;
	TFilter = array [1..MaxRange] of Boolean;
	TPrime = array [1..MaxPrimeNum] of TIndex;
var
	Range: TIndex;
	Filter: TFilter;
	PrimeNum: TIndex;
	Prime: TPrime;

procedure PrimeFilter;
var
	i, j: TIndex;
begin
	FillChar(Filter, SizeOf(Filter), true);
	Filter[1] := false;
	PrimeNum := 0;
	for i := 2 to Range do
		if Filter[i] then
		begin
			Inc(PrimeNum);
			Prime[PrimeNum] := i;
			for j := i to Range div i do
				Filter[i * j] := false;
		end;
end;
procedure Main;
var
	i: TIndex;
begin
	Range := MaxRange;
	PrimeFilter;
	for i := 1 to PrimeNum do
		Write(Prime[i], ' ');
end;
begin
	Main;
end.

