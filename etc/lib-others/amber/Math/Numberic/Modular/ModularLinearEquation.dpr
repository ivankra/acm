(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Modular Linear Equation
	Category: Math - Numberic - Modular - Modular Linear Equation
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_ModularLinearEquation(Input, Output);
const
	MaxN = 100;
type
	TIndex = Longint;
	TData = Longint;
	TAnswer = array [1..MaxN] of TData;
var
	A, B, N: TIndex;
	D: TIndex; //GCD(A,B) and the number of the solutions
	Answer: TAnswer;

function ExtendedGCD(A, B: TData; var X, Y: TData): TData; //A*X+B*Y=GCD(A,B)
begin
	if A < B then
		Result := ExtendedGCD(B, A, Y, X)
	else if B = 0 then
	begin
		Result := A;
		X := 1;
		Y := 0;
	end
	else
	begin
		Result := ExtendedGCD(B, A mod B, Y, X);
		Dec(Y, A div B * X);
	end;
end;

function ModularLinearEquation: Boolean; // Ax=B(mod N)
var
	i: TIndex;
	X, Y: TData;
	E: TData;
begin
	D := ExtendedGCD(A, N, X, Y);
	Result := false;
	if B mod D <> 0 then Exit; //No solution
	E := X * (B div D) mod N;
	if E < 0 then Inc(E, N); //Keep E positive
	for i := 0 to D - 1 do
		Answer[i + 1] := (E + i * N div D) mod N;
	Result := true;
end;

procedure Main;
var
	i: TIndex;
begin
	Readln(A, B, N); //A, B>0
	if ModularLinearEquation then
	begin
		for i := 1 to D do
			Writeln(Answer[i]);
	end
	else
		Writeln('No answer');
end;
begin
	Main;
end.


