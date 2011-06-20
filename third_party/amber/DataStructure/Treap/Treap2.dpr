(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Treap
	Category: Data Structure
	Version: 2.0
	Remark: Object
	Tested Problems: POI 2000 Pro
	Date: 2006-11-16
*)
program ASSL_Treap2(Input, Output);
const
	Infinity = MaxLongint div 2;
type
	TIndex = Longint;
	TData = Int64;
	PTreapNode = ^TTreapNode;
	TTreapNode = record
		Key: TIndex;
		Priority: TIndex;
		Count: TIndex;
		LeftNode, RightNode: PTreapNode;
	end;
	TTreap = object
		NullNode, RootNode: PTreapNode;
		procedure Initialize;
		procedure LeftRotate(var CurNode: PTreapNode);
		procedure RightRotate(var CurNode: PTreapNode);
		procedure InsertNode(var CurNode: PTreapNode; Key: TIndex);
		procedure DeleteNode(var CurNode: PTreapNode; Key: TIndex);
		function GetMinimum: TIndex;
		function GetMaximum: TIndex;
	end;

procedure TTreap.Initialize;
begin
	New(NullNode);
	NullNode^.Priority := Infinity;
	NullNode^.LeftNode := NullNode;
	NullNode^.RightNode := NullNode;
	RootNode := NullNode;
end;
procedure TTreap.LeftRotate(var CurNode: PTreapNode);
var
	TmpNode: PTreapNode;
begin
	TmpNode := CurNode^.LeftNode;
	CurNode^.LeftNode := TmpNode^.RightNode;
	TmpNode^.RightNode := CurNode;
	CurNode := TmpNode;
end;
procedure TTreap.RightRotate(var CurNode: PTreapNode);
var
	TmpNode: PTreapNode;
begin
	TmpNode := CurNode^.RightNode;
	CurNode^.RightNode := TmpNode^.LeftNode;
	TmpNode^.LeftNode := CurNode;
	CurNode := TmpNode;
end;
procedure TTreap.InsertNode(var CurNode: PTreapNode; Key: TIndex);
begin
	if CurNode = NullNode then
	begin
		New(CurNode);
		CurNode^.Key := Key;
		CurNode^.Priority := Random(Infinity);
		CurNode^.Count := 1;
		CurNode^.LeftNode := NullNode;
		CurNode^.RightNode := NullNode;
	end
	else if Key < CurNode^.Key then
	begin
		InsertNode(CurNode^.LeftNode, Key);
		if CurNode^.LeftNode^.Priority < CurNode^.Priority then
			LeftRotate(CurNode);
	end
	else if Key > CurNode^.Key then
	begin
		InsertNode(CurNode^.RightNode, Key);
		if CurNode^.RightNode^.Priority < CurNode^.Priority then
			RightRotate(CurNode);
	end
	else //if CurNode^.Key = Key then
		Inc(CurNode^.Count);
end;
procedure TTreap.DeleteNode(var CurNode: PTreapNode; Key: TIndex);
begin
	if Key < CurNode^.Key then
		DeleteNode(CurNode^.LeftNode, Key)
	else if Key > CurNode^.Key then
		DeleteNode(CurNode^.RightNode, Key)
	else if CurNode^.Count > 1 then
		Dec(CurNode^.Count)
	else if (CurNode^.LeftNode = NullNode) and (CurNode^.RightNode = NullNode) then
	begin
		Dispose(CurNode);
		CurNode := NullNode;
	end
	else
	begin
		if CurNode^.LeftNode^.Priority < CurNode^.RightNode^.Priority then
			LeftRotate(CurNode)
		else
			RightRotate(CurNode);
		DeleteNode(CurNode, Key);
	end;
end;
function TTreap.GetMinimum: TIndex;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	while CurNode^.LeftNode <> NullNode do
		CurNode := CurNode^.LeftNode;
	Result := CurNode^.Key;
end;
function TTreap.GetMaximum: TIndex;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	while CurNode^.RightNode <> NullNode do
		CurNode := CurNode^.RightNode;
	Result := CurNode^.Key;
end;
var
	N: TIndex;
	Treap: TTreap;
	Sum: TData;

procedure Main;
var
	i, j: TIndex;
	Value: TIndex;
begin
	Treap.Initialize;
	Readln(N);
	Sum := 0;
	for i := 1 to N do
	begin
		Read(j);
		while j > 0 do
		begin
			Dec(j);
			Read(Value);
			Treap.InsertNode(Treap.RootNode, Value);
		end;
		Readln;
		Inc(Sum, Treap.GetMaximum - Treap.GetMinimum);
		Treap.DeleteNode(Treap.RootNode, Treap.GetMaximum);
		Treap.DeleteNode(Treap.RootNode, Treap.GetMinimum);
	end;
	Writeln(Sum);
end;
begin
	Main;
end.
