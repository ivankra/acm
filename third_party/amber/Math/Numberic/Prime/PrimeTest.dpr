(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Naive Prime Test
	Category: Math - Numberic - Prime - Naive Prime Test
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: Ural 1343 Fairy tale
*)
program ASSL_PrimeTest(Input, Output);
type
	TIndex = Longint;
	TData = Int64;

function IsPrime(N: TData): Boolean; //Here N > 0
var
	A: TIndex;
begin
	Result := false;
	if N = 1 then Exit;
	if not Odd(N) then
	begin
		if N = 2 then Result := true;
		Exit;
	end;
	A := 3;
	while A * A <= N do
	begin
		if N mod A = 0 then Exit;
		Inc(A, 2);
	end;
	Result := true;
end;
begin
end.

