(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Treap
	Category: Data Structure
	Version: 1.0
	Remark: XXXXXXXX
	Tested Problems: N/A
	Date: 2006-11-16
*)
program ASSL_Treap(Input, Output);
const
	Infinity = 65535;
type
	TIndex = Longint;
	TKey = Longint;
	TPriority = Word;
	PTreapNode = ^TTreapNode;
	TTreapNode = record
		Left, Right: PTreapNode;
		Priority: TPriority;
		Key: TKey;
	end;
var
	NullNode: PTreapNode;

procedure Initalize;
begin
	if NullNode = nil then
	begin
		New(NullNode);
		NullNode^.Left := NullNode;
		NullNode^.Right := NullNode;
		NullNode^.Priority := Infinity;
	end;
end;

function FindMax(T: PTreapNode): PTreapNode;
begin
	if T <> NullNode then
		while T^.Right <> NullNode do
			T := T^.Right;
	Result := T;
end;

function FindMin(T: PTreapNode): PTreapNode;
begin
	if T <> NullNode then
		while T^.Left <> NullNode do
			T := T^.Left;
	Result := T;
end;

function Find(T: PTreapNode; Key: TKey): PTreapNode;
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

function LeftRotate(T: PTreapNode): PTreapNode;
begin
	Result := T^.Left;
	T^.Left := Result^.Right;
	Result^.Right := T;
end;

function RightRotate(T: PTreapNode): PTreapNode;
begin
	Result := T^.Right;
	T^.Right := Result^.Left;
	Result^.Left := T;
end;

function InsertNode(Key: TKey; T: PTreapNode): PTreapNode;
begin
	if T = NullNode then
	begin
		New(T);
		T^.Left := NullNode;
		T^.Right := NullNode;
		T^.Key := Key;
		T^.Priority := Random(65535);
	end
	else if Key < T^.Key then
	begin
		T^.Left := InsertNode(Key, T^.Left);
		if T^.Left^.Priority < T^.Priority then
			T := LeftRotate(T);
	end
	else if Key > T^.Key then
	begin
		T^.Right := InsertNode(Key, T^.Right);
		if T^.Right^.Priority < T^.Priority then
			T := RightRotate(T);
	end;
	Result := T;
end;

function DeleteNode(Key: TKey; T: PTreapNode): PTreapNode;
begin
	if T <> NullNode then
		if Key < T^.Key then
			T^.Left := DeleteNode(Key, T^.Left)
		else if Key > T^.Key then
			T^.Right := DeleteNode(Key, T^.Right)
		else
		begin
			if T^.Left^.Priority < T^.Right^.Priority then
				T := LeftRotate(T)
			else
				T := RightRotate(T);
			if T <> NullNode then
				T := DeleteNode(Key, T)
			else //RightRotate
			begin
				Dispose(T^.Left);
				T^.Left := NullNode;
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