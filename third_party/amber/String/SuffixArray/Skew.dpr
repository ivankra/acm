(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Skew
	Category: String - Suffix Array
	Version: 1.0
	Date: 2006-12-25
	Remark: N/A
	Tested Problems: Ural 1517 Freedom of choice
*)
program ASSL_Skew(Input, Output);
type
	TIndex = Longint;
	TArray = array of TIndex;
	TSuffixArray = object
	public
		Size: TIndex;
		Text: TArray;
		SA: TArray;
		Rank: TArray;
		Height: TArray;
		procedure Initialize(const FSize: TIndex);
		procedure CalculateSA(const Range: TIndex);
		procedure CalculateRank;
		procedure CalculateHeight;
	private
		Mod3: TArray;
		function Increase(var X: TIndex): TIndex;
		procedure CreateArray(var List: TArray; const Len: TIndex);
		procedure RadixSort(var List: TArray; const Key: TArray; const Len, Range: TIndex);
		procedure Skew(var CurText, SAAll: TArray; const Len, Range: TIndex);
	end;

function TSuffixArray.Increase(var X: TIndex): TIndex;
begin
	Inc(X);
	Result := X;
end;
procedure TSuffixArray.CreateArray(var List: TArray; const Len: TIndex);
begin
	SetLength(List, Len + 1);
end;
procedure TSuffixArray.RadixSort(var List: TArray; const Key: TArray; const Len, Range: TIndex);
var
	i: TIndex;
	NewList: TArray;
	Count: TArray;
begin
	CreateArray(NewList, Len);
	CreateArray(Count, Range);
	for i := 0 to Range do
		Count[i] := 0;
	for i := 1 to Len do
		Inc(Count[Key[i]]);
	for i := 1 to Range do
		Inc(Count[i], Count[i - 1]);
	for i := Len downto 1 do
	begin
		NewList[Count[Key[i]]] := List[i];
		Dec(Count[Key[i]]);
	end;
	List := NewList;
end;
procedure TSuffixArray.Skew(var CurText, SAAll: TArray; const Len, Range: TIndex);
var
	i, j: TIndex;
	Num, Num1, Num23: TIndex;
	S23, SA1, SA23, Key1, Key23, Pos23, IndexSA23, Index, Map, Rank23: TArray;
	HasNull: Boolean;

	function ComparePair(const A1, A2: TIndex; const B1, B2: TIndex): TIndex;
	begin
		Result := A1 - B1;
		if Result = 0 then Result := A2 - B2;
	end;
	function CompareTriple(const A1, A2, A3: TIndex; const B1, B2, B3: TIndex): TIndex;
	begin
		Result := A1 - B1;
		if Result = 0 then Result := ComparePair(A2, A3, B2, B3);
	end;
	function Compare1And23(const i, j: TIndex): TIndex; //i mod 3 = 1
	begin
		if Mod3[j] = 2 then
			Result := ComparePair(CurText[i], Rank23[i + 1], CurText[j], Rank23[j + 1])
		else
			Result := CompareTriple(CurText[i], CurText[i + 1], Rank23[i + 2], CurText[j], CurText[j + 1], Rank23[j + 2])
	end;
	function Compare23(const i, j: TIndex): TIndex; //i, j mod 3 <> 1
	begin
		Result := CompareTriple(CurText[i], CurText[i + 1], CurText[i + 2], CurText[j], CurText[j + 1], CurText[j + 2]);
	end;

begin
	if Len = 1 then
	begin
		SAAll[1] := 1;
		Exit;
	end;

	//Fill Blank
	CurText[Len + 1] := 0;
	CurText[Len + 2] := 0;
	CurText[Len + 3] := 0;
	
	//Gap between Position 2 and Position 3 in S23
	HasNull := (Mod3[Len + 1] = 2);

	//Allocate memory
	Num23 := Len * 2 div 3;
	Num1 := Len - Num23;
	if HasNull then Inc(Num23);
	CreateArray(S23, Num23);
	CreateArray(Key23, Num23);
	CreateArray(Pos23, Num23 + 3);
	CreateArray(IndexSA23, Num23);
	CreateArray(Index, Len + Ord(HasNull));
	CreateArray(Map, Num23);
	CreateArray(SA23, Num23);
	CreateArray(Rank23, Len + 3);
	CreateArray(SA1, Num1);
	CreateArray(Key1, Num1);

	//Create S23 whose order is Position 2, the Gap and Position 3
	Num23 := 0;
	for i := 1 to Len do
		if Mod3[i] = 2 then
			S23[Increase(Num23)] := i;
	if HasNull then 
		S23[Increase(Num23)] := Len + 1;
	for i := 1 to Len do
		if Mod3[i] = 0 then
			S23[Increase(Num23)] := i;

	//Create Index and Map for S23
	for i := 1 to Num23 do
		Index[S23[i]] := i;
	for i := 1 to Num23 do
		Map[i] := S23[i];

	//Sort S23
	for i := 1 to Num23 do
		Key23[i] := CurText[S23[i] + 2];
	RadixSort(S23, Key23, Num23, Range);
	for i := 1 to Num23 do
		Key23[i] := CurText[S23[i] + 1];
	RadixSort(S23, Key23, Num23, Range);
	for i := 1 to Num23 do
		Key23[i] := CurText[S23[i]];
	RadixSort(S23, Key23, Num23, Range);
	
	//Get Pos23 namely the rank of S23
	Pos23[Index[S23[1]]] := 1;
	for i := 2 to Num23 do
		Pos23[Index[S23[i]]] := Pos23[Index[S23[i - 1]]] + Ord(Compare23(S23[i - 1], S23[i]) < 0);

	//Sort Pos23, then get the SA IndexSA23
	Skew(Pos23, IndexSA23, Num23, Num23);
	
	//Set SA23, Rank23
	Rank23[Len + 1] := 0;
	Rank23[Len + 2] := 0;
	Rank23[Len + 3] := 0;
	for i := 1 to Num23 do
	begin
		SA23[i] := Map[IndexSA23[i]];
		Rank23[SA23[i]] := i;
	end;

	//Create SA1
	Num1 := 0;
	for i := 1 to Len do
		if Mod3[i] = 1 then
			SA1[Increase(Num1)] := i;
	//Sort SA1
	for i := 1 to Num1 do
		Key1[i] := Rank23[SA1[i] + 1];
	RadixSort(SA1, Key1, Num1, Num23);
	for i := 1 to Num1 do
		Key1[i] := CurText[SA1[i]];
	RadixSort(SA1, Key1, Num1, Range);

	//Merge SA1 and SA23 to get SA
	Num := 0;
	i := 1;
	j := 1;
	if HasNull then Inc(j);
	while (i <= Num1) or (j <= Num23) do
		if (i <= Num1) and ((j > Num23) or (Compare1And23(SA1[i], SA23[j]) < 0)) then
			SAAll[Increase(Num)] := SA1[Increase(i) - 1]
		else
			SAAll[Increase(Num)] := SA23[Increase(j) - 1];
end;
procedure TSuffixArray.CalculateSA(const Range: TIndex);
begin
	Skew(Text, SA, Size, Range);
end;
procedure TSuffixArray.CalculateRank;
var
	i: TIndex;
begin
	for i := 1 to Size do
		Rank[SA[i]] := i;
end;
procedure TSuffixArray.CalculateHeight;
var
	i, j: TIndex;
	L: TIndex;
begin
	L := 0;
	for i := 1 to Size do
		if Rank[i] > 1 then
		begin
			j := SA[Rank[i] - 1];
			while (i + L <= Size) and (j + L <= Size) and (Text[i + L] = Text[j + L]) do Inc(L);
			Height[Rank[i]] := L;
			if L > 0 then Dec(L);
		end;
end;
procedure TSuffixArray.Initialize(const FSize: TIndex);
var
	i: TIndex;
begin
	Size := FSize;
	CreateArray(Text, Size + 3);
	CreateArray(Mod3, Size + 3);
	CreateArray(SA, Size);
	CreateArray(Rank, Size);
	CreateArray(Height, Size);
	for i := 1 to Size + 3 do
		Mod3[i] := i mod 3;
end;
var
	N: TIndex;
	SuffixArray: TSuffixArray;
procedure Main;
var
	i: TIndex;
	Ch: Char;
begin
	Readln(N);
	SuffixArray.Initialize(N);
	for i := 1 to N do
	begin
		Read(Ch);
		SuffixArray.Text[i] := Ord(Ch) - Ord('A') + 1;
	end;
	SuffixArray.CalculateSA(26);
	SuffixArray.CalculateRank;
	SuffixArray.CalculateHeight;
end;
begin
	Main;
end.