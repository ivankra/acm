(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Doubling
	Category: String - Suffix Array
	Version: 1.0
	Date: 2006-12-25
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_Doubling(Input, Output);
const
	MaxN = 200000;
	Range = 26;
type
	TIndex = Longint;
	TText = array [1..MaxN] of TIndex;
	TRank = array [1..MaxN] of TIndex;
	TSuffixArray = array [1..MaxN] of TIndex;
	TCountData = array [0..Range] of TIndex;
	TCountRank = array [0..MaxN] of TIndex;
	THeight = array [1..MaxN] of TIndex;
var
	N: TIndex;
	Text: TText;
	SA: TSuffixArray;
	Rank: TRank;
	Height: THeight;

	//Temp for Calculating SA
	TmpSA: TSuffixArray;
	Rank1, Rank2: TRank;
	CountData: TCountData;
	CountRank: TCountRank;

procedure Doubling; //N > 1
var
	i: TIndex;
	L: TIndex;
begin
	//Count sort
	FillChar(CountData, SizeOf(CountData), 0);
	for i := 1 to N do
		Inc(CountData[Text[i]]);
	for i := Low(CountData) + 1 to High(CountData) do
		Inc(CountData[i], CountData[i - 1]);
	for i := 1 to N do
		Rank[i] := CountData[Text[i]];

	//Doubling algorithm
	L := 1;
	while L < N do
	begin
		//Key Init
		for i := 1 to N do
		begin
			Rank1[i] := Rank[i];
			if i + L <= N then
				Rank2[i] := Rank[i + L]
			else
				Rank2[i] := 0;
		end;

		//Radix Sort
		FillChar(CountRank, SizeOf(CountRank), 0);
		for i := 1 to N do
			Inc(CountRank[Rank2[i]]);
		for i := 1 to N do
			Inc(CountRank[i], CountRank[i - 1]);
		for i := N downto 1 do
		begin
			TmpSA[CountRank[Rank2[i]]] := i;
			Dec(CountRank[Rank2[i]]);
		end;

		FillChar(CountRank, SizeOf(CountRank), 0);
		for i := 1 to N do
			Inc(CountRank[Rank1[i]]);
		for i := 1 to N do
			Inc(CountRank[i], CountRank[i - 1]);
		for i := N downto 1 do
		begin
			SA[CountRank[Rank1[TmpSA[i]]]] := TmpSA[i];
			Dec(CountRank[Rank1[TmpSA[i]]]);
		end;
		
		//Calculate Rank
		Rank[SA[1]] := 1;
		for i := 2 to N do
		begin
			Rank[SA[i]] := Rank[SA[i - 1]];
			if not ((Rank1[SA[i]] = Rank1[SA[i - 1]]) and (Rank2[SA[i]] = Rank2[SA[i - 1]])) then
				Inc(Rank[SA[i]]);
		end;

		L := L * 2;
	end;
end;
procedure CalculateHeight;
var
	i, j: TIndex;
	L: TIndex;
begin
	//Calculate heights
	L := 0;
	for i := 1 to N do
		if Rank[i] > 1 then
		begin
			j := SA[Rank[i] - 1];
			while (i + L <= N) and (j + L <= N) and (Text[i + L] = Text[j + L]) do Inc(L);
			Height[Rank[i]] := L;
			if L > 0 then Dec(L);
		end;
end;
procedure Main;
var
	i: TIndex;
	Ch: Char;
begin
	Readln(N);
	for i := 1 to N do
	begin
		Read(Ch);
		Text[i] := Ord(Ch) - Ord('A') + 1;
	end;
	Doubling;
	CalculateHeight;
end;
procedure Print;
var
	i: TIndex;
begin
	Height[1] := 0;
	for i := 1 to N do
		Writeln(SA[i], ' ', Height[i], ' ', Rank[i]);
end;
begin
	Main;
	Print;
end.