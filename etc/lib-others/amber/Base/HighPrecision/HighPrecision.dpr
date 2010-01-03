(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: High Precision
	Category: Base algorithm
	Version: 1.0
	Date: 2006-10-24
	Remark: N/A
	Tested Problems: N/A
*)
program ASSL_HighPrecision(Input, Output);
const
	MaxLen = 100;
type
	TIndex = Longint;
	TData = Longint;
	THP = record
		Len: Longint;
		D: array[1..MaxLen] of Longint;
	end;

function Compare(a, b: THP): TData; forward;
procedure Add(a, b: THP; var c: THP); forward;
procedure Subtract(a, b: THP; var c: THP); forward;
procedure Multiply(a: THP; b: TData; var c: THP); forward;
procedure MultiplyHigh(a, b: THP; var c: THP); forward;
procedure Divide(a: THP; b: TData; var c: THP; var d: TData); forward;
procedure DivideHigh(a, b: THP; var c, d: THP); forward;
procedure Extract(a: THP; b: TIndex; var c, d: THP); forward;

function Compare(a, b: THP): TData;
var
	Len: TIndex;
begin
	if a.Len > b.Len then
		Len := a.Len
	else
		Len := b.Len;
	while (Len > 1) and (a.D[Len] = b.D[Len]) do
		Dec(Len);
	Compare := a.D[Len] - b.D[Len];
end;

procedure Add(a, b: THP; var c: THP);
var
	i, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	if a.Len > b.Len then
		Len := a.Len
	else
		Len := b.Len;
	for i := 1 to Len do
	begin
		Inc(c.D[i], a.D[i] + b.D[i]);
		Inc(c.D[i + 1], c.D[i] div 10);
		c.D[i] := c.D[i] mod 10;
	end;
	if c.D[Len + 1] > 0 then Inc(Len);
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure Subtract(a, b: THP; var c: THP);
var
	t: THP;
	i, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	if Compare(a, b) < 0 then
	begin
		t := a;
		a := b;
		b := t;
	end;
	Len := a.Len;
	for i := 1 to Len do
	begin
		Inc(c.D[i], a.D[i] - b.D[i]);
		if c.D[i] < 0 then
		begin
			Inc(c.D[i], 10);
			Dec(c.D[i + 1]);
		end;
	end;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure Multiply(a: THP; b: TData; var c: THP);
var
	i, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	Len := a.Len;
	for i := 1 to Len do
	begin
		Inc(c.D[i], a.D[i] * b);
		Inc(c.D[i + 1], c.D[i] div 10);
		c.D[i] := c.D[i] mod 10;
	end;
	while c.D[Len + 1] > 0 do
	begin
		Inc(Len);
		Inc(c.D[Len + 1], c.D[Len] div 10);
		c.D[Len] := c.D[Len] mod 10;
	end;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure MultiplyHigh(a, b: THP; var c: THP);
var
	i, j, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	for i := 1 to a.Len do
		for j := 1 to b.Len do
		begin
			Inc(c.D[i + j - 1], a.D[i] * b.D[j]);
			Inc(c.D[i + j], c.D[i + j - 1] div 10);
			c.D[i + j - 1] := c.D[i + j - 1] mod 10;
		end;
	Len := a.Len + b.Len + 1;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure Divide(a: THP; b: TData; var c: THP; var d: TData); {c=a div b;d=a mod b}
var
	i, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	d := 0;
	if b = 0 then Exit;
	Len := a.Len;
	for i := Len downto 1 do
	begin
		d := d * 10 + a.D[i];
		c.D[i] := d div b;
		d := d mod b;
	end;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure Multiply10(var a: THP);
var
	i, Len: TIndex;
begin
	Len := a.Len;
	for i := Len + 1 downto 2 do
		a.D[i] := a.D[i - 1];
	a.D[1] := 0;
	Inc(Len);
	while (Len > 1) and (a.D[Len] = 0) do
		Dec(Len);
	a.Len := Len;
end;

procedure DivideHigh(a, b: THP; var c, d: THP); {c=a div b;d=a mod b}
var
	i, Len: TIndex;
begin
	FillChar(c, SizeOf(c), 0);
	FillChar(d, SizeOf(d), 0);
	if (b.Len = 1) and (b.D[1] = 0) then Exit;
	d.Len := 1;
	Len := a.Len;
	for i := Len downto 1 do
	begin
		Multiply10(d);
		d.D[1] := a.D[i];
		while Compare(d, b) >= 0 do
		begin
			Subtract(d, b, d);
			Inc(c.D[i]);
		end;
	end;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
end;

procedure Extract(a: THP; b: TIndex; var c, d: THP);{c=int(a^(1/b)) d=a-e^b}
var
	i, j, k, Len: TIndex;
	q, t: THP;
begin
	FillChar(c, SizeOf(c), 0);
	Len := (a.Len - 1) div b + 1;
	c.Len := Len;
	for i := Len downto 1 do
	begin
		q := c;
		for j := 0 to 9 do
		begin
			q.D[i] := j;
			t := q;
			for k := 1 to b - 1 do
				MultiplyHigh(t, q, t);
			if Compare(a, t) < 0 then
				Break
			else
				c.D[i] := j;
		end;
	end;
	while (Len > 1) and (c.D[Len] = 0) do
		Dec(Len);
	c.Len := Len;
	t := c;
	for k := 1 to b - 1 do
		MultiplyHigh(t, c, t);
	Subtract(a, t, d);
end;

procedure Print(a: THP);
var
	i: TIndex;
begin
	for i := a.Len downto 1 do
		Write(a.D[i]);
	Writeln;
end;

procedure Main;
var
	i: TIndex;
	a, b, c, d: THP;
	d1, k: TIndex;
	Code: Integer;
	St: string;
begin
	FillChar(a, Sizeof(a), 0);
	Readln(St);
	a.Len := Length(St);
	for i := 1 to a.Len do
		a.D[i] := Ord(St[a.Len - i + 1]) - Ord('0');
	FillChar(b, Sizeof(b), 0);
	Readln(St);
	b.Len := Length(St);
	Val(St, k, Code);
	for i := 1 to b.Len do
		b.D[i] := Ord(St[b.Len - i + 1]) - Ord('0');
	Writeln('Add');
	Add(a, b, c);
	Print(c);
	Writeln('Subtract');
	Subtract(a, b, c);
	Print(c);
	Writeln('Multiply');
	Multiply(a, k, c);
	Print(c);
	MultiplyHigh(a, b, c);
	Print(c);
	Writeln('Divide');
	Divide(a, k, c, d1);
	Print(c);
	Writeln(d1);
	DivideHigh(a, b, c, d);
	Print(c);
	Print(d);
	Writeln('Extract');
	Extract(a, k, c, d);
	Print(c);
	Print(d);
end;
begin
	Main;
end.


