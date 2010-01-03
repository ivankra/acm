(*
	Author: Amber
*)
unit PairHeap;

interface
uses
	Base;
type
	PPairNode = ^TPairNode;
	TPairNode = record
		Index: TIndex;
		Key: TKey;
		Child: PPairNode;
		Prev: PPairNode;
		Next: PPairNode;
	end;
	PPairHeap = ^TPairHeap;
	TPairHeap = object
		NodeNum: TIndex;
		MaxNodeNum: TIndex;
		Root: PPairNode;
		Nodes: array of PPairNode;
		Trees: array of PPairNode;
	public
		constructor Create(Size: TIndex);
		destructor Destory;
		procedure Insert(const Index: TIndex; const Key: TKey);
		procedure Delete(const Index: TIndex);
		function Minimum: PPairNode;
		procedure DeleteMin;
		procedure DecreaseKey(const Index: TIndex; const NewKey: TKey);
	private
		function CompareAndLink(First, Second: PPairNode): PPairNode;
		function CombineSiblings(CurNode: PPairNode): PPairNode;
	end;

implementation

constructor TPairHeap.Create(Size: TIndex);
var
	Index: TIndex;
begin
	NodeNum := 0;
	MaxNodeNum := Size;
	Root := nil;

	SetLength(Nodes, Size + 1);
	SetLength(Trees, Size + 1);
	for Index := 1 to Size do
		Nodes[Index] := nil;
end;

destructor TPairHeap.Destory;
var
	Index: TIndex;
begin
	for Index := 1 to MaxNodeNum do
		if Nodes[Index] <> nil then
			Dispose(Nodes[Index]);
end;

procedure TPairHeap.Insert(const Index: TIndex; const Key: TKey);
var
	NewNode: PPairNode;
begin
	New(NewNode);
	NewNode^.Index := Index;
	NewNode^.Key := Key;
	NewNode^.Child := nil;
	NewNode^.Prev := nil;
	NewNode^.Next := nil;
	Nodes[Index] := NewNode;

	Inc(NodeNum);
	if Root = nil then
		Root := NewNode
	else
		Root := CompareAndLink(Root, NewNode); //CurNode^.Next MUST be nil.
end;

procedure TPairHeap.Delete(const Index: TIndex);
begin
	DecreaseKey(Index, -InfiniteValue);
	DeleteMin;
end;

function TPairHeap.Minimum: PPairNode;
begin
	Result := Root;
end;

procedure TPairHeap.DeleteMin;
var
	NewRoot: PPairNode;
begin
	if Root = nil then Exit;

	NewRoot := nil;
	if Root^.Child <> nil then
		NewRoot := CombineSiblings(Root^.Child);

	Nodes[Root^.Index] := nil;
	Dispose(Root);
	Dec(NodeNum);

	Root := NewRoot;
end;

procedure TPairHeap.DecreaseKey(const Index: TIndex; const NewKey: TKey);
var
	CurNode: PPairNode;
begin
	CurNode := Nodes[Index];
	if CurNode = nil then Exit;
	if CurNode^.Key < NewKey then Exit;

	CurNode^.Key := NewKey;
	if CurNode = Root then Exit;

	if CurNode^.Next <> nil then
		CurNode^.Next^.Prev := CurNode^.Prev;
	if CurNode^.Prev^.Child = CurNode then //If CurNode is the first child.
		CurNode^.Prev^.Child := CurNode^.Next
	else
		CurNode^.Prev^.Next := CurNode^.Next;

	CurNode^.Next := nil;
	Root := CompareAndLink(Root, CurNode); //CurNode^.Next MUST be nil.
end;

//First MUST be nil. First^.Next MUST be nil.

function TPairHeap.CompareAndLink(First, Second: PPairNode): PPairNode;
begin
	if Second = nil then
		Result := First
	else if First^.Key <= Second^.Key then
	begin
		Second^.Prev := First;
		First^.Next := Second^.Next;
		if First^.Next <> nil then
			First^.Next^.Prev := First;
		Second^.Next := First^.Child;
		if Second^.Next <> nil then
			Second^.Next^.Prev := Second;
		First^.Child := Second;
		Result := First;
	end
	else
	begin
		Second^.Prev := First^.Prev;
		First^.Prev := Second;
		First^.Next := Second^.Child;
		if First^.Next <> nil then
			First^.Next^.Prev := First;
		Second^.Child := First;
		Result := Second;
	end;
end;

function TPairHeap.CombineSiblings(CurNode: PPairNode): PPairNode;
var
	Cur: TIndex;
	NumSibling: TIndex;
begin
	if CurNode^.Next = nil then
	begin
		Result := CurNode;
		Exit;
	end;
	NumSibling := 0;
	while CurNode <> nil do
	begin
		Inc(NumSibling);
		Trees[NumSibling] := CurNode;
		CurNode^.Prev^.Next := nil; //for CompareAndLink
		CurNode := CurNode^.Next;
	end;
	Cur := 1;
	while Cur + 1 <= NumSibling do
	begin
		Trees[Cur] := CompareAndLink(Trees[Cur], Trees[Cur + 1]);
		Inc(Cur, 2);
	end;
	if not Odd(NumSibling) then
		Dec(Cur, 2);
	while Cur > 1 do
	begin
		Trees[Cur - 2] := CompareAndLink(Trees[Cur - 2], Trees[Cur]);
		Dec(Cur, 2);
	end;
	Result := Trees[1];
end;
begin
end.
