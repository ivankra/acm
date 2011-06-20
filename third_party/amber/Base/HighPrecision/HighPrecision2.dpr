(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: High Precision
	Category: Base algorithm
	Version: 2.0
	Date: 2006-10-24
	Remark: TData using LongInt is more faster than using Int64 if there is multiply, divide operation.
	Tested Problems: N/A
*)
program ASSL_HighPrecision2(Input, Output);
const
	UnitDigit = 4;
	UnitSize = 10000;
	MaxLen = 100 div UnitDigit;
type
	TIndex = Longint;
	TData = Longint;
	THP = record
		Len: TIndex;
		D: array [1..MaxLen] of TData;
	end;

//-----------------------------------------------
procedure ReadHP(var A: THP); forward;
procedure PrintHP(const A: THP); forward;
procedure AssignValue(var A: THP; const B: TData; Offset: TIndex = 1); forward;
function Compare(const A: THP; const B: THP): TData; forward;
procedure Trim(var A: THP); forward;

function Add(const A: THP; const B: TData): THP; overload; forward;
procedure AssignAdd(var A: THP; const B: TData); overload; forward;
function Add(const A: THP; const B: THP): THP; overload; forward;
procedure AssignAdd(var A: THP; const B: THP); overload; forward;

function Subtract(const A: THP; const B: TData): THP; overload; forward;
procedure AssignSubtract(var A: THP; const B: TData); overload; forward;
function Subtract(const A: THP; const B: THP): THP; overload; forward;
procedure AssignSubtract(var A: THP; const B: THP); overload; forward;

function Multiply(const A: THP; const B: TData): THP; overload; forward;
procedure AssignMultiply(var A: THP; const B: TData); overload; forward;
function Multiply(const A: THP; const B: THP): THP; overload; forward;
procedure AssignMultiply(var A: THP; const B: THP); overload; forward;

function BinarySearchForDivide(const A: THP; const B: THP): TIndex; forward;

function Divide(const A: THP; const B: TData): THP; overload; forward;
procedure AssignDivide(var A: THP; const B: TData); overload; forward;
function Divide(const A: THP; const B: THP): THP; overload; forward;
procedure AssignDivide(var A: THP; const B: THP); overload; forward;

function Modulo(const A: THP; const B: TData): TData; overload; forward;
function Modulo(const A: THP; const B: THP): THP; overload; forward;

//-----------------------------------------------
procedure ReadHP(var A: THP);
var
	i: TIndex;
	Code: Integer;
	St: AnsiString;
	Len: TIndex;
begin
	FillChar(A, SizeOf(A), 0);
	Readln(St);
	Len := Length(St);
	A.Len := Len div UnitDigit;
	for i := 1 to A.Len do
		Val(Copy(St, Len - i * UnitDigit + 1, UnitDigit), A.D[i], Code);
	if Len mod UnitDigit > 0 then
	begin
		Inc(A.Len);
		Val(Copy(St, 1, Len mod UnitDigit), A.D[A.Len], Code);
	end;
end;
procedure PrintHP(const A: THP);
var
	i, j: TIndex;
	St: String[UnitDigit];
begin
	Write(A.D[A.Len]);
	for i := A.Len - 1 downto 1 do
	begin
		Str(A.D[i]: UnitDigit, St);
		for j := 1 to UnitDigit do
			if St[j] = ' ' then
				Write('0')
			else
				Write(St[j]);
	end;
	Writeln;
end;
procedure AssignValue(var A: THP; const B: TData; Offset: TIndex = 1); //B < UnitSize
begin
	FillChar(A, SizeOf(A), 0);
	A.Len := Offset;
	A.D[Offset] := B;
end;
function Compare(const A: THP; const B: THP): TData;
var
	i: TIndex;
begin
	Result := A.Len - B.Len;
	if Result = 0 then
	begin
		i := A.Len;
		while (i > 1) and (A.D[i] = B.D[i]) do Dec(i);
		Result := A.D[i] - B.D[i];
	end;
end;
procedure Trim(var A: THP);
begin
	while (A.Len > 1) and (A.D[A.Len] = 0) do Dec(A.Len);
end;

function Add(const A: THP; const B: TData): THP; overload;
var
	i: TIndex;
	Overflow: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Overflow := B;
	i := 1;
	while (i <= A.Len) or (Overflow > 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if Overflow >= UnitSize then
		begin
			Result.D[i] := Overflow - UnitSize;
			Overflow := 1;
		end
		else
		begin
			Result.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Result.Len := i - 1;
	Trim(Result);
end;
procedure AssignAdd(var A: THP; const B: TData); overload;
var
	i: TIndex;
	Overflow: TData;
begin
	Overflow := B;
	i := 1;
	while Overflow > 0 do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if Overflow >= UnitSize then
		begin
			A.D[i] := Overflow - UnitSize;
			Overflow := 1;
		end
		else
		begin
			A.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	if A.Len < i - 1 then A.Len := i - 1;
	Trim(A);
end;
function Add(const A: THP; const B: THP): THP; overload;
var
	i: TIndex;
	Overflow: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Overflow := 0;
	i := 1;
	while (i <= A.Len) or (i <= B.Len) or (Overflow > 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if i <= B.Len then Inc(Overflow, B.D[i]);
		if Overflow >= UnitSize then
		begin
			Result.D[i] := Overflow - UnitSize;
			Overflow := 1;
		end
		else
		begin
			Result.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Result.Len := i - 1;
	Trim(Result);
end;
procedure AssignAdd(var A: THP; const B: THP); overload;
var
	i: TIndex;
	Overflow: TData;
begin
	Overflow := 0;
	i := 1;
	while (i <= B.Len) or (Overflow > 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if i <= B.Len then Inc(Overflow, B.D[i]);
		if Overflow >= UnitSize then
		begin
			A.D[i] := Overflow - UnitSize;
			Overflow := 1;
		end
		else
		begin
			A.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	if A.Len < i - 1 then A.Len := i - 1;
	Trim(A);
end;

//A >= B
function Subtract(const A: THP; const B: TData): THP; overload;
var
	i: TIndex;
	Overflow: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Overflow := -B;
	i := 1;
	while (i <= A.Len) or (Overflow < 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if Overflow < 0 then
		begin
			Result.D[i] := Overflow + UnitSize;
			Overflow := -1;
		end
		else
		begin
			Result.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Result.Len := i - 1;
	Trim(Result);
end;
procedure AssignSubtract(var A: THP; const B: TData); overload;
var
	i: TIndex;
	Overflow: TData;
begin
	Overflow := -B;
	i := 1;
	while Overflow < 0 do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if Overflow < 0 then
		begin
			A.D[i] := Overflow + UnitSize;
			Overflow := -1;
		end
		else
		begin
			A.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Trim(A);
end;
function Subtract(const A: THP; const B: THP): THP; overload;
var
	i: TIndex;
	Overflow: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Overflow := 0;
	i := 1;
	while (i <= A.Len) or (i <= B.Len) or (Overflow < 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if i <= B.Len then Dec(Overflow, B.D[i]);
		if Overflow < 0 then
		begin
			Result.D[i] := Overflow + UnitSize;
			Overflow := -1;
		end
		else
		begin
			Result.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Result.Len := i - 1;
	Trim(Result);
end;
procedure AssignSubtract(var A: THP; const B: THP); overload;
var
	i: TIndex;
	Overflow: TData;
begin
	Overflow := 0;
	i := 1;
	while (i <= B.Len) or (Overflow < 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i]);
		if i <= B.Len then Dec(Overflow, B.D[i]);
		if Overflow < 0 then
		begin
			A.D[i] := Overflow + UnitSize;
			Overflow := -1;
		end
		else
		begin
			A.D[i] := Overflow;
			Overflow := 0;
		end;
		Inc(i);
	end;
	Trim(A);
end;

function Multiply(const A: THP; const B: TData): THP; overload;
var
	i: TIndex;
	Overflow: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Overflow := 0;
	i := 1;
	while (i <= A.Len) or (Overflow > 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i] * B);
		Result.D[i] := Overflow mod UnitSize;
		Overflow := Overflow div UnitSize;
		Inc(i);
	end;
	Result.Len := i - 1;
	Trim(Result);
end;
procedure AssignMultiply(var A: THP; const B: TData); overload;
var
	i: TIndex;
	Overflow: TData;
begin
	Overflow := 0;
	i := 1;
	while (i <= A.Len) or (Overflow > 0) do
	begin
		if i <= A.Len then Inc(Overflow, A.D[i] * B);
		A.D[i] := Overflow mod UnitSize;
		Overflow := Overflow div UnitSize;
		Inc(i);
	end;
	A.Len := i - 1;
	Trim(A);
end;
function Multiply(const A: THP; const B: THP): THP; overload;
var
	i, j: TIndex;
begin
	FillChar(Result, SizeOf(Result), 0);
	for i := 1 to A.Len do
		for j := 1 to B.Len do
		begin
			Inc(Result.D[i + j - 1], A.D[i] * B.D[j]);
			Inc(Result.D[i + j], Result.D[i + j - 1] div UnitSize);
			Result.D[i + j - 1] := Result.D[i + j - 1] mod UnitSize;
		end;
	Result.Len := A.Len + B.Len;
	Trim(Result);
end;
procedure AssignMultiply(var A: THP; const B: THP); overload;
begin
	A := Multiply(A, B);
end;

function BinarySearchForDivide(const A: THP; const B: THP): TIndex;
var
	Left, Right, Mid: TData;
begin
	Left := 0;
	Right := UnitSize - 1;
	while Left < Right do
	begin
		Mid := (Left + Right + 1) div 2;
		if Compare(Multiply(B, Mid), A) <= 0 then
			Left := Mid
		else
			Right := Mid - 1;
	end;
	Result := Left;
end;
function Divide(const A: THP; const B: TData): THP; overload;
var
	i: TIndex;
	Remain: TData;
begin
	FillChar(Result, SizeOf(Result), 0);
	Remain := 0;
	for i := A.Len downto 1 do
	begin
		Remain := Remain * UnitSize + A.D[i];
		Result.D[i] := Remain div B;
		Remain := Remain mod B;
	end;
	Result.Len := A.Len;
	Trim(Result);
end;
procedure AssignDivide(var A: THP; const B: TData); overload;
var
	i: TIndex;
	Remain: TData;
begin
	Remain := 0;
	for i := A.Len downto 1 do
	begin
		Remain := Remain * UnitSize + A.D[i];
		A.D[i] := Remain div B;
		Remain := Remain mod B;
	end;
	Trim(A);
end;
function Divide(const A: THP; const B: THP): THP; overload;
var
	i: TIndex;
	R: THP;
begin
	FillChar(Result, SizeOf(Result), 0);
	FillChar(R, SizeOf(R), 0);
	R.Len := B.Len - 1;
	Move(A.D[A.Len - R.Len + 1], R.D[1], SizeOf(TData) * R.Len);
	for i := A.Len - B.Len + 1 downto 1 do
	begin
		Move(R.D[1], R.D[2], SizeOf(TData) * R.Len);
		R.D[1] := A.D[i];
		Inc(R.Len);
		Trim(R);
		Result.D[i] := BinarySearchForDivide(R, B);
		AssignSubtract(R, Multiply(B, Result.D[i]));
	end;
	Result.Len := A.Len - B.Len + 1;
	Trim(Result);
end;
procedure AssignDivide(var A: THP; const B: THP); overload;
begin
	A := Divide(A, B);
end;
function Modulo(const A: THP; const B: TData): TData; overload;
var
	i: TIndex;
begin
	Result := 0;
	for i := A.Len downto 1 do
		Result := (Result * UnitSize + A.D[i]) mod B;
end;
function Modulo(const A: THP; const B: THP): THP; overload;
var
	i: TIndex;
begin
	FillChar(Result, SizeOf(Result), 0);
	Result.Len := B.Len - 1;
	Move(A.D[A.Len - Result.Len + 1], Result.D[1], SizeOf(TData) * Result.Len);
	for i := A.Len - B.Len + 1 downto 1 do
	begin
		Move(Result.D[1], Result.D[2], SizeOf(TData) * Result.Len);
		Result.D[1] := A.D[i];
		Inc(Result.Len);
		Trim(Result);
		AssignSubtract(Result, Multiply(B, BinarySearchForDivide(Result, B)));
	end;
end;
begin
end.

