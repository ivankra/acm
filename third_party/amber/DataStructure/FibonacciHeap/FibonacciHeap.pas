unit FibonacciHeap;

interface
uses
	Base;
type
	PFibonacciNode = ^TFibonacciNode;
	TFibonacciNode = record
		Index: TIndex;
		Key: TKey;
		Degree: TIndex;
		Marked: Boolean;
		Parent: PFibonacciNode;
		Child: PFibonacciNode;
		Prev: PFibonacciNode;
		Next: PFibonacciNode;
	end;
	PFibonacciHeap = ^TFibonacciHeap;
	TFibonacciHeap = object
		NodeNum: TIndex;
		MaxNodeNum: TIndex;
		MaxDegree: TIndex;
		MinRoot: PFibonacciNode;
		Nodes: array of PFibonacciNode;
		Trees: array of PFibonacciNode;
	public
		constructor Create(Size: TIndex);
		destructor Destory;
		procedure Insert(const Index: TIndex; const Key: TKey);
		procedure Delete(const Index: TIndex);
		function Minimum: PFibonacciNode;
		procedure DeleteMin;
		procedure DecreaseKey(const Index: TIndex; const NewKey: TKey);
	private
		procedure Swap(var CurNodeA, CurNodeB: PFibonacciNode);
		procedure Consolidate;
		procedure Link(CurNode, ParentNode: PFibonacciNode);
		procedure AddToRootList(CurNode: PFibonacciNode);
		procedure Cut(CurNode, ParentNode: PFibonacciNode);
		procedure CascadingCut(CurNode: PFibonacciNode);
	end;

implementation

constructor TFibonacciHeap.Create(Size: TIndex);
var
	Index: TIndex;
begin
	MaxNodeNum := Size;
	MinRoot := nil;
	NodeNum := 0;

	SetLength(Nodes, Size + 1);
	for Index := 1 to Size do
		Nodes[Index] := nil;

	MaxDegree := 0;
	while 1 shl MaxDegree < Size do
		Inc(MaxDegree);

	SetLength(Trees, MaxDegree + 1);
end;

destructor TFibonacciHeap.Destory;
var
	Index: TIndex;
begin
	for Index := 1 to MaxNodeNum do
		if Nodes[Index] <> nil then
			Dispose(Nodes[Index]);
end;

procedure TFibonacciHeap.Insert(const Index: TIndex; const Key: TKey);
var
	NewNode: PFibonacciNode;
begin
	New(NewNode);
	NewNode^.Index := Index;
	NewNode^.Key := Key;
	NewNode^.Degree := 0;
	NewNode^.Child := nil;
	Nodes[Index] := NewNode;

	Inc(NodeNum);
	AddToRootList(NewNode);
end;

procedure TFibonacciHeap.Delete(const Index: TIndex);
begin
	DecreaseKey(Index, -InfiniteValue);
	DeleteMin;
end;

function TFibonacciHeap.Minimum: PFibonacciNode;
begin
	Result := MinRoot;
end;

procedure TFibonacciHeap.DeleteMin;
var
	CurNode, ChildNode: PFibonacciNode;
begin
	if MinRoot = nil then Exit;

	CurNode := MinRoot;
	MinRoot := MinRoot^.Next;
	CurNode^.Prev^.Next := CurNode^.Next;
	CurNode^.Next^.Prev := CurNode^.Prev;

	if CurNode^.Child = nil then
	begin
		if MinRoot = CurNode then
			MinRoot := nil;
	end
	else if MinRoot = CurNode then
		MinRoot := CurNode^.Child
	else
	begin
		ChildNode := CurNode^.Child;
		MinRoot^.Prev^.Next := ChildNode^.Next;
		ChildNode^.Next^.Prev := MinRoot^.Prev;
		ChildNode^.Next := MinRoot;
		MinRoot^.Prev := ChildNode;
	end;
	Consolidate;

	Nodes[CurNode^.Index] := nil;
	Dispose(CurNode);
	Dec(NodeNum);
end;

procedure TFibonacciHeap.DecreaseKey(const Index: TIndex; const NewKey: TKey);
var
	CurNode, ParentNode: PFibonacciNode;
begin
	CurNode := Nodes[Index];
	if CurNode = nil then Exit;
	if CurNode^.Key < NewKey then Exit;
	CurNode^.Key := NewKey;

	ParentNode := CurNode^.Parent;
	if ParentNode <> nil then
		if CurNode^.Key < ParentNode^.Key then
		begin
			Cut(CurNode, ParentNode);
			CascadingCut(ParentNode);
		end;
	if CurNode^.Key < MinRoot^.Key then
		MinRoot := CurNode;
end;

procedure TFibonacciHeap.Swap(var CurNodeA, CurNodeB: PFibonacciNode);
var
	TmpNode: PFibonacciNode;
begin
	TmpNode := CurNodeA;
	CurNodeA := CurNodeB;
	CurNodeB := TmpNode;
end;

procedure TFibonacciHeap.Consolidate;
var
	Degree: TIndex;
	RootNode, ChildNode, CurNode: PFibonacciNode;
begin
	if MinRoot = nil then Exit;
	for Degree := 0 to MaxDegree do
		Trees[Degree] := nil;
	MinRoot^.Prev^.Next := nil; //Break the circle
	MinRoot^.Prev := nil;

	RootNode := MinRoot;
	repeat
		CurNode := RootNode;
		RootNode := RootNode^.Next;
		Degree := CurNode^.Degree;
		while Trees[Degree] <> nil do
		begin
			ChildNode := Trees[Degree];
			if ChildNode^.Key < CurNode^.Key then //Keep ChildNode greater
				Swap(CurNode, ChildNode);
			Link(ChildNode, CurNode);
			Trees[Degree] := nil;
			Inc(Degree);
		end;
		Trees[Degree] := CurNode;
	until RootNode = nil;

	//Rebulid the root list
	MinRoot := nil;
	for Degree := 0 to MaxDegree do
		if Trees[Degree] <> nil then
			AddToRootList(Trees[Degree]);
end;

procedure TFibonacciHeap.Link(CurNode, ParentNode: PFibonacciNode);
begin
	//Remove the node from root list
	if CurNode^.Next <> nil then
		CurNode^.Next^.Prev := CurNode^.Prev;
	if CurNode^.Prev <> nil then
		CurNode^.Prev^.Next := CurNode^.Next;

	//Link the node to its new parent's child.
	CurNode^.Parent := ParentNode;
	if ParentNode^.Child = nil then
	begin
		ParentNode^.Child := CurNode;
		CurNode^.Prev := CurNode;
		CurNode^.Next := CurNode;
	end
	else
	begin
		CurNode^.Prev := ParentNode^.Child;
		CurNode^.Next := ParentNode^.Child^.Next;
		CurNode^.Prev^.Next := CurNode;
		CurNode^.Next^.Prev := CurNode;
	end;

	Inc(ParentNode^.Degree);
	if ParentNode^.Marked then
		ParentNode^.Marked := false;
end;

procedure TFibonacciHeap.AddToRootList(CurNode: PFibonacciNode);
begin
	CurNode^.Marked := false;
	CurNode^.Parent := nil;
	if MinRoot = nil then
	begin
		MinRoot := CurNode;
		CurNode^.Prev := CurNode;
		CurNode^.Next := CurNode;
	end
	else
	begin
		CurNode^.Prev := MinRoot^.Prev;
		CurNode^.Next := MinRoot;
		CurNode^.Prev^.Next := CurNode;
		CurNode^.Next^.Prev := CurNode;
		if CurNode^.Key < MinRoot^.Key then
			MinRoot := CurNode;
	end;
end;

procedure TFibonacciHeap.Cut(CurNode, ParentNode: PFibonacciNode);
begin
	if ParentNode^.Child = CurNode then
		ParentNode^.Child := CurNode^.Next;
	if ParentNode^.Child = CurNode then
		ParentNode^.Child := nil;

	Dec(ParentNode^.Degree);
	CurNode^.Prev^.Next := CurNode^.Next;
	CurNode^.Next^.Prev := CurNode^.Prev;
	AddToRootList(CurNode);
end;

procedure TFibonacciHeap.CascadingCut(CurNode: PFibonacciNode);
var
	ParentNode: PFibonacciNode;
begin
	ParentNode := CurNode^.Parent;
	while ParentNode <> nil do
		if CurNode^.Marked then
		begin
			Cut(CurNode, ParentNode);
			CurNode := ParentNode;
			ParentNode := CurNode^.Parent;
		end
		else
		begin
			CurNode^.Marked := true;
			ParentNode := nil;
		end;
end;
begin
end.
