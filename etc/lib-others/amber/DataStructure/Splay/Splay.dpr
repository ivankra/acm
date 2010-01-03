(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Splay
	Category: Data Structure
	Version: 1.0
	Remark: XXXXXXXX
	Tested Problems: N/A
	Date: 2006-11-16
*)
program ASSL_Splay(Input, Output);
const
	Infinity = 65535;
type
	TIndex = Longint;
	TKey = Longint;
	PSplayNode = ^TSplayNode;
	TSplayNode = record
		Left, Right: PSplayNode;
		Key: TKey;
	end;
var
	NullNode: PSplayNode;
	Header: TSplayNode;
	NewNode: PSplayNode;

function Initalize: PSplayNode;
begin
	if NullNode = nil then
	begin
		New(NullNode);
		NullNode^.Left := NullNode;
		NullNode^.Right := NullNode;
	end;
	Result := NullNode;
end;

function MakeEmpty(T: PSplayNode): PSplayNode;
begin
	if T <> NullNode then
	begin
		MakeEmpty(T^.Left);
		MakeEmpty(T^.Right);
		Dispose(T);
	end;
	Result := NullNode;
end;

function LeftRotate(T: PSplayNode): PSplayNode;
begin
	Result := T^.Left;
	T^.Left := Result^.Right;
	Result^.Right := T;
end;

function RightRotate(T: PSplayNode): PSplayNode;
begin
	Result := T^.Right;
	T^.Right := Result^.Left;
	Result^.Left := T;
end;

function Splay(T: PSplayNode; Key: TKey): PSplayNode;
var
	LeftTreeMax, RightTreeMin: PSplayNode;
begin
	Header.Left := NullNode;
	Header.Right := NullNode;
	LeftTreeMax := @Header;
	RightTreeMin := @Header;
	NullNode^.Key := Key;
	while Key <> T^.Key do
		if Key < T^.Key then
		begin
			if Key < T^.Left^.Key then
				T := LeftRotate(T);
			if T^.Left = NullNode then
				Break;
			//Link Right
			RightTreeMin^.Left := T;
			RightTreeMin := T;
			T := T^.Left;
		end
		else
		begin
			if Key > T^.Right^.Key then
				T := RightRotate(T);
			if T^.Right = NullNode then
				Break;
			//Link Left
			LeftTreeMax^.Right := T;
			LeftTreeMax := T;
			T := T^.Right;
		end;
	LeftTreeMax^.Right := T^.Left;
	RightTreeMin^.Left := T^.Right;
	T^.Left := Header.Right;
	T^.Right := Header.Left;
	Result := T;
end;

function Find(T: PSplayNode; Key: TKey): PSplayNode;
begin
	Result := Splay(T, Key);
end;

function FindMin(T: PSplayNode): PSplayNode;
begin
	Result := Splay(T, -Infinity);
end;

function FindMax(T: PSplayNode): PSplayNode;
begin
	Result := Splay(T, Infinity);
end;

function Insert(T: PSplayNode; Key: TKey): PSplayNode;
begin
	New(NewNode);
	NewNode^.Key := Key;
	if T = NullNode then
	begin
		NewNode^.Left := NullNode;
		NewNode^.Right := NullNode;
		T := NewNode;
	end
	else
	begin
		T := Splay(T, Key);
		if Key < T^.Key then
		begin
			NewNode^.Left := T^.Left;
			NewNode^.Right := T;
			T^.Left := NullNode;
			T := NewNode;
		end
		else if Key > T^.Key then
		begin
			NewNode^.Right := T^.Right;
			NewNode^.Left := T;
			T^.Right := NullNode;
			T := NewNode;
		end;
	end;
	Result := T;
end;

function Remove(T: PSplayNode; Key: TKey): PSplayNode;
var
	NewNode: PSplayNode;
begin
	if T <> NullNode then
	begin
		T := Splay(T, Key);
		if Key = T^.Key then
		begin
			if T^.Left = NullNode then
				NewNode := T^.Right
			else
			begin
				NewNode := Splay(T^.Left, Key);
				NewNode^.Right := T^.Right;
			end;
			Dispose(T);
			T := NewNode;
		end;
	end;
	Result := T;
end;

procedure Main;
begin
	Initalize;
end;
begin
	Main;
end.

