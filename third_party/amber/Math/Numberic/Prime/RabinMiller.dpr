(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Rabin-Miller Strong Pseudoprime Test
	Category: Math - Numberic - Prime - Rabin-Miller Strong Pseudoprime Test
	Version: 1.0
	Date: 2006-10-24
	Remark:
		Using first k prime for test	The smallest strong pseudoprime
		2	2047
		2,3	1373653
		2,3,5	25326001
		2,3,5,7	3215031751
		2,3,5,7,11	2152302898747
		2,3,5,7,11,13	3474749660383
		2,3,5,7,11,13,17	341550071728321
		2,3,5,7,11,13,17,19	341550071728321
		2,3,5,7,11,13,17,19,23	¡Ü41234316135705689041
	Tested Problems: Ural 1343 Fairy tale
*)
program ASSL_RabinMiller(Input, Output);
type
	TIndex = Longint;
	TData = Int64;
const
	TestPrimeNum = 9;
	TestPrime: array [1..TestPrimeNum] of TData = (2, 3, 5, 7, 11, 13, 17, 19, 23);

function GetMulMod(Base, Times, Divisor: TData): TData; //multiply a and b modulo c
begin
	if Times = 0 then
		Result := 0
	else
	begin
		Result := GetMulMod(Base, Times shr 1, Divisor);
		Result := Result shl 1 mod Divisor;
		if Odd(Times) then
			Result := (Result + Base) mod Divisor;
	end;
end;

function GetExpMod(Base, Exponent, Divisor: TData): TData; //power a with b modulo c
begin
	if Exponent = 0 then
		Result := 1
	else
	begin
		Result := GetExpMod(Base, Exponent shr 1, Divisor);
		Result := GetMulMod(Result, Result, Divisor);
		if Odd(Exponent) then
			Result := GetMulMod(Result, Base, Divisor);
	end;
end;
function IsPrime(N: TData): Boolean; //Here N > 0
var
	i: TIndex;
	A: TData;
begin
	Result := false;
	if (N = 1) or ((N <> 2) and not Odd(N)) then Exit;
	for i := 1 to TestPrimeNum do
	begin
		if TestPrime[i] >= N then Continue;
		if GetExpMod(TestPrime[i], N - 1, N) = 1 then Continue;
		Exit;
	end;
	Result := true;
end;
var
	M: TIndex;

procedure Main;
var
	i: TIndex;
	Cur: TData;
begin
	Readln(M);
	for i := 1 to M do
	begin
		Readln(Cur);
		Writeln(IsPrime(Cur));
	end;
end;
begin
	Main;
end.

