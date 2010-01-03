(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Extended GCD
	Category: Math - Numberic - Modular - Extended GCD
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_ExtendedGCD(Input, Output);
type
	TData = Longint;

function ExtendedGCD(A, B: TData; var X, Y: TData): TData; //A*X+B*Y=GCD(A,B)
begin
	if B = 0 then
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
procedure Main;
var
	X, Y: TData;
	A, B, C: TData;
begin
	Readln(A, B); //A, B>0
	C := ExtendedGCD(A, B, X, Y);
	Writeln(X, '*', A, '+', Y, '*', B, '=', C);
end;
begin
	Main;
end.

