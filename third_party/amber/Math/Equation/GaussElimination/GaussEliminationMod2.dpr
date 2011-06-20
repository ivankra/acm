(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Gauss Elimination
	Category: Math - Equation - Gauss Elimination
	Version: 2.0 Boolean Equation
	Date: 2006-10-24
	Remark: 
		i表示当前所在方程
		j表示当前处理变量
		若没有方程有j变量，则j++;
		否则，交换方程i与有j变量的方程，用方程i，消去所有含有j变量的方程的j变量，j++,i++。
	Tested Problems: SGU 260
*)
program ASSL_GaussEliminationMod2(Input, Output);
const
	MaxN = 200;
type
	TIndex = Longint;
	TEquation = array [1..MaxN + 1] of Boolean;
	TEquations = array [1..MaxN] of TEquation;
	TAnswer = array [1..MaxN] of Boolean;
	TFree = array [1..MaxN] of Boolean;
var
	N: TIndex;

function Solve(Equation: TEquations): Boolean;
var
	i, j, p, q: TIndex;
	Count: TIndex;
	Tmp: TEquation;
	Answer: TAnswer;
	Free: TFree;
begin
	Result := false;
	FillChar(Free, sizeof(Free), true);
	i := 1; //Current Equation
	for j := 1 to N do //Current Variable
	begin
		for p := i to N do
			if Equation[p][j] then
			begin
				Tmp := Equation[p];
				Equation[p] := Equation[i];
				Equation[i] := Tmp;
				Break;
			end;
		if not Equation[i][j] then Continue;
		Free[j] := false;
		for p := i + 1 to N do
			if Equation[p][j] then
				for q := N + 1 downto j do
					Equation[p][q] := Equation[p][q] xor Equation[i][q];
		Inc(i);
	end;
	//No solution
	for p := i to N do
		if Equation[p, N + 1] then
			Exit;
	FillChar(Answer, SizeOf(Answer), 0);
	Count := 0;
	for j := N downto 1 do
		if not Free[j] then
		begin
			Dec(i);
			Answer[j] := Equation[i, N + 1];
			for q := j + 1 to N do
				Answer[j] := Answer[j] xor (Answer[q] and Equation[i][q]);
			if Answer[j] then Inc(Count);
		end;
	Writeln(Count);
	for j := 1 to N do
		if Answer[j] then
			Write(j, ' ');
	Writeln;
	Result := true;
end;
procedure Main;
var
	i, j, k: TIndex;
	Equation: TEquations;
begin
	FillChar(Equation, SizeOf(Equation), 0);
	Readln(N);
	for i := 1 to N do
	begin
		Read(k);
		while k > 0 do
		begin
			Dec(k);
			Read(j);
			Equation[j][i] := true;
		end;
		Readln;
	end;
	for i := 1 to N do
	begin
		Read(j);
		Equation[i][N + 1] := (j = 1);
	end;
	Readln;
	if Solve(Equation) then Exit;
	for i := 1 to N do
		Equation[i][N + 1] := not Equation[i][N + 1];
	if Solve(Equation) then Exit;
	Writeln(-1);
end;
begin
	Main;
end.
