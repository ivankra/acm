(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: KMP
	Category: String Match
	Version: 1.0
	Remark: N/A
	Tested Problems: N/A
	Date: 2006-10-27
*)
program ASSL_KMP(Input, Output);
const
	MaxLen = 1000;
type
	TIndex = Longint;
	TPrefix = array [1..MaxLen] of TIndex;
	TString = AnsiString;
var
	Prefix: TPrefix;
	Pattern, Text: TString;

procedure ComputePrefix;
var
	i, k: TIndex;
begin
	Prefix[1] := 0;
	k := Prefix[1];
	for i := 2 to Length(Pattern) do
	begin
		while (k > 0) and (Pattern[k + 1] <> Pattern[i]) do
			k := Prefix[k];
		if Pattern[k + 1] = Pattern[i] then
			Inc(k);
		Prefix[i] := k;
	end;
end;
procedure Match;
var
	i, k: TIndex;
begin
	k := 0;
	for i := 1 to Length(Text) do
	begin
		while (k > 0) and (Pattern[k + 1] <> Text[i]) do
			k := Prefix[k];
		if Pattern[k + 1] = Text[i] then
			Inc(k);
		if k = Length(Pattern) then
		begin
			Writeln(i - k + 1);
			k := Prefix[k]; //Seek for next match
		end;
	end;
end;
procedure Main;
begin
	Readln(Pattern);
	Readln(Text);
	ComputePrefix;
	Match;
end;
begin
	Main;
end.



