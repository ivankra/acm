(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: AATree
	Category: Data Structure
	Version: 1.0
	Remark: N/A
	Tested Problems: N/A
	Date: 2006-11-16
*)
program ASSL_AATree(Input, Output);
const
	Infinity = 65535;
type
	TIndex = Longint;
	TKey = Longint;
	TLevel = Longint;
	PAANode = ^TAANode;
	TAANode = record
		Left, Right: PAANode;
		Key: TKey;
		Level: TLevel;
	end;
var
	NullNode: PAANode;
	DeletePtr, LastPtr: PAANode;

function Initalize: PAANode;
begin
	if NullNode = nil then
	begin
		New(NullNode);
		NullNode^.Left := NullNode;
		NullNode^.Right := NullNode;
		NullNode^.Level := 0;
	end;
	Result := NullNode;
end;
function MakeEmpty(T: PAANode): PAANode;
begin
	if T <> NullNode then
	begin
		MakeEmpty(T^.Left);
		MakeEmpty(T^.Right);
		Dispose(T);
	end;
	Result := NullNode;
end;
function LeftRotate(T: PAANode): PAANode;
begin
	Result := T^.Left;
	T^.Left := Result^.Right;
	Result^.Right := T;
end;
function RightRotate(T: PAANode): PAANode;
begin
	Result := T^.Right;
	T^.Right := Result^.Left;
	Result^.Left := T;
end;
function Find(T: PAANode; Key: TKey): PAANode;
begin
	while T <> NullNode do
		if Key < T^.Key then
			T := T^.Left
		else if Key > T^.Key then
			T := T^.Right
		else
			Break;
	Result := T;
end;
function FindMin(T: PAANode): PAANode;
begin
	if T <> NullNode then
		while T^.Left <> NullNode do
			T := T^.Left;
	Result := T;
end;
function FindMax(T: PAANode): PAANode;
begin
	if T <> NullNode then
		while T^.Right <> NullNode do
			T := T^.Right;
	Result := T;
end;
function Skew(T: PAANode): PAANode;
begin
	if T^.Left^.Level = T^.Level then T := LeftRotate(T);
	Result := T;
end;
function Split(T: PAANode): PAANode;
begin
	if T^.Right^.Right^.Level = T^.Level then
	begin
		T := RightRotate(T);
		Inc(T^.Level);
	end;
	Result := T;
end;
function Insert(T: PAANode; Key: TKey): PAANode;
begin
	if T = NullNode then
	begin
		New(T);
		T^.Left := NullNode;
		T^.Right := NullNode;
		T^.Key := Key;
		T^.Level := 1;
	end
	else if Key < T^.Key then
		T^.Left := Insert(T^.Left, Key)
	else if Key > T^.Key then
		T^.Right := Insert(T^.Right, Key);
	T := Skew(T);
	T := Split(T);
	Result := T;
end;
function Remove(T: PAANode; Key: TKey): PAANode;
begin
	if T <> NullNode then
	begin
		LastPtr := T;
		if Key < T^.Key then
			T^.Left := Remove(T^.Left, Key)
		else
		begin
			DeletePtr := T;
			T^.Right := Remove(T^.Right, Key);
		end;
		if T = LastPtr then
		begin
			if (DeletePtr <> NullNode) and (Key = DeletePtr^.Key) then
			begin
				DeletePtr^.Key := T^.Key;
				DeletePtr := NullNode;
				T := T^.Right;
				Dispose(LastPtr);
			end;
		end
		else if (T^.Left^.Level < T^.Level - 1) or (T^.Right^.Level < T^.Level - 1) then
		begin
			Dec(T^.Level);
			if T^.Right^.Level > T^.Level then T^.Right^.Level := T^.Level;
			T := Skew(T);
			T^.Right := Skew(T^.Right);
			T^.Right^.Right := Skew(T^.Right^.Right);
			T := Split(T);
			T^.Right := Split(T^.Right);
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
