(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Modular Linear Equation
	Category: Math - Numberic - Modular - Modular Linear Equation System
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_ModularLinearEquationSystem(Input, Output);
const
	MaxN = 100;
type
	TIndex = Longint;
	TData = Longint;
	TModulo = array[1..MaxN] of TData;
	TResidue = array[1..MaxN] of TData;
var
	N: TIndex;
	M: TModulo;
	R: TResidue;

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

function ModularLinearEquationSystem: TData; // x=Ri(mod Mi), GCD(Mi,Mj)=1 for any i,j
var
	i: TIndex;
	S: TData;
	X, Y: TData;
begin
	S := 1;
	for i := 1 to N do
		S := S * M[i];
	Result := 0;
	for i := 1 to N do
	begin
		ExtendedGCD(S div M[i], M[i], X, Y);
		Result := (Result + S div M[i] * X * R[i]) mod S;
	end;
	if Result < 0 then
		Inc(Result, S);
end;

procedure Main;
var
	i: TIndex;
begin
	Readln(N); //A,B>0
	for i := 1 to N do
		Readln(R[i], M[i]);
	Writeln(ModularLinearEquationSystem);
end;
begin
	Main;
end.

