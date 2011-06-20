(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Splay
	Category: Data Structure
	Version: 2.0
	Remark: From top go down, Object
	Tested Problems: POI 2000 Pro
	Date: 2006-11-16
*)
program ASSL_Splay2(Input, Output);
const
	Infinity = MaxLongint div 2;
type
	TIndex = Longint;
	TData = Int64;
	PSplayNode = ^TSplayNode;
	TSplayNode = record
		Key: TIndex;
		Count: TIndex;
		LeftNode, RightNode: PSplayNode;
	end;
	TSplay = object
		NullNode, RootNode: PSplayNode;
		procedure Initialize;
		procedure LeftRotate(var CurNode: PSplayNode);
		procedure RightRotate(var CurNode: PSplayNode);
		procedure Splay(var CurNode: PSplayNode; Key: TIndex);
		procedure InsertNode(Key: TIndex);
		procedure DeleteNode(Key: TIndex);
		function GetMinimum: TIndex;
		function GetMaximum: TIndex;
	end;

procedure TSplay.Initialize;
begin
	New(NullNode);
	NullNode^.Key := 0;
	NullNode^.LeftNode := NullNode;
	NullNode^.RightNode := NullNode;
	RootNode := NullNode;
end;
procedure TSplay.LeftRotate(var CurNode: PSplayNode);
var
	TmpNode: PSplayNode;
begin
	TmpNode := CurNode^.LeftNode;
	CurNode^.LeftNode := TmpNode^.RightNode;
	TmpNode^.RightNode := CurNode;
	CurNode := TmpNode;
end;
procedure TSplay.RightRotate(var CurNode: PSplayNode);
var
	TmpNode: PSplayNode;
begin
	TmpNode := CurNode^.RightNode;
	CurNode^.RightNode := TmpNode^.LeftNode;
	TmpNode^.LeftNode := CurNode;
	CurNode := TmpNode;
end;
procedure TSplay.Splay(var CurNode: PSplayNode; Key: TIndex);
begin
	if Key < CurNode^.Key then
	begin
		if CurNode^.LeftNode <> NullNode then
		begin
			Splay(CurNode^.LeftNode, Key);
			LeftRotate(CurNode);
		end;
	end
	else if Key > CurNode^.Key then
	begin
		if CurNode^.RightNode <> NullNode then
		begin
			Splay(CurNode^.RightNode, Key);
			RightRotate(CurNode);
		end;
	end;
end;
procedure TSplay.InsertNode(Key: TIndex);
var
	CurNode: PSplayNode;
begin
	Splay(RootNode, Key);
	if Key < RootNode^.Key then
	begin
		New(CurNode);
		CurNode^.Key := Key;
		CurNode^.Count := 1;
		CurNode^.LeftNode := RootNode^.LeftNode;
		CurNode^.RightNode := RootNode;
		RootNode^.LeftNode := NullNode;
		RootNode := CurNode;
	end
	else if Key > RootNode^.Key then
	begin
		New(CurNode);
		CurNode^.Key := Key;
		CurNode^.Count := 1;
		CurNode^.LeftNode := RootNode;
		CurNode^.RightNode := RootNode^.RightNode;
		RootNode^.RightNode := NullNode;
		RootNode := CurNode;
	end
	else //if RootNode^.Key = Key then
		Inc(RootNode^.Count);
end;
procedure TSplay.DeleteNode(Key: TIndex);
var
	CurNode: PSplayNode;
begin
	Splay(RootNode, Key);
	if Key = RootNode^.Key then
		if RootNode^.Count > 1 then
			Dec(RootNode^.Count)
		else
		begin
			if RootNode^.LeftNode = NullNode then
				CurNode := RootNode^.RightNode
			else
			begin
				CurNode := RootNode^.LeftNode;
				Splay(CurNode, Key);
				CurNode^.RightNode := RootNode^.RightNode;
			end;
			Dispose(RootNode);
			RootNode := CurNode;
		end;
end;
function TSplay.GetMinimum: TIndex;
begin
	Splay(RootNode, -Infinity);
	Result := RootNode^.Key;
end;
function TSplay.GetMaximum: TIndex;
begin
	Splay(RootNode, Infinity);
	Result := RootNode^.Key;
end;
var
	N: TIndex;
	Splay: TSplay;
	Sum: TData;

procedure Main;
var
	i, j: TIndex;
	Value: TIndex;
begin
	Splay.Initialize;
	Readln(N);
	Sum := 0;
	for i := 1 to N do
	begin
		Read(j);
		while j > 0 do
		begin
			Dec(j);
			Read(Value);
			Splay.InsertNode(Value);
		end;
		Readln;
		Inc(Sum, Splay.GetMaximum - Splay.GetMinimum);
		Splay.DeleteNode(Splay.GetMaximum);
		Splay.DeleteNode(Splay.GetMinimum);
	end;
	Writeln(Sum);
end;
begin
	Main;
end.
