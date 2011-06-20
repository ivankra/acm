(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Treap
	Category: Data Structure
	Version: 3.0
	Remark: Object
	Tested Problems: POI 2000 Pro
	Date: 2006-11-16
*)
program ASSL_Treap3(Input, Output);
const
	Infinity = MaxLongint div 2;
type
	TIndex = Longint;
	TData = Int64;
	PTreapNode = ^TTreapNode;
	TTreapNode = record
		Key: TData;
		Priority: TIndex;
		Count: TIndex;
		Total: TIndex;
		LeftNode, RightNode: PTreapNode;
	end;
	TTreap = object
		NullNode, RootNode: PTreapNode;
		procedure Initialize;
		procedure UpdateSum(var CurNode: PTreapNode);
		procedure LeftRotate(var CurNode: PTreapNode);
		procedure RightRotate(var CurNode: PTreapNode);
		procedure InsertNode(var CurNode: PTreapNode; const Key: TData);
		procedure DeleteNode(var CurNode: PTreapNode; const Key: TData);
		function GetMinimum: TData;
		function GetMaximum: TData;
		procedure Insert(const Key: TData);
		procedure Delete(const Key: TData);
		function FindRank(Rank: TIndex): TData;
		function GetRank(const Key: TData): TIndex;
	end;

procedure TTreap.Initialize;
begin
	New(NullNode);
	NullNode^.Priority := Infinity;
	NullNode^.Count := 0;
	NullNode^.Total := 0;
	NullNode^.LeftNode := NullNode;
	NullNode^.RightNode := NullNode;
	RootNode := NullNode;
end;
procedure TTreap.UpdateSum(var CurNode: PTreapNode);
begin
	CurNode^.Total := CurNode^.LeftNode^.Total + CurNode^.RightNode^.Total + CurNode^.Count;
end;
procedure TTreap.LeftRotate(var CurNode: PTreapNode);
var
	TmpNode: PTreapNode;
begin
	TmpNode := CurNode^.LeftNode;
	CurNode^.LeftNode := TmpNode^.RightNode;
	TmpNode^.RightNode := CurNode;
	UpdateSum(CurNode);
	UpdateSum(TmpNode);
	CurNode := TmpNode;
end;
procedure TTreap.RightRotate(var CurNode: PTreapNode);
var
	TmpNode: PTreapNode;
begin
	TmpNode := CurNode^.RightNode;
	CurNode^.RightNode := TmpNode^.LeftNode;
	TmpNode^.LeftNode := CurNode;
	UpdateSum(CurNode);
	UpdateSum(TmpNode);
	CurNode := TmpNode;
end;
procedure TTreap.InsertNode(var CurNode: PTreapNode; const Key: TData);
begin
	if CurNode = NullNode then
	begin
		New(CurNode);
		CurNode^.Key := Key;
		CurNode^.Priority := Random(Infinity);
		CurNode^.Count := 1;
		CurNode^.Total := 1;
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
	UpdateSum(CurNode);
end;
procedure TTreap.DeleteNode(var CurNode: PTreapNode; const Key: TData);
begin
	if CurNode <> NullNode then
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
	UpdateSum(CurNode);
end;
function TTreap.GetMinimum: TData;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	while CurNode^.LeftNode <> NullNode do
		CurNode := CurNode^.LeftNode;
	Result := CurNode^.Key;
end;
function TTreap.GetMaximum: TData;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	while CurNode^.RightNode <> NullNode do
		CurNode := CurNode^.RightNode;
	Result := CurNode^.Key;
end;
procedure TTreap.Insert(const Key: TData);
begin
	InsertNode(RootNode, Key);
end;
procedure TTreap.Delete(const Key: TData);
begin
	DeleteNode(RootNode, Key);
end;
function TTreap.FindRank(Rank: TIndex): TData;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	while CurNode <> NullNode do
		if Rank <= CurNode^.LeftNode^.Total then
			CurNode := CurNode^.LeftNode
		else
		begin
			Dec(Rank, CurNode^.LeftNode^.Total);
			if Rank <= CurNode^.Count then Break;
			Dec(Rank, CurNode^.Count);
			CurNode := CurNode^.RightNode;
		end;
	Result := CurNode^.Key;
end;
function TTreap.GetRank(const Key: TData): TIndex;
var
	CurNode: PTreapNode;
begin
	CurNode := RootNode;
	Result := 0;
	while CurNode <> NullNode do
		if Key < CurNode^.Key then
			CurNode := CurNode^.LeftNode
		else
		begin
			Inc(Result, CurNode^.LeftNode^.Total + CurNode^.Count);
			if Key = CurNode^.Key then Break;
			CurNode := CurNode^.RightNode;
		end;
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
			Treap.Insert(Value);
		end;
		Readln;
		Inc(Sum, Treap.GetMaximum - Treap.GetMinimum);
		Treap.Delete(Treap.GetMaximum);
		Treap.Delete(Treap.GetMinimum);
	end;
	Writeln(Sum);
end;
begin
	Main;
end.
