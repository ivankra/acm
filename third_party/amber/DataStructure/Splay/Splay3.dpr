(*
	Project: Amber Standard Sources Library [ASSL]
	Author: Amber
	Title: Splay
	Category: Data Structure
	Version: 3.0
	Remark: From bottom go up, Object
	Tested Problems: POI 2000 Pro
	Date: 2006-11-16
*)
program ASSL_Splay3(Input, Output);
const
	Infinity = MaxLongint div 2;
type
	TIndex = Longint;
	TData = Int64;
	PSplayNode = ^TSplayNode;
	TSplayNode = record
		Key: TIndex;
		Count: TIndex;
		LeftNode, RightNode, Parent: PSplayNode;
	end;
	TSplay = object
		RootNode: PSplayNode;
		procedure Initialize;
		procedure LeftRotate(CurNode: PSplayNode);
		procedure RightRotate(CurNode: PSplayNode);
		procedure Splay(CurNode: PSplayNode);
		function Find(CurNode: PSplayNode; Key: TIndex): PSplayNode;
		procedure InsertNode(Key: TIndex);
		procedure DeleteNode(Key: TIndex);
		function GetMinimum: TIndex;
		function GetMaximum: TIndex;
	end;

procedure TSplay.Initialize;
begin
	RootNode := nil;
end;
procedure TSplay.LeftRotate(CurNode: PSplayNode);
var
	PntNode, AncNode: PSplayNode;
begin
	PntNode := CurNode^.Parent;
	AncNode := PntNode^.Parent;
	PntNode^.LeftNode := CurNode^.RightNode;
	if PntNode^.LeftNode <> nil then PntNode^.LeftNode^.Parent := PntNode;
	CurNode^.RightNode := PntNode;
	PntNode^.Parent := CurNode;
	CurNode^.Parent := AncNode;
	if AncNode <> nil then
		if AncNode^.LeftNode = PntNode then
			AncNode^.LeftNode := CurNode
		else
			AncNode^.RightNode := CurNode;
end;
procedure TSplay.RightRotate(CurNode: PSplayNode);
var
	PntNode, AncNode: PSplayNode;
begin
	PntNode := CurNode^.Parent;
	AncNode := PntNode^.Parent;
	PntNode^.RightNode := CurNode^.LeftNode;
	if PntNode^.RightNode <> nil then PntNode^.RightNode^.Parent := PntNode;
	CurNode^.LeftNode := PntNode;
	PntNode^.Parent := CurNode;
	CurNode^.Parent := AncNode;
	if AncNode <> nil then
		if AncNode^.LeftNode = PntNode then
			AncNode^.LeftNode := CurNode
		else
			AncNode^.RightNode := CurNode;
end;
procedure TSplay.Splay(CurNode: PSplayNode);
var
	PntNode, AncNode: PSplayNode;
begin
	while CurNode^.Parent <> nil do
	begin
		PntNode := CurNode^.Parent;
		AncNode := PntNode^.Parent;
		if AncNode = nil then
			if PntNode^.LeftNode = CurNode then
				LeftRotate(CurNode)
			else
				RightRotate(CurNode)
		else if AncNode^.LeftNode = PntNode then
			if PntNode^.LeftNode = CurNode then
			begin
				LeftRotate(PntNode);
				LeftRotate(CurNode);
			end
			else
			begin
				RightRotate(CurNode);
				LeftRotate(CurNode);
			end
		else
			if PntNode^.RightNode = CurNode then
			begin
				RightRotate(PntNode);
				RightRotate(CurNode);
			end
			else
			begin
				LeftRotate(CurNode);
				RightRotate(CurNode);
			end;
	end;
	RootNode := CurNode;
end;
function TSplay.Find(CurNode: PSplayNode; Key: TIndex): PSplayNode;
begin
	while CurNode^.Key <> Key do
		if Key < CurNode^.Key then
		begin
			if CurNode^.LeftNode = nil then Break;
			CurNode := CurNode^.LeftNode;
		end
		else
		begin
			if CurNode^.RightNode = nil then Break;
			CurNode := CurNode^.RightNode;
		end;
	Result := CurNode;
end;
procedure TSplay.InsertNode(Key: TIndex);
var
	CurNode: PSplayNode;
begin
	New(CurNode);
	CurNode^.Key := Key;
	CurNode^.Count := 1;
	CurNode^.LeftNode := nil;
	CurNode^.RightNode := nil;
	CurNode^.Parent := nil;
	if RootNode = nil then
		RootNode := CurNode
	else
	begin
		Splay(Find(RootNode, Key));
		if Key = RootNode^.Key then
		begin
			Inc(RootNode^.Count);
			Dispose(CurNode);
		end
		else
		begin
			if Key < RootNode^.Key then
			begin
				CurNode^.LeftNode := RootNode^.LeftNode;
				if CurNode^.LeftNode <> nil then CurNode^.LeftNode^.Parent := CurNode;
				RootNode^.LeftNode := nil;
				CurNode^.RightNode := RootNode;
			end
			else
			begin
				CurNode^.RightNode := RootNode^.RightNode;
				if CurNode^.RightNode <> nil then CurNode^.RightNode^.Parent := CurNode;
				RootNode^.RightNode := nil;
				CurNode^.LeftNode := RootNode;
			end;
			if RootNode <> nil then RootNode^.Parent := CurNode;
			RootNode := CurNode;
		end;
	end;
end;
procedure TSplay.DeleteNode(Key: TIndex);
var
	CurNode: PSplayNode;
begin
	CurNode := Find(RootNode, Key);
	if Key <> CurNode^.Key then Exit;
	if CurNode^.Count > 1 then
		Dec(CurNode^.Count)
	else
	begin
		Splay(CurNode);
		if CurNode^.LeftNode = nil then
		begin
			RootNode := CurNode^.RightNode;
			if RootNode <> nil then RootNode^.Parent := nil;
		end
		else
		begin
			CurNode^.LeftNode^.Parent := nil;
			RootNode := Find(CurNode^.LeftNode, Infinity);
			Splay(RootNode);
			RootNode^.RightNode := CurNode^.RightNode;
			if RootNode^.RightNode <> nil then RootNode^.RightNode^.Parent := RootNode;
		end;
		Dispose(CurNode);
	end;
end;
function TSplay.GetMinimum: TIndex;
begin
	Splay(Find(RootNode, -Infinity));
	Result := RootNode^.Key;
end;
function TSplay.GetMaximum: TIndex;
begin
	Splay(Find(RootNode, Infinity));
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
