(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Aho Corasick
	Category: String - DFA
	Version: 1.0
	Date: 2007-1-21
	Remark: N/A
	Tested Problems: MIPT 014
*)
program ASSL_AhoCorasick(Input, Output);
const
	MaxN = 100000;
	MaxM = 100000;
	MaxNodeNum = 1000000 + 26 + 1;
type
	TIndex = Longint;
	TNode = record
		Child: array ['a'..'z'] of TIndex;
		Suffix: TIndex;
		Visited: Boolean;
	end;
	TText = array [1..MaxN] of Char;
	TQueue = array [1..MaxNodeNum] of TIndex;
	TDFA = object
		NodeNum: TIndex;
		Root: TIndex;
		Trie: array [1..MaxNodeNum] of TNode;
		Queue: TQueue;

		procedure Initialize;
		function Insert(Ptr: TIndex; Ch: Char): TIndex;
		function Next(Ptr: TIndex; Ch: Char): TIndex;
		procedure CreateSuffixLink;
		procedure Transfer;
	end;
	TAppear = array [1..MaxM] of TIndex;
var
	N, M: TIndex;
	Text: TText;
	DFA: TDFA;
	Appear: TAppear;

procedure TDFA.Initialize;
begin
	NodeNum := 1;
	Root := 1;
	FillChar(Trie, SizeOf(Trie), 0);
end;
function TDFA.Insert(Ptr: TIndex; Ch: Char): TIndex;
begin
	if Trie[Ptr].Child[Ch] = 0 then
	begin
		Inc(NodeNum);
		Trie[Ptr].Child[Ch] := NodeNum;
	end;
	Result := Trie[Ptr].Child[Ch];
end;
function TDFA.Next(Ptr: TIndex; Ch: Char): TIndex;
begin
	Result := Trie[Ptr].Child[Ch];
end;
procedure TDFA.CreateSuffixLink;
var
	Ch: Char;
	Cur: TIndex;
	Pop, Push: TIndex;
begin
	Pop := 1;
	Push := 1;
	for Ch := 'a' to 'z' do
	begin
		Cur := Insert(1, Ch);
		Trie[Cur].Suffix := 1;
		Queue[Push] := Cur;
		Inc(Push);
	end;
	while Pop < Push do
	begin
		Cur := Queue[Pop];
		Inc(Pop);
		for Ch := 'a' to 'z' do
			if Trie[Cur].Child[Ch] = 0 then
				Trie[Cur].Child[Ch] := Trie[Trie[Cur].Suffix].Child[Ch]
			else
			begin
				Trie[Trie[Cur].Child[Ch]].Suffix := Trie[Trie[Cur].Suffix].Child[Ch];
				Queue[Push] := Trie[Cur].Child[Ch];
				Inc(Push);
			end;
	end;
end;
procedure TDFA.Transfer;
var
	i: TIndex;
	Cur: TIndex;
begin
	for i := NodeNum - 1 downto 1 do
	begin
		Cur := Queue[i];
		if Trie[Cur].Visited then
			Trie[Trie[Cur].Suffix].Visited := true;
	end;
end;
procedure Main;
var
	i: TIndex;
	Ch: Char;
	Ptr: TIndex;
begin
	Readln(N);
	for i := 1 to N do
		Read(Text[i]);
	Readln;
	
	//Create Trie
	DFA.Initialize;
	Readln(M);
	for i := 1 to M do
	begin
		Ptr := DFA.Root;
		while not SeekEoln do
		begin
			Read(Ch);
			Ptr := DFA.Insert(Ptr, Ch);
		end;
		Appear[i] := Ptr;
		Readln;
	end;
	DFA.CreateSuffixLink;
	//Run DFA
	Ptr := 1;
	for i := 1 to N do
	begin
		Ptr := DFA.Next(Ptr, Text[i]);
		DFA.Trie[Ptr].Visited := true;
	end;
	DFA.Transfer;
	for i := 1 to M do
		if DFA.Trie[Appear[i]].Visited then
			Writeln('YES')
		else
			Writeln('NO');
end;
begin
	Main;
end.